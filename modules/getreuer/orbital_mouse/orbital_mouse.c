// Copyright 2023-2025 Google LLC
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
 * @file orbital_mouse.c
 * @brief Orbital Mouse community module implementation
 *
 * For documentation, see
 * <https://getreuer.info/posts/keyboards/orbital-mouse>
 */

#include "orbital_mouse.h"

#ifndef ORBITAL_MOUSE_RADIUS
#define ORBITAL_MOUSE_RADIUS 36
#endif  // ORBITAL_MOUSE_RADIUS
#ifndef ORBITAL_MOUSE_SLOW_MOVE_FACTOR
#define ORBITAL_MOUSE_SLOW_MOVE_FACTOR 0.333
#endif  // ORBITAL_MOUSE_SLOW_MOVE_FACTOR
#ifndef ORBITAL_MOUSE_SLOW_TURN_FACTOR
#define ORBITAL_MOUSE_SLOW_TURN_FACTOR 0.5
#endif  // ORBITAL_MOUSE_SLOW_TURN_FACTOR
#ifndef ORBITAL_MOUSE_WHEEL_SPEED
#define ORBITAL_MOUSE_WHEEL_SPEED 0.2
#endif  // ORBITAL_MOUSE_WHEEL_SPEED
#ifndef ORBITAL_MOUSE_DBL_DELAY_MS
#define ORBITAL_MOUSE_DBL_DELAY_MS 50
#endif  // ORBITAL_MOUSE_DBL_DELAY_MS
#ifndef ORBITAL_MOUSE_SPEED_CURVE
#define ORBITAL_MOUSE_SPEED_CURVE \
      {24, 24, 24, 32, 58, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66}
//     |               |               |               |           |
// t = 0.000           1.024           2.048           3.072       3.840 s
#endif  // ORBITAL_MOUSE_SPEED_CURVE
#ifndef ORBITAL_MOUSE_INTERVAL_MS
#define ORBITAL_MOUSE_INTERVAL_MS 16
#endif  // ORBITAL_MOUSE_INTERVAL_MS

#if !(0 <= ORBITAL_MOUSE_RADIUS && ORBITAL_MOUSE_RADIUS <= 63)
#error "Invalid ORBITAL_MOUSE_RADIUS. Value must be in [0, 63]."
#endif

enum {
  /** Number of distinct angles. */
  NUM_ANGLES = 64,
  /** Number of intervals in speed curve table. */
  NUM_SPEED_CURVE_INTERVALS = 16,
  /** Orbit radius in pixels as a Q6.2 value. */
  RADIUS_Q6_2 = (uint8_t)((ORBITAL_MOUSE_RADIUS) * 4 + 0.5),
  /** Slow mode movement speed factor as a Q.8 value. */
  SLOW_MOVE_FACTOR_Q_8 = (ORBITAL_MOUSE_SLOW_MOVE_FACTOR) < 0.99
      ? ((uint8_t)((ORBITAL_MOUSE_SLOW_MOVE_FACTOR) * 256 + 0.5)) : 255,
  /** Slow mode turn speed factor as a Q.8 value. */
  SLOW_TURN_FACTOR_Q_8 = (ORBITAL_MOUSE_SLOW_TURN_FACTOR) < 0.99
      ? ((uint8_t)((ORBITAL_MOUSE_SLOW_TURN_FACTOR) * 256 + 0.5)) : 255,
  /** Wheel speed in steps/frame as a Q2.6 value. */
  WHEEL_SPEED_Q2_6 = (ORBITAL_MOUSE_WHEEL_SPEED) < 3.99
      ? ((uint8_t)((ORBITAL_MOUSE_WHEEL_SPEED) * 64 + 0.5)) : 255,
  /** Double click delay in units of intervals. */
  DOUBLE_CLICK_DELAY_INTERVALS =
      (ORBITAL_MOUSE_DBL_DELAY_MS) / (ORBITAL_MOUSE_INTERVAL_MS),
};

// Masks for the `held_keys` bitfield.
enum {
  HELD_U = 1,
  HELD_D = 2,
  HELD_L = 4,
  HELD_R = 8,
  HELD_W_U = 16,
  HELD_W_D = 32,
  HELD_W_L = 64,
  HELD_W_R = 128,
};

static const uint8_t init_speed_curve[NUM_SPEED_CURVE_INTERVALS] =
  ORBITAL_MOUSE_SPEED_CURVE;
static struct {
  report_mouse_t report;
  // Current speed curve, should point to a table of 16 values.
  const uint8_t* speed_curve;
  // Time when the Orbital Mouse task function should next run.
  uint16_t timer;
  // Fractional displacement of the cursor as Q7.8 values.
  int16_t x;
  int16_t y;
  // Fractional displacement of the mouse wheel as Q9.6 values.
  int16_t wheel_x;
  int16_t wheel_y;
  // Current cursor movement speed as a Q9.6 value.
  int16_t speed;
  // Bitfield tracking which movement keys are currently held.
  uint8_t held_keys;
  // Cursor movement time, counted in number of intervals.
  uint8_t move_t;
  // Cursor movement direction, 1 => forward, -1 => backward.
  int8_t move_dir;
  // Steering direction, 1 => counter-clockwise, -1 => clockwise.
  int8_t steer_dir;
  // Mouse wheel movement directions.
  int8_t wheel_x_dir;
  int8_t wheel_y_dir;
  // Heading direction as a Q6.8 value, with 0 => up, 16 * 256 => left, etc.
  uint16_t angle;
  // Selected mouse button as a base-0 index.
  uint8_t selected_button;
  // Tracks double click action.
  uint8_t double_click_frame;
  // When true, movement and turning are slower.
  bool slow;
} state = {.speed_curve = init_speed_curve};

/**
 * Fixed-point sine with specified amplitude and phase.
 *
 * @param amplitude Nonnegative Q6.2 value.
 * @param phase Value in [0, 63].
 * @returns Result as a Q6.8 value.
 */
static int16_t scaled_sin(uint8_t amplitude, uint8_t phase) {
  // Look up table covers half a cycle of a sine wave.
  static const uint8_t lut[NUM_ANGLES / 2] PROGMEM = {
      0,   25,  50,  74,  98,  120, 142, 162, 180, 197, 212,
      225, 236, 244, 250, 254, 255, 254, 250, 244, 236, 225,
      212, 197, 180, 162, 142, 120, 98,  74,  50,  25};
  // amplitude Q6.2 and lut is Q0.8. Shift down by 2 so that the result is Q6.8.
  int16_t value = (int16_t)(((uint16_t)amplitude
        * pgm_read_byte(lut + (phase & (NUM_ANGLES / 2 - 1))) + 2) >> 2);
  return ((NUM_ANGLES / 2) & phase) == 0 ? value : -value;
}

/** Computes fixed-point cosine. */
static int16_t scaled_cos(uint8_t amplitude, uint8_t phase) {
  return scaled_sin(amplitude, phase + (NUM_ANGLES / 4));
}

/** Wakes the Orbital Mouse task.  */
static void wake_orbital_mouse_task(void) {
  if (!state.timer) {
    state.timer = timer_read() | 1;
  }
}

/** Converts a keycode to a mask for  the `held_keys` bitfield. */
static uint8_t keycode_to_held_mask(uint16_t keycode) {
  switch (keycode) {
    case OM_U: return HELD_U;
    case OM_D: return HELD_D;
    case OM_L: return HELD_L;
    case OM_R: return HELD_R;
    case OM_W_U: return HELD_W_U;
    case OM_W_D: return HELD_W_D;
    case OM_W_L: return HELD_W_L;
    case OM_W_R: return HELD_W_R;
  }
  return 0;
}

/** Presses mouse button i, with i being a base-0 index. */
static void press_mouse_button(uint8_t i, bool pressed) {
  if (i >= 8) {
    i = state.selected_button;
  }
  const uint8_t mask = 1 << i;
  if (pressed) {
    state.report.buttons |= mask;
  } else {
    state.report.buttons &= ~mask;
  }
  wake_orbital_mouse_task();
}

/** Selects mouse button i. */
static void select_mouse_button(uint8_t i) {
  state.selected_button = i;
  // Reset buttons and double-click state when switching selection.
  state.report.buttons = 0;
  state.double_click_frame = 0;
  wake_orbital_mouse_task();
}

static int8_t get_dir_from_held_keys(uint8_t bit_shift) {
  static const int8_t dir[4] = {0, 1, -1, 0};
  return dir[(state.held_keys >> bit_shift) & 3];
}

void set_orbital_mouse_speed_curve(const uint8_t* speed_curve) {
  state.speed_curve = (speed_curve != NULL) ? speed_curve : init_speed_curve;
}

uint8_t get_orbital_mouse_angle(void) {
  return (state.angle >> 8) & (NUM_ANGLES - 1);
}

static void set_orbital_mouse_angle_fractional(uint16_t angle) {
  state.x += scaled_sin(RADIUS_Q6_2, state.angle >> 8);
  state.y += scaled_cos(RADIUS_Q6_2, state.angle >> 8);
  state.angle = angle;
  state.x -= scaled_sin(RADIUS_Q6_2, angle >> 8);
  state.y -= scaled_cos(RADIUS_Q6_2, angle >> 8);
  wake_orbital_mouse_task();
}

void set_orbital_mouse_angle(uint8_t angle) {
  set_orbital_mouse_angle_fractional((uint16_t)angle << 8);
}

bool process_record_orbital_mouse(uint16_t keycode, keyrecord_t* record) {
  if (!(IS_MOUSE_KEYCODE(keycode) ||
        (OM_SLOW <= keycode && keycode <= OM_SEL8))) {
    return true;
  }

  uint8_t held_mask = keycode_to_held_mask(keycode);
  if (held_mask != 0) {
    // Update `held_keys` bitfield.
    if (record->event.pressed) {
      state.held_keys |= held_mask;
    } else {
      state.held_keys &= ~held_mask;
    }
  } else {
    switch (keycode) {
      case OM_BTN1 ... OM_BTN8:
        press_mouse_button(keycode - OM_BTN1, record->event.pressed);
        return false;
      case OM_BTNS:
        press_mouse_button(255, record->event.pressed);
        return false;
      case OM_HLDS:
        if (record->event.pressed) {
          press_mouse_button(255, true);
        }
        return false;
      case OM_RELS:
        if (record->event.pressed) {
          press_mouse_button(255, false);
        }
        return false;
      case OM_DBLS:
        if (record->event.pressed) {
          state.double_click_frame = 1;
        }
        break;
      case OM_SLOW:
        state.slow = record->event.pressed;
        return false;
      case OM_SEL1 ... OM_SEL8:
        if (record->event.pressed) {
          select_mouse_button(keycode - OM_SEL1);
        }
        return false;
    }
  }

  // Update cursor movement direction.
  const int8_t dir = get_dir_from_held_keys(0);
  if (state.move_dir != dir) {
    state.move_dir = dir;
    state.move_t = 0;
  }
  // Update steering direction.
  state.steer_dir = get_dir_from_held_keys(2);
  // Update wheel movement.
  state.wheel_y_dir = get_dir_from_held_keys(4);
  state.wheel_x_dir = get_dir_from_held_keys(6);
  wake_orbital_mouse_task();

  return false;
}

void housekeeping_task_orbital_mouse(void) {
  const uint16_t now = timer_read();
  if (!state.timer || !timer_expired(now, state.timer)) {
    return;
  }

  bool active = false;

  // Update position if moving.
  if (state.move_dir) {
    // Update speed, interpolated from speed_curve.
    if (state.move_t <= 16 * (NUM_SPEED_CURVE_INTERVALS - 1)) {
      if (state.move_t == 0) {
        state.speed = (int16_t)state.speed_curve[0] * 16;
      } else {
        const uint8_t i = (state.move_t - 1) / 16;
        state.speed += (int16_t)state.speed_curve[i + 1]
                     - (int16_t)state.speed_curve[i];
      }

      ++state.move_t;
    }
    // Round and cast from Q9.6 to Q6.2.
    uint8_t speed = (state.speed + 8) / 16;
    if (state.slow) {
      speed = ((uint16_t)speed) * (1 + (uint16_t)SLOW_MOVE_FACTOR_Q_8) >> 8;
    }

    state.x -= state.move_dir * scaled_sin(speed, state.angle >> 8);
    state.y -= state.move_dir * scaled_cos(speed, state.angle >> 8);
    active = true;
  }

  // Update heading angle if steering.
  if (state.steer_dir) {
    int16_t angle_step = state.slow ? SLOW_TURN_FACTOR_Q_8 : 256;
    if (state.steer_dir == -1) {
      angle_step = -angle_step;
    }
    set_orbital_mouse_angle_fractional(state.angle + angle_step);
    active = true;
  }

  // Update mouse wheel if active.
  if (state.wheel_x_dir || state.wheel_y_dir) {
    state.wheel_x -= state.wheel_x_dir * WHEEL_SPEED_Q2_6;
    state.wheel_y += state.wheel_y_dir * WHEEL_SPEED_Q2_6;
    active = true;
  }

  // Update double click action.
  if (state.double_click_frame) {
    ++state.double_click_frame;
    const uint8_t mask = 1 << state.selected_button;
    switch (state.double_click_frame) {
      case 2:
      case 3:
      case 4 + DOUBLE_CLICK_DELAY_INTERVALS:
        state.report.buttons ^= mask;
        break;
      case 5 + DOUBLE_CLICK_DELAY_INTERVALS:
        state.report.buttons &= ~mask;
        state.double_click_frame = 0;
    }
    active = true;
  }

  // Schedule when task should run again, or go to sleep if inactive.
  state.timer = active ? ((now + ORBITAL_MOUSE_INTERVAL_MS) | 1) : 0;

  // Set whole part of movement deltas in report and retain fractional parts.
  state.report.x = state.x / 256;
  state.report.y = state.y / 256;
  state.x -= (int16_t)state.report.x * 256;
  state.y -= (int16_t)state.report.y * 256;
  state.report.h = state.wheel_x / 64;
  state.report.v = state.wheel_y / 64;
  state.wheel_x -= (int16_t)state.report.h * 64;
  state.wheel_y -= (int16_t)state.report.v * 64;
  host_mouse_send(&state.report);
}

