// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file lumino.c
 * @brief Lumino module implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/lumino>
 */

#include "lumino.h"

#include <lib/lib8tion/lib8tion.h>

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Set default config options where unset.
#ifndef LUMINO_HIGH_BRIGHTNESS
#  define LUMINO_HIGH_BRIGHTNESS 1.0
#endif // LUMINO_HIGH_BRIGHTNESS
#ifndef LUMINO_LOW_BRIGHTNESS
#  define LUMINO_LOW_BRIGHTNESS (0.4 * (LUMINO_HIGH_BRIGHTNESS))
#endif // LUMINO_LOW_BRIGHTNESS
#ifndef LUMINO_SOON_TIMEOUT
#  define LUMINO_SOON_TIMEOUT  5000
#endif // LUMINO_SOON_TIMEOUT
#ifndef LUMINO_LONG_TIMEOUT
#  define LUMINO_LONG_TIMEOUT  120000
#endif // LUMINO_LONG_TIMEOUT
#ifndef LUMINO_TRANSITION
#  define LUMINO_TRANSITION  500
#elif LUMINO_TRANSITION > 2000
#  error "LUMINO_TRANSITION must be at most 2000 ms."
#endif // LUMINO_TRANSITION
#ifndef LUMINO_BOOT_COLOR
#  define LUMINO_BOOT_COLOR RGB_RED
#endif // LUMINO_BOOT_COLOR

#if (LUMINO_LONG_TIMEOUT) > 0 || (LUMINO_SOON_TIMEOUT) > 0
#  define USE_SLEEP_TIMER
#endif

enum {
  // Convert values in [0.0, 1.0] to [0, RGB_MATRIX_MAXIMUM_BRIGHTNESS].
  HIGH_BRIGHTNESS = (uint8_t)(
      (((LUMINO_HIGH_BRIGHTNESS) <= 1.0) ? (LUMINO_HIGH_BRIGHTNESS) : 1.0) *
      (RGB_MATRIX_MAXIMUM_BRIGHTNESS) + 0.5),
  LOW_BRIGHTNESS = (uint8_t)(
      (((LUMINO_LOW_BRIGHTNESS) <= 1.0) ? (LUMINO_LOW_BRIGHTNESS) : 1.0) *
      (RGB_MATRIX_MAXIMUM_BRIGHTNESS) + 0.5),
  // Compute (255 / LUMINO_TRANSITION) with 6 fractional bits.
  ANIM_TIME_SCALE_Q6 = (255 * 64 + (LUMINO_TRANSITION) / 2)
      / (LUMINO_TRANSITION),
  FRAME_PERIOD = 16,  // About 60 fps.
};

enum { ANIM_SLEEP, ANIM_WAKE, ANIM_SET_VALUE };

#ifdef USE_SLEEP_TIMER
/** Time when lighting should go to sleep. */
static uint32_t sleep_time = 0;
#endif  // USE_SLEEP_TIMER

/** Time when animated lighting should next be updated. */
static uint16_t anim_update_time = 0;
/** Time when animated lighting transition started. */
static uint16_t anim_start_time = 0;
/** Animation starting brightness value. */
static uint8_t anim_start_value = 0;
/** Animation ending brightness value. */
static uint8_t anim_end_value = 0;
/** The kind of animation being performed. */
static uint8_t anim_kind = ANIM_SLEEP;

/** Configured brightness value to use when awake. */
static uint8_t awake_value = 0;
/** Number of key events since last awoken. */
static uint8_t event_count = 0;
/** Whether lighting is currently awake. */
static bool awake = false;

/** Reads the RGB Matrix current brightness value. */
static uint8_t read_current_value(void) {
  return rgb_matrix_is_enabled() ? rgb_matrix_get_val() : 0;
}

/** Updates the RGB Matrix brightness value without saving to EEPROM. */
static void update_current_value(uint8_t value) {
#ifndef NO_DEBUG
  // Avoid spamming console with RGB matrix log messages.
  const bool saved_debug_enable = debug_enable;
  debug_enable = false;
#endif // NO_DEBUG

  if (value > 0 && !rgb_matrix_is_enabled()) {
    rgb_matrix_enable_noeeprom();
  }

  hsv_t hsv = rgb_matrix_get_hsv();
  hsv.v = value;
  rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);

#ifndef NO_DEBUG
  debug_enable = saved_debug_enable;
#endif // NO_DEBUG
}

#ifdef USE_SLEEP_TIMER
/** Updates the inactivity sleep timer. */
static void update_sleep_timer(void) {
#  if (LUMINO_SOON_TIMEOUT) > 0 && \
      ((LUMINO_SOON_TIMEOUT) < (LUMINO_LONG_TIMEOUT) || \
       (LUMINO_LONG_TIMEOUT) <= 0)
  if (event_count <= 10) {
    sleep_time = (timer_read32() + UINT32_C(LUMINO_SOON_TIMEOUT)) | 1;
  }
  else
#  endif
  {
#  if (LUMINO_LONG_TIMEOUT) > 0
    sleep_time = (timer_read32() + UINT32_C(LUMINO_LONG_TIMEOUT)) | 1;
#  else
    sleep_time = 0;  // Never go to sleep.
#  endif
  }
}
#else
#define update_sleep_timer()
#endif  // USE_SLEEP_TIMER

/** Start animation, transitioning to `end_value`. */
static void anim_play(uint8_t kind, uint8_t end_value) {
  const uint8_t start_value = read_current_value();
  if (start_value != end_value) {
    dprintf("lumino: Brightness value %u -> %u.\n", start_value, end_value);
    anim_start_time = timer_read() | 1;
    anim_update_time = anim_start_time;
    anim_start_value = start_value;
    anim_end_value = end_value;
    anim_kind = kind;
    awake = true;
  }
}

uint8_t lumino_get_value(void) {
  const uint8_t current_value = read_current_value();
  return (current_value > 0) ? current_value : awake_value;
}

void lumino_set_value(uint8_t value) {
  const uint8_t current_value = read_current_value();
  if (value != awake_value || value != current_value) {
    anim_play(ANIM_SET_VALUE, value);
    awake_value = value;
  }
}

void lumino_cycle_3_state(void) {
  lumino_set_value(
      (awake_value == 0) ? LOW_BRIGHTNESS :
      ((awake_value < HIGH_BRIGHTNESS) ? HIGH_BRIGHTNESS : 0)
  );
}

void lumino_sleep_soon(void) {
  event_count = 0;
  update_sleep_timer();
}

void housekeeping_task_lumino(void) {
  if (!awake) { return; }

  if (anim_start_time) {
    const uint16_t now = timer_read();
    if (timer_expired(now, anim_update_time)) {
      // Next animation frame.
      uint8_t value;
#if LUMINO_TRANSITION >= 64
      const uint16_t elapsed = now - anim_start_time;
      // Compute t = min(elapsed * (255 / LUMINO_TRANSITION), 255).
      const uint8_t t = (elapsed <= (LUMINO_TRANSITION))
          ? (((uint16_t)elapsed * ANIM_TIME_SCALE_Q6) >> 6) : 255;
      const uint8_t weight = ease8InOutCubic(t);
      if (weight < 255) {
        value = lerp8by8(anim_start_value, anim_end_value, weight);
        anim_update_time = now + FRAME_PERIOD;
      }
      else
#endif
      {  // End of transition.
        anim_start_time = 0;  // No longer animating.
        value = anim_end_value;

        switch (anim_kind) {
          case ANIM_SLEEP:
            event_count = 0;
            awake = false;
            break;
          case ANIM_SET_VALUE: {
#ifndef LUMINO_NO_EEPROM
            // If this is the end of an animation was initiated by
            // lumino_set_value(), save the set brightness value to EEPROM.
            // NOTE: This should be the only place in Lumino where EEPROM is
            // written. All other RGB Matrix updates should use the `_noeeprom`
            // APIs to avoid writing to EEPROM unnecessarily.
            hsv_t hsv = rgb_matrix_get_hsv();
            rgb_matrix_sethsv(hsv.h, hsv.s, value);
#endif  // LUMINO_NO_EEPROM
          } // Fallthrough intended.
          case ANIM_WAKE:
            update_sleep_timer();
            break;
        }
      }

      update_current_value(value);
    }
  }
#ifdef USE_SLEEP_TIMER
  else if (sleep_time && timer_expired32(timer_read32(), sleep_time)) {
    awake_value = read_current_value();
    anim_play(ANIM_SLEEP, 0);  // Go to sleep.
  }
#endif  // USE_SLEEP_TIMER
  housekeeping_task_lumino_kb();
}

void keyboard_post_init_lumino(void) {
  if (rgb_matrix_is_enabled()) {
    awake_value = rgb_matrix_get_val();
    update_current_value(0);
    anim_play(ANIM_WAKE, awake_value);
  }
  keyboard_post_init_lumino_kb();
}

bool process_record_lumino(uint16_t keycode, keyrecord_t* record) {
  if (!process_record_lumino_kb(keycode, record)) {
    return false;
  }
#ifdef USE_SLEEP_TIMER
  event_count = qadd8(event_count, 1);
#endif  // USE_SLEEP_TIMER

  switch (keycode) {
    case LUMINO:
      if (record->event.pressed) {
        lumino_cycle_3_state();
      }
      break;

    default:
      if (awake_value > 0) {
        if (!awake || (anim_start_time && anim_end_value == 0)) {
          anim_play(ANIM_WAKE, awake_value);  // Wake up.
        } else {
          update_sleep_timer();
        }
      }
  }
  return true;
}

bool shutdown_lumino(bool jump_to_bootloader) {
  if (!shutdown_lumino_kb(jump_to_bootloader)) {
    return false;
  }
  rgb_matrix_enable_noeeprom();
  rgb_matrix_set_color_all(LUMINO_BOOT_COLOR);
  rgb_matrix_update_pwm_buffers();

  return true;
}
