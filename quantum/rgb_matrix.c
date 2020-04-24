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

#ifndef RGB_MATRIX_CENTER
const point_t k_rgb_matrix_center = {112, 32};
#else
const point_t k_rgb_matrix_center = RGB_MATRIX_CENTER;
#endif

// Generic effect runners
#include "rgb_matrix_runners/effect_runner_dx_dy_dist.h"
#include "rgb_matrix_runners/effect_runner_dx_dy.h"
#include "rgb_matrix_runners/effect_runner_i.h"
#include "rgb_matrix_runners/effect_runner_sin_cos_i.h"
#include "rgb_matrix_runners/effect_runner_reactive.h"
#include "rgb_matrix_runners/effect_runner_reactive_splash.h"

// ------------------------------------------
// -----Begin rgb effect includes macros-----
#define RGB_MATRIX_EFFECT(name)
#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "rgb_matrix_animations/rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif

#undef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#undef RGB_MATRIX_EFFECT
// -----End rgb effect includes macros-------
// ------------------------------------------

#ifndef RGB_DISABLE_AFTER_TIMEOUT
#    define RGB_DISABLE_AFTER_TIMEOUT 0
#endif

#ifndef RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_DISABLE_WHEN_USB_SUSPENDED false
#endif

#if !defined(RGB_MATRIX_MAXIMUM_BRIGHTNESS) || RGB_MATRIX_MAXIMUM_BRIGHTNESS > UINT8_MAX
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

#if !defined(RGB_MATRIX_HUE_STEP)
#    define RGB_MATRIX_HUE_STEP 8
#endif

#if !defined(RGB_MATRIX_SAT_STEP)
#    define RGB_MATRIX_SAT_STEP 16
#endif

#if !defined(RGB_MATRIX_VAL_STEP)
#    define RGB_MATRIX_VAL_STEP 16
#endif

#if !defined(RGB_MATRIX_SPD_STEP)
#    define RGB_MATRIX_SPD_STEP 16
#endif

#if !defined(RGB_MATRIX_STARTUP_MODE)
#    ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    else
// fallback to solid colors if RGB_MATRIX_CYCLE_LEFT_RIGHT is disabled in userspace
#        define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#    endif
#endif

#if !defined(RGB_MATRIX_STARTUP_HUE)
#    define RGB_MATRIX_STARTUP_HUE 0
#endif

#if !defined(RGB_MATRIX_STARTUP_SAT)
#    define RGB_MATRIX_STARTUP_SAT UINT8_MAX
#endif

#if !defined(RGB_MATRIX_STARTUP_VAL)
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#if !defined(RGB_MATRIX_STARTUP_SPD)
#    define RGB_MATRIX_STARTUP_SPD UINT8_MAX / 2
#endif

bool g_suspend_state = false;

rgb_config_t rgb_matrix_config;

rgb_counters_t  g_rgb_counters;
static uint32_t rgb_counters_buffer;

#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
uint8_t rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS] = {{0}};
#endif

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
last_hit_t        g_last_hit_tracker;
static last_hit_t last_hit_buffer;
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

// Extern driver internally, driver should not be used directly
extern const rgb_matrix_driver_t rgb_matrix_driver;

#ifdef RGB_MATRIX_SPLIT
const uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
#endif

void eeconfig_read_rgb_matrix(void) { eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config)); }

void eeconfig_update_rgb_matrix(void) { eeprom_update_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config)); }

void eeconfig_update_rgb_matrix_default(void) {
    dprintf("eeconfig_update_rgb_matrix_default\n");
    rgb_matrix_config.enable = 1;
    rgb_matrix_config.mode   = RGB_MATRIX_STARTUP_MODE;
    rgb_matrix_config.hsv    = (HSV){RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL};
    rgb_matrix_config.speed  = RGB_MATRIX_STARTUP_SPD;
    eeconfig_update_rgb_matrix();
}

void eeconfig_debug_rgb_matrix(void) {
    dprintf("rgb_matrix_config eprom\n");
    dprintf("rgb_matrix_config.enable = %d\n", rgb_matrix_config.enable);
    dprintf("rgb_matrix_config.mode = %d\n", rgb_matrix_config.mode);
    dprintf("rgb_matrix_config.hsv.h = %d\n", rgb_matrix_config.hsv.h);
    dprintf("rgb_matrix_config.hsv.s = %d\n", rgb_matrix_config.hsv.s);
    dprintf("rgb_matrix_config.hsv.v = %d\n", rgb_matrix_config.hsv.v);
    dprintf("rgb_matrix_config.speed = %d\n", rgb_matrix_config.speed);
}

__attribute__((weak)) uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) { return 0; }

uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i) {
    uint8_t led_count = rgb_matrix_map_row_column_to_led_kb(row, column, led_i);
    uint8_t led_index = g_led_config.matrix_co[row][column];
    if (led_index != NO_LED) {
        led_i[led_count] = led_index;
        led_count++;
    }
    return led_count;
}

void rgb_matrix_update_pwm_buffers(void) { rgb_matrix_driver.flush(); }

void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
#ifdef RGB_MATRIX_SPLIT
    if (!is_keyboard_left() && index >= k_rgb_matrix_split[0])
        rgb_matrix_driver.set_color(index - k_rgb_matrix_split[0], red, green, blue);
    else if (is_keyboard_left() && index < k_rgb_matrix_split[0])
#endif
    rgb_matrix_driver.set_color(index, red, green, blue);
}

void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
#ifdef RGB_MATRIX_SPLIT
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
        rgb_matrix_set_color(i, red, green, blue);
#else
    rgb_matrix_driver.set_color_all(red, green, blue);
#endif
}

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = 0;

#    if defined(RGB_MATRIX_KEYRELEASES)
    if (!record->event.pressed) {
        led_count                  = rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led);
        g_rgb_counters.any_key_hit = 0;
    }
#    elif defined(RGB_MATRIX_KEYPRESSES)
    if (record->event.pressed) {
        led_count                  = rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led);
        g_rgb_counters.any_key_hit = 0;
    }
#    endif  // defined(RGB_MATRIX_KEYRELEASES)

    if (last_hit_buffer.count + led_count > LED_HITS_TO_REMEMBER) {
        memcpy(&last_hit_buffer.x[0], &last_hit_buffer.x[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.y[0], &last_hit_buffer.y[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.tick[0], &last_hit_buffer.tick[led_count], (LED_HITS_TO_REMEMBER - led_count) * 2);  // 16 bit
        memcpy(&last_hit_buffer.index[0], &last_hit_buffer.index[led_count], LED_HITS_TO_REMEMBER - led_count);
        last_hit_buffer.count--;
    }

    for (uint8_t i = 0; i < led_count; i++) {
        uint8_t index                = last_hit_buffer.count;
        last_hit_buffer.x[index]     = g_led_config.point[led[i]].x;
        last_hit_buffer.y[index]     = g_led_config.point[led[i]].y;
        last_hit_buffer.index[index] = led[i];
        last_hit_buffer.tick[index]  = 0;
        last_hit_buffer.count++;
    }
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)
    if (rgb_matrix_config.mode == RGB_MATRIX_TYPING_HEATMAP) {
        process_rgb_matrix_typing_heatmap(record);
    }
#endif  // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)

    return true;
}

void rgb_matrix_test(void) {
    // Mask out bits 4 and 5
    // Increase the factor to make the test animation slower (and reduce to make it faster)
    uint8_t factor = 10;
    switch ((g_rgb_counters.tick & (0b11 << factor)) >> factor) {
        case 0: {
            rgb_matrix_set_color_all(20, 0, 0);
            break;
        }
        case 1: {
            rgb_matrix_set_color_all(0, 20, 0);
            break;
        }
        case 2: {
            rgb_matrix_set_color_all(0, 0, 20);
            break;
        }
        case 3: {
            rgb_matrix_set_color_all(20, 20, 20);
            break;
        }
    }
}

static bool rgb_matrix_none(effect_params_t *params) {
    if (!params->init) {
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    return led_max < DRIVER_LED_TOTAL;
}

static uint8_t         rgb_last_enable   = UINT8_MAX;
static uint8_t         rgb_last_effect   = UINT8_MAX;
static effect_params_t rgb_effect_params = {0, 0xFF};
static rgb_task_states rgb_task_state    = SYNCING;

static void rgb_task_timers(void) {
    // Update double buffer timers
    uint16_t deltaTime  = sync_timer_elapsed32(rgb_counters_buffer);
    rgb_counters_buffer = sync_timer_read32();
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
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED
}

static void rgb_task_sync(void) {
    // next task
    if (sync_timer_elapsed32(g_rgb_counters.tick) >= RGB_MATRIX_LED_FLUSH_LIMIT) rgb_task_state = STARTING;
}

static void rgb_task_start(void) {
    // reset iter
    rgb_effect_params.iter = 0;

    // update double buffers
    g_rgb_counters.tick = rgb_counters_buffer;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    g_last_hit_tracker = last_hit_buffer;
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

    // next task
    rgb_task_state = RENDERING;
}

static void rgb_task_render(uint8_t effect) {
    bool rendering         = false;
    rgb_effect_params.init = (effect != rgb_last_effect) || (rgb_matrix_config.enable != rgb_last_enable);

    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch (effect) {
        case RGB_MATRIX_NONE:
            rendering = rgb_matrix_none(&rgb_effect_params);
            break;

// ---------------------------------------------
// -----Begin rgb effect switch case macros-----
#define RGB_MATRIX_EFFECT(name, ...)          \
    case RGB_MATRIX_##name:                   \
        rendering = name(&rgb_effect_params); \
        break;
#include "rgb_matrix_animations/rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT

#if defined(RGB_MATRIX_CUSTOM_KB) || defined(RGB_MATRIX_CUSTOM_USER)
#    define RGB_MATRIX_EFFECT(name, ...)          \
        case RGB_MATRIX_CUSTOM_##name:            \
            rendering = name(&rgb_effect_params); \
            break;
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
#    undef RGB_MATRIX_EFFECT
#endif
            // -----End rgb effect switch case macros-------
            // ---------------------------------------------

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
    bool    suspend_backlight = ((g_suspend_state && RGB_DISABLE_WHEN_USB_SUSPENDED) || (RGB_DISABLE_AFTER_TIMEOUT > 0 && g_rgb_counters.any_key_hit > RGB_DISABLE_AFTER_TIMEOUT * 60 * 20));
    uint8_t effect            = suspend_backlight || !rgb_matrix_config.enable ? 0 : rgb_matrix_config.mode;

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

__attribute__((weak)) void rgb_matrix_indicators_kb(void) {}

__attribute__((weak)) void rgb_matrix_indicators_user(void) {}

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
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

    if (!eeconfig_is_enabled()) {
        dprintf("rgb_matrix_init_drivers eeconfig is not enabled.\n");
        eeconfig_init();
        eeconfig_update_rgb_matrix_default();
    }

    eeconfig_read_rgb_matrix();
    if (!rgb_matrix_config.mode) {
        dprintf("rgb_matrix_init_drivers rgb_matrix_config.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_rgb_matrix_default();
    }
    eeconfig_debug_rgb_matrix();  // display current eeprom values
}

void rgb_matrix_set_suspend_state(bool state) {
    if (RGB_DISABLE_WHEN_USB_SUSPENDED && state) {
        rgb_matrix_set_color_all(0, 0, 0);  // turn off all LEDs when suspending
    }
    g_suspend_state = state;
}

void rgb_matrix_toggle(void) {
    rgb_matrix_config.enable ^= 1;
    rgb_task_state = STARTING;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_enable(void) {
    rgb_matrix_enable_noeeprom();
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_enable_noeeprom(void) {
    if (!rgb_matrix_config.enable) rgb_task_state = STARTING;
    rgb_matrix_config.enable = 1;
}

void rgb_matrix_disable(void) {
    rgb_matrix_disable_noeeprom();
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_disable_noeeprom(void) {
    if (rgb_matrix_config.enable) rgb_task_state = STARTING;
    rgb_matrix_config.enable = 0;
}

void rgb_matrix_step(void) {
    rgb_matrix_config.mode++;
    if (rgb_matrix_config.mode >= RGB_MATRIX_EFFECT_MAX) rgb_matrix_config.mode = 1;
    rgb_task_state = STARTING;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_step_reverse(void) {
    rgb_matrix_config.mode--;
    if (rgb_matrix_config.mode < 1) rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX - 1;
    rgb_task_state = STARTING;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_increase_hue(void) {
    rgb_matrix_config.hsv.h += RGB_MATRIX_HUE_STEP;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_decrease_hue(void) {
    rgb_matrix_config.hsv.h -= RGB_MATRIX_HUE_STEP;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_increase_sat(void) {
    rgb_matrix_config.hsv.s = qadd8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP);
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_decrease_sat(void) {
    rgb_matrix_config.hsv.s = qsub8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP);
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_increase_val(void) {
    rgb_matrix_config.hsv.v = qadd8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP);
    if (rgb_matrix_config.hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) rgb_matrix_config.hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_decrease_val(void) {
    rgb_matrix_config.hsv.v = qsub8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP);
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_increase_speed(void) {
    rgb_matrix_config.speed = qadd8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP);
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_decrease_speed(void) {
    rgb_matrix_config.speed = qsub8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP);
    eeconfig_update_rgb_matrix();
}

led_flags_t rgb_matrix_get_flags(void) { return rgb_effect_params.flags; }

void rgb_matrix_set_flags(led_flags_t flags) { rgb_effect_params.flags = flags; }

void rgb_matrix_mode(uint8_t mode) {
    rgb_matrix_config.mode = mode;
    rgb_task_state         = STARTING;
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_mode_noeeprom(uint8_t mode) { rgb_matrix_config.mode = mode; }

uint8_t rgb_matrix_get_mode(void) { return rgb_matrix_config.mode; }

void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_sethsv_noeeprom(hue, sat, val);
    eeconfig_update_rgb_matrix();
}

void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_config.hsv.h = hue;
    rgb_matrix_config.hsv.s = sat;
    rgb_matrix_config.hsv.v = val;
    if (rgb_matrix_config.hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) rgb_matrix_config.hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
}
