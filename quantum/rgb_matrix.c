/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "rgb_matrix.h"
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include <string.h>
#include <math.h>

#include "lib/lib8tion/lib8tion.h"

#include "rgb_matrix_animations/solid_color_anim.h"
#include "rgb_matrix_animations/alpha_mods_anim.h"
#include "rgb_matrix_animations/dual_beacon_anim.h"
#include "rgb_matrix_animations/gradient_up_down_anim.h"
#include "rgb_matrix_animations/raindrops_anim.h"
#include "rgb_matrix_animations/cycle_all_anim.h"
#include "rgb_matrix_animations/cycle_left_right_anim.h"
#include "rgb_matrix_animations/cycle_up_down_anim.h"
#include "rgb_matrix_animations/rainbow_beacon_anim.h"
#include "rgb_matrix_animations/rainbow_pinwheels_anim.h"
#include "rgb_matrix_animations/rainbow_moving_chevron_anim.h"
#include "rgb_matrix_animations/jellybean_raindrops_anim.h"
#include "rgb_matrix_animations/digital_rain_anim.h"
#include "rgb_matrix_animations/solid_reactive_simple_anim.h"
#include "rgb_matrix_animations/solid_reactive_anim.h"
#include "rgb_matrix_animations/solid_reactive_wide.h"
#include "rgb_matrix_animations/solid_reactive_cross.h"
#include "rgb_matrix_animations/solid_reactive_nexus.h"
#include "rgb_matrix_animations/splash_anim.h"
#include "rgb_matrix_animations/solid_splash_anim.h"
#include "rgb_matrix_animations/breathing_anim.h"

#ifndef RGB_DISABLE_AFTER_TIMEOUT
  #define RGB_DISABLE_AFTER_TIMEOUT 0
#endif

#ifndef RGB_DISABLE_WHEN_USB_SUSPENDED
  #define RGB_DISABLE_WHEN_USB_SUSPENDED false
#endif

#ifndef EECONFIG_RGB_MATRIX
  #define EECONFIG_RGB_MATRIX EECONFIG_RGBLIGHT
#endif

#if !defined(RGB_MATRIX_MAXIMUM_BRIGHTNESS) || RGB_MATRIX_MAXIMUM_BRIGHTNESS > UINT8_MAX
  #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

#if !defined(RGB_MATRIX_HUE_STEP)
  #define RGB_MATRIX_HUE_STEP 8
#endif

#if !defined(RGB_MATRIX_SAT_STEP)
  #define RGB_MATRIX_SAT_STEP 16
#endif

#if !defined(RGB_MATRIX_VAL_STEP)
  #define RGB_MATRIX_VAL_STEP 16
#endif

#if !defined(RGB_MATRIX_SPD_STEP)
  #define RGB_MATRIX_SPD_STEP 16
#endif

bool g_suspend_state = false;

rgb_config_t rgb_matrix_config;

rgb_counters_t g_rgb_counters;
static uint32_t rgb_counters_buffer;

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
  last_hit_t g_last_hit_tracker;
  static last_hit_t last_hit_buffer;
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED

uint32_t eeconfig_read_rgb_matrix(void) {
  return eeprom_read_dword(EECONFIG_RGB_MATRIX);
}

void eeconfig_update_rgb_matrix(uint32_t val) {
  eeprom_update_dword(EECONFIG_RGB_MATRIX, val);
}

void eeconfig_update_rgb_matrix_default(void) {
  dprintf("eeconfig_update_rgb_matrix_default\n");
  rgb_matrix_config.enable = 1;
#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  rgb_matrix_config.mode = RGB_MATRIX_CYCLE_LEFT_RIGHT;
#else
  // fallback to solid colors if RGB_MATRIX_CYCLE_LEFT_RIGHT is disabled in userspace
  rgb_matrix_config.mode = RGB_MATRIX_SOLID_COLOR;
#endif
  rgb_matrix_config.hue = 0;
  rgb_matrix_config.sat = UINT8_MAX;
  rgb_matrix_config.val = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
  rgb_matrix_config.speed = UINT8_MAX / 2;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void eeconfig_debug_rgb_matrix(void) {
  dprintf("rgb_matrix_config eprom\n");
  dprintf("rgb_matrix_config.enable = %d\n", rgb_matrix_config.enable);
  dprintf("rgb_matrix_config.mode = %d\n", rgb_matrix_config.mode);
  dprintf("rgb_matrix_config.hue = %d\n", rgb_matrix_config.hue);
  dprintf("rgb_matrix_config.sat = %d\n", rgb_matrix_config.sat);
  dprintf("rgb_matrix_config.val = %d\n", rgb_matrix_config.val);
  dprintf("rgb_matrix_config.speed = %d\n", rgb_matrix_config.speed);
}

uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i) {
  // TODO: This is kinda expensive, fix this soonish
  uint8_t led_count = 0;
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL && led_count < LED_HITS_TO_REMEMBER; i++) {
    matrix_co_t matrix_co = g_rgb_leds[i].matrix_co;
    if (row == matrix_co.row && column == matrix_co.col) {
      led_i[led_count] = i;
      led_count++;
    }
  }
  return led_count;
}

void rgb_matrix_update_pwm_buffers(void) {
  rgb_matrix_driver.flush();
}

void rgb_matrix_set_color( int index, uint8_t red, uint8_t green, uint8_t blue ) {
#ifdef RGB_MATRIX_EXTRA_TOG
  const bool is_key = g_rgb_leds[index].matrix_co.raw != 0xff;
  if (
    (rgb_matrix_config.enable == RGB_ZONE_KEYS && !is_key) ||
    (rgb_matrix_config.enable == RGB_ZONE_UNDER && is_key)
  ) {
    rgb_matrix_driver.set_color(index, 0, 0, 0);
    return;
  }
#endif

  rgb_matrix_driver.set_color(index, red, green, blue);
}

void rgb_matrix_set_color_all( uint8_t red, uint8_t green, uint8_t blue ) {
#ifdef RGB_MATRIX_EXTRA_TOG
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
      rgb_matrix_set_color(i, red, green, blue);
  }
#else
  rgb_matrix_driver.set_color_all(red, green, blue);
#endif
}

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
  uint8_t led[LED_HITS_TO_REMEMBER];
  uint8_t led_count = 0;

#if defined(RGB_MATRIX_KEYRELEASES)
  if (!record->event.pressed) {
    led_count = rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led);
    g_rgb_counters.any_key_hit = 0;
  }
#elif defined(RGB_MATRIX_KEYPRESSES)
  if (record->event.pressed) {
    led_count = rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led);
    g_rgb_counters.any_key_hit = 0;
  }
#endif // defined(RGB_MATRIX_KEYRELEASES)

  if (last_hit_buffer.count + led_count > LED_HITS_TO_REMEMBER) {
    memcpy(&last_hit_buffer.x[0], &last_hit_buffer.x[led_count], LED_HITS_TO_REMEMBER - led_count);
    memcpy(&last_hit_buffer.y[0], &last_hit_buffer.y[led_count], LED_HITS_TO_REMEMBER - led_count);
    memcpy(&last_hit_buffer.tick[0], &last_hit_buffer.tick[led_count], (LED_HITS_TO_REMEMBER - led_count) * 2); // 16 bit
    memcpy(&last_hit_buffer.index[0], &last_hit_buffer.index[led_count], LED_HITS_TO_REMEMBER - led_count);
    last_hit_buffer.count--;
  }

  for(uint8_t i = 0; i < led_count; i++) {
    uint8_t index = last_hit_buffer.count;
    last_hit_buffer.x[index] = g_rgb_leds[led[i]].point.x;
    last_hit_buffer.y[index] = g_rgb_leds[led[i]].point.y;
    last_hit_buffer.index[index] = led[i];
    last_hit_buffer.tick[index] = 0;
    last_hit_buffer.count++;
  }
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
  return true;
}

void rgb_matrix_test(void) {
  // Mask out bits 4 and 5
  // Increase the factor to make the test animation slower (and reduce to make it faster)
  uint8_t factor = 10;
  switch ( (g_rgb_counters.tick & (0b11 << factor)) >> factor )
  {
    case 0: {
      rgb_matrix_set_color_all( 20, 0, 0 );
      break;
    }
    case 1: {
      rgb_matrix_set_color_all( 0, 20, 0 );
      break;
    }
    case 2: {
      rgb_matrix_set_color_all( 0, 0, 20 );
      break;
    }
    case 3: {
      rgb_matrix_set_color_all( 20, 20, 20 );
      break;
    }
  }
}

static bool rgb_matrix_none(effect_params_t* params) {
  if (!params->init) {
    return false;
  }

  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0, 0, 0);
  }
  return led_max < DRIVER_LED_TOTAL;
}

static uint8_t rgb_last_enable = UINT8_MAX;
static uint8_t rgb_last_effect = UINT8_MAX;
static effect_params_t rgb_effect_params = { 0, 0 };
static rgb_task_states rgb_task_state = SYNCING;

static void rgb_task_timers(void) {
  // Update double buffer timers
  uint16_t deltaTime = timer_elapsed32(rgb_counters_buffer);
  rgb_counters_buffer = timer_read32();
  if (g_rgb_counters.any_key_hit < UINT32_MAX) {
    if (UINT32_MAX - deltaTime < g_rgb_counters.any_key_hit) {
      g_rgb_counters.any_key_hit = UINT32_MAX;
    } else {
      g_rgb_counters.any_key_hit += deltaTime;
    }
  }

  // Update double buffer last hit timers
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
  uint8_t count = last_hit_buffer.count;
  for (uint8_t i = 0; i < count; ++i) {
    if (UINT16_MAX - deltaTime < last_hit_buffer.tick[i]) {
      last_hit_buffer.count--;
      continue;
    }
    last_hit_buffer.tick[i] += deltaTime;
  }
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
}

static void rgb_task_sync(void) {
  // next task
  if (timer_elapsed32(g_rgb_counters.tick) >= RGB_MATRIX_LED_FLUSH_LIMIT)
    rgb_task_state = STARTING;
}

static void rgb_task_start(void) {
  // reset iter
  rgb_effect_params.iter = 0;

  // update double buffers
  g_rgb_counters.tick = rgb_counters_buffer;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
  g_last_hit_tracker = last_hit_buffer;
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED

  // next task
  rgb_task_state = RENDERING;
}

static void rgb_task_render(uint8_t effect) {
  bool rendering = false;
  rgb_effect_params.init = (effect != rgb_last_effect) || (rgb_matrix_config.enable != rgb_last_enable);

  // each effect can opt to do calculations
  // and/or request PWM buffer updates.
  switch (effect) {
    case RGB_MATRIX_NONE:
      rendering = rgb_matrix_none(&rgb_effect_params);
      break;

    case RGB_MATRIX_SOLID_COLOR:
      rendering = rgb_matrix_solid_color(&rgb_effect_params);           // Max 1ms Avg 0ms
      break;
#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
    case RGB_MATRIX_ALPHAS_MODS:
      rendering = rgb_matrix_alphas_mods(&rgb_effect_params);           // Max 2ms Avg 1ms
      break;
#endif // DISABLE_RGB_MATRIX_ALPHAS_MODS
#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    case RGB_MATRIX_GRADIENT_UP_DOWN:
      rendering = rgb_matrix_gradient_up_down(&rgb_effect_params);      // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#ifndef DISABLE_RGB_MATRIX_BREATHING
    case RGB_MATRIX_BREATHING:
      rendering = rgb_matrix_breathing(&rgb_effect_params);             // Max 1ms Avg 0ms
      break;
#endif // DISABLE_RGB_MATRIX_BREATHING
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
    case RGB_MATRIX_CYCLE_ALL:
      rendering = rgb_matrix_cycle_all(&rgb_effect_params);             // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_CYCLE_ALL
#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    case RGB_MATRIX_CYCLE_LEFT_RIGHT:
      rendering = rgb_matrix_cycle_left_right(&rgb_effect_params);      // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
    case RGB_MATRIX_CYCLE_UP_DOWN:
      rendering = rgb_matrix_cycle_up_down(&rgb_effect_params);         // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
      rendering = rgb_matrix_rainbow_moving_chevron(&rgb_effect_params); // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
    case RGB_MATRIX_DUAL_BEACON:
      rendering = rgb_matrix_dual_beacon(&rgb_effect_params);           // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_DUAL_BEACON
#ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
    case RGB_MATRIX_RAINBOW_BEACON:
      rendering = rgb_matrix_rainbow_beacon(&rgb_effect_params);        // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_RAINBOW_BEACON
#ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    case RGB_MATRIX_RAINBOW_PINWHEELS:
      rendering = rgb_matrix_rainbow_pinwheels(&rgb_effect_params);     // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#ifndef DISABLE_RGB_MATRIX_RAINDROPS
    case RGB_MATRIX_RAINDROPS:
      rendering = rgb_matrix_raindrops(&rgb_effect_params);             // Max 1ms Avg 0ms
      break;
#endif // DISABLE_RGB_MATRIX_RAINDROPS
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    case RGB_MATRIX_JELLYBEAN_RAINDROPS:
      rendering = rgb_matrix_jellybean_raindrops(&rgb_effect_params);   // Max 1ms Avg 0ms
      break;
#endif // DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#ifndef DISABLE_RGB_MATRIX_DIGITAL_RAIN
    case RGB_MATRIX_DIGITAL_RAIN:
      rendering = rgb_matrix_digital_rain(&rgb_effect_params);         // Max 9ms Avg 8ms | this is expensive, fix it
      break;
#endif // DISABLE_RGB_MATRIX_DIGITAL_RAIN
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
      rendering = rgb_matrix_solid_reactive_simple(&rgb_effect_params);// Max 4ms Avg 3ms
      break;
#endif
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
    case RGB_MATRIX_SOLID_REACTIVE:
      rendering = rgb_matrix_solid_reactive(&rgb_effect_params);       // Max 4ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    case RGB_MATRIX_SOLID_REACTIVE_WIDE:
      rendering = rgb_matrix_solid_reactive_wide(&rgb_effect_params);       // Max ?? ms Avg ?? ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE:
      rendering = rgb_matrix_solid_reactive_multiwide(&rgb_effect_params);       // Max ?? ms Avg ?? ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    case RGB_MATRIX_SOLID_REACTIVE_CROSS:
      rendering = rgb_matrix_solid_reactive_cross(&rgb_effect_params);       // Max ?? ms Avg ?? ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS:
      rendering = rgb_matrix_solid_reactive_multicross(&rgb_effect_params);       // Max ?? ms Avg ?? ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    case RGB_MATRIX_SOLID_REACTIVE_NEXUS:
      rendering = rgb_matrix_solid_reactive_nexus(&rgb_effect_params);       // Max ?? ms Avg ?? ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:
      rendering = rgb_matrix_solid_reactive_multinexus(&rgb_effect_params);       // Max ?? ms Avg ?? ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#ifndef DISABLE_RGB_MATRIX_SPLASH
    case RGB_MATRIX_SPLASH:
      rendering = rgb_matrix_splash(&rgb_effect_params);               // Max 5ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_SPLASH
#ifndef DISABLE_RGB_MATRIX_MULTISPLASH
    case RGB_MATRIX_MULTISPLASH:
      rendering = rgb_matrix_multisplash(&rgb_effect_params);          // Max 10ms Avg 5ms
      break;
#endif // DISABLE_RGB_MATRIX_MULTISPLASH
#ifndef DISABLE_RGB_MATRIX_SOLID_SPLASH
    case RGB_MATRIX_SOLID_SPLASH:
      rendering = rgb_matrix_solid_splash(&rgb_effect_params);         // Max 5ms Avg 3ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_SPLASH
#ifndef DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
    case RGB_MATRIX_SOLID_MULTISPLASH:
      rendering = rgb_matrix_solid_multisplash(&rgb_effect_params);    // Max 10ms Avg 5ms
      break;
#endif // DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED

    // Factory default magic value
    case UINT8_MAX: {
        rgb_matrix_test();
        rgb_task_state = FLUSHING;
      }
      return;
  }

  rgb_effect_params.iter++;

  // next task
  if (!rendering) {
    rgb_task_state = FLUSHING;
    if (!rgb_effect_params.init && effect == RGB_MATRIX_NONE) {
      // We only need to flush once if we are RGB_MATRIX_NONE
      rgb_task_state = SYNCING;
    }
  }
}

static void rgb_task_flush(uint8_t effect) {
  // update last trackers after the first full render so we can init over several frames
  rgb_last_effect = effect;
  rgb_last_enable = rgb_matrix_config.enable;

  // update pwm buffers
  rgb_matrix_update_pwm_buffers();

  // next task
  rgb_task_state = SYNCING;
}

void rgb_matrix_task(void) {
  rgb_task_timers();

  // Ideally we would also stop sending zeros to the LED driver PWM buffers
  // while suspended and just do a software shutdown. This is a cheap hack for now.
  bool suspend_backlight = ((g_suspend_state && RGB_DISABLE_WHEN_USB_SUSPENDED) || (RGB_DISABLE_AFTER_TIMEOUT > 0 && g_rgb_counters.any_key_hit > RGB_DISABLE_AFTER_TIMEOUT * 60 * 20));
  uint8_t effect = suspend_backlight || !rgb_matrix_config.enable ? 0 : rgb_matrix_config.mode;

  switch (rgb_task_state) {
    case STARTING:
      rgb_task_start();
      break;
    case RENDERING:
      rgb_task_render(effect);
      break;
    case FLUSHING:
      rgb_task_flush(effect);
      break;
    case SYNCING:
      rgb_task_sync();
      break;
  }

  if (!suspend_backlight) {
    rgb_matrix_indicators();
  }
}

void rgb_matrix_indicators(void) {
  rgb_matrix_indicators_kb();
  rgb_matrix_indicators_user();
}

__attribute__((weak))
void rgb_matrix_indicators_kb(void) {}

__attribute__((weak))
void rgb_matrix_indicators_user(void) {}

void rgb_matrix_init(void) {
  rgb_matrix_driver.init();

  // TODO: put the 1 second startup delay here?

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
  g_last_hit_tracker.count = 0;
  for (uint8_t i = 0; i < LED_HITS_TO_REMEMBER; ++i) {
    g_last_hit_tracker.tick[i] = UINT16_MAX;
  }

  last_hit_buffer.count = 0;
  for (uint8_t i = 0; i < LED_HITS_TO_REMEMBER; ++i) {
    last_hit_buffer.tick[i] = UINT16_MAX;
  }
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED

  if (!eeconfig_is_enabled()) {
    dprintf("rgb_matrix_init_drivers eeconfig is not enabled.\n");
    eeconfig_init();
    eeconfig_update_rgb_matrix_default();
  }

  rgb_matrix_config.raw = eeconfig_read_rgb_matrix();
  rgb_matrix_config.speed = UINT8_MAX / 2; //EECONFIG needs to be increased to support this
  if (!rgb_matrix_config.mode) {
    dprintf("rgb_matrix_init_drivers rgb_matrix_config.mode = 0. Write default values to EEPROM.\n");
    eeconfig_update_rgb_matrix_default();
    rgb_matrix_config.raw = eeconfig_read_rgb_matrix();
  }
  eeconfig_debug_rgb_matrix(); // display current eeprom values
}

void rgb_matrix_set_suspend_state(bool state) {
  g_suspend_state = state;
}

void rgb_matrix_toggle(void) {
  rgb_matrix_config.enable++;
  if (!rgb_matrix_config.enable) {
    rgb_task_state = STARTING;
  }
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_enable(void) {
	rgb_matrix_config.enable = 1;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_enable_noeeprom(void) {
	rgb_matrix_config.enable = 1;
}

void rgb_matrix_disable(void) {
	rgb_matrix_config.enable = 0;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_disable_noeeprom(void) {
	rgb_matrix_config.enable = 0;
}

void rgb_matrix_step(void) {
  rgb_matrix_config.mode++;
  if (rgb_matrix_config.mode >= RGB_MATRIX_EFFECT_MAX)
    rgb_matrix_config.mode = 1;
  rgb_task_state = STARTING;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_step_reverse(void) {
  rgb_matrix_config.mode--;
  if (rgb_matrix_config.mode < 1)
    rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX - 1;
  rgb_task_state = STARTING;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_hue(void) {
  rgb_matrix_config.hue += RGB_MATRIX_HUE_STEP;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_hue(void) {
  rgb_matrix_config.hue -= RGB_MATRIX_HUE_STEP;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_sat(void) {
  rgb_matrix_config.sat = qadd8(rgb_matrix_config.sat, RGB_MATRIX_SAT_STEP);
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_sat(void) {
  rgb_matrix_config.sat = qsub8(rgb_matrix_config.sat, RGB_MATRIX_SAT_STEP);
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_val(void) {
  rgb_matrix_config.val = qadd8(rgb_matrix_config.val, RGB_MATRIX_VAL_STEP);
  if (rgb_matrix_config.val > RGB_MATRIX_MAXIMUM_BRIGHTNESS)
    rgb_matrix_config.val = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_val(void) {
  rgb_matrix_config.val = qsub8(rgb_matrix_config.val, RGB_MATRIX_VAL_STEP);
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_speed(void) {
  rgb_matrix_config.speed = qadd8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP);
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);//EECONFIG needs to be increased to support this
}

void rgb_matrix_decrease_speed(void) {
  rgb_matrix_config.speed = qsub8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP);
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);//EECONFIG needs to be increased to support this
}

void rgb_matrix_mode(uint8_t mode) {
  rgb_matrix_config.mode = mode;
  rgb_task_state = STARTING;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_mode_noeeprom(uint8_t mode) {
  rgb_matrix_config.mode = mode;
}

uint8_t rgb_matrix_get_mode(void) {
  return rgb_matrix_config.mode;
}

void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val) {
  rgb_matrix_sethsv_noeeprom(hue, sat, val);
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) {
  rgb_matrix_config.hue = hue;
  rgb_matrix_config.sat = sat;
  rgb_matrix_config.val = val;
  if (rgb_matrix_config.val > RGB_MATRIX_MAXIMUM_BRIGHTNESS)
    rgb_matrix_config.val = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
}
