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

#include <lib/lib8tion/lib8tion.h>

#ifndef RGB_MATRIX_CENTER
const led_point_t k_rgb_matrix_center = {112, 32};
#else
const led_point_t k_rgb_matrix_center = RGB_MATRIX_CENTER;
#endif

__attribute__((weak)) RGB rgb_matrix_hsv_to_rgb(HSV hsv) { return hsv_to_rgb(hsv); }

// Generic effect runners
#include "rgb_matrix_runners.inc"

// ------------------------------------------
// -----Begin rgb effect includes macros-----
#define RGB_MATRIX_EFFECT(name)
#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "rgb_matrix_effects.inc"
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

#if defined(RGB_DISABLE_AFTER_TIMEOUT) && !defined(RGB_DISABLE_TIMEOUT)
#    define RGB_DISABLE_TIMEOUT (RGB_DISABLE_AFTER_TIMEOUT * 1200UL)
#endif

#ifndef RGB_DISABLE_TIMEOUT
#    define RGB_DISABLE_TIMEOUT 0
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
#    ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
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

// globals
rgb_config_t rgb_matrix_config;  // TODO: would like to prefix this with g_ for global consistancy, do this in another pr
uint32_t     g_rgb_timer;
#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
uint8_t g_rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS] = {{0}};
#endif  // RGB_MATRIX_FRAMEBUFFER_EFFECTS
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
last_hit_t g_last_hit_tracker;
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

// internals
static bool            suspend_state     = false;
static uint8_t         rgb_last_enable   = UINT8_MAX;
static uint8_t         rgb_last_effect   = UINT8_MAX;
static effect_params_t rgb_effect_params = {0, LED_FLAG_ALL, false};
static rgb_task_states rgb_task_state    = SYNCING;
#if RGB_DISABLE_TIMEOUT > 0
static uint32_t rgb_anykey_timer;
#endif  // RGB_DISABLE_TIMEOUT > 0

// double buffers
static uint32_t rgb_timer_buffer;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
static last_hit_t last_hit_buffer;
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

// split rgb matrix
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
const uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
#endif

EECONFIG_DEBOUNCE_HELPER(rgb_matrix, EECONFIG_RGB_MATRIX, rgb_matrix_config);

void eeconfig_update_rgb_matrix(void) { eeconfig_flush_rgb_matrix(true); }

void eeconfig_update_rgb_matrix_default(void) {
    dprintf("eeconfig_update_rgb_matrix_default\n");
    rgb_matrix_config.enable = 1;
    rgb_matrix_config.mode   = RGB_MATRIX_STARTUP_MODE;
    rgb_matrix_config.hsv    = (HSV){RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL};
    rgb_matrix_config.speed  = RGB_MATRIX_STARTUP_SPD;
    rgb_matrix_config.flags  = LED_FLAG_ALL;
    eeconfig_flush_rgb_matrix(true);
}

void eeconfig_debug_rgb_matrix(void) {
    dprintf("rgb_matrix_config EEPROM\n");
    dprintf("rgb_matrix_config.enable = %d\n", rgb_matrix_config.enable);
    dprintf("rgb_matrix_config.mode = %d\n", rgb_matrix_config.mode);
    dprintf("rgb_matrix_config.hsv.h = %d\n", rgb_matrix_config.hsv.h);
    dprintf("rgb_matrix_config.hsv.s = %d\n", rgb_matrix_config.hsv.s);
    dprintf("rgb_matrix_config.hsv.v = %d\n", rgb_matrix_config.hsv.v);
    dprintf("rgb_matrix_config.speed = %d\n", rgb_matrix_config.speed);
    dprintf("rgb_matrix_config.flags = %d\n", rgb_matrix_config.flags);
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

void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) { rgb_matrix_driver.set_color(index, red, green, blue); }

void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) rgb_matrix_set_color(i, red, green, blue);
#else
    rgb_matrix_driver.set_color_all(red, green, blue);
#endif
}

void process_rgb_matrix(uint8_t row, uint8_t col, bool pressed) {
#ifndef RGB_MATRIX_SPLIT
    if (!is_keyboard_master()) return;
#endif
#if RGB_DISABLE_TIMEOUT > 0
    rgb_anykey_timer = 0;
#endif  // RGB_DISABLE_TIMEOUT > 0

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = 0;

#    if defined(RGB_MATRIX_KEYRELEASES)
    if (!pressed)
#    elif defined(RGB_MATRIX_KEYPRESSES)
    if (pressed)
#    endif  // defined(RGB_MATRIX_KEYRELEASES)
    {
        led_count = rgb_matrix_map_row_column_to_led(row, col, led);
    }

    if (last_hit_buffer.count + led_count > LED_HITS_TO_REMEMBER) {
        memcpy(&last_hit_buffer.x[0], &last_hit_buffer.x[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.y[0], &last_hit_buffer.y[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.tick[0], &last_hit_buffer.tick[led_count], (LED_HITS_TO_REMEMBER - led_count) * 2);  // 16 bit
        memcpy(&last_hit_buffer.index[0], &last_hit_buffer.index[led_count], LED_HITS_TO_REMEMBER - led_count);
        last_hit_buffer.count = LED_HITS_TO_REMEMBER - led_count;
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

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
    if (rgb_matrix_config.mode == RGB_MATRIX_TYPING_HEATMAP) {
        process_rgb_matrix_typing_heatmap(row, col);
    }
#endif  // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
}

void rgb_matrix_test(void) {
    // Mask out bits 4 and 5
    // Increase the factor to make the test animation slower (and reduce to make it faster)
    uint8_t factor = 10;
    switch ((g_rgb_timer & (0b11 << factor)) >> factor) {
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

    rgb_matrix_set_color_all(0, 0, 0);
    return false;
}

static void rgb_task_timers(void) {
#if defined(RGB_MATRIX_KEYREACTIVE_ENABLED) || RGB_DISABLE_TIMEOUT > 0
    uint32_t deltaTime = sync_timer_elapsed32(rgb_timer_buffer);
#endif  // defined(RGB_MATRIX_KEYREACTIVE_ENABLED) || RGB_DISABLE_TIMEOUT > 0
    rgb_timer_buffer = sync_timer_read32();

    // Update double buffer timers
#if RGB_DISABLE_TIMEOUT > 0
    if (rgb_anykey_timer + deltaTime <= UINT32_MAX) {
        rgb_anykey_timer += deltaTime;
    }
#endif  // RGB_DISABLE_TIMEOUT > 0

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
    eeconfig_flush_rgb_matrix(false);
    // next task
    if (sync_timer_elapsed32(g_rgb_timer) >= RGB_MATRIX_LED_FLUSH_LIMIT) rgb_task_state = STARTING;
}

static void rgb_task_start(void) {
    // reset iter
    rgb_effect_params.iter = 0;

    // update double buffers
    g_rgb_timer = rgb_timer_buffer;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    g_last_hit_tracker = last_hit_buffer;
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

    // next task
    rgb_task_state = RENDERING;
}

static void rgb_task_render(uint8_t effect) {
    bool rendering         = false;
    rgb_effect_params.init = (effect != rgb_last_effect) || (rgb_matrix_config.enable != rgb_last_enable);
    if (rgb_effect_params.flags != rgb_matrix_config.flags) {
        rgb_effect_params.flags = rgb_matrix_config.flags;
        rgb_matrix_set_color_all(0, 0, 0);
    }

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
#include "rgb_matrix_effects.inc"
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
    bool suspend_backlight = suspend_state ||
#if RGB_DISABLE_TIMEOUT > 0
                             (rgb_anykey_timer > (uint32_t)RGB_DISABLE_TIMEOUT) ||
#endif  // RGB_DISABLE_TIMEOUT > 0
                             false;

    uint8_t effect = suspend_backlight || !rgb_matrix_config.enable ? 0 : rgb_matrix_config.mode;

    switch (rgb_task_state) {
        case STARTING:
            rgb_task_start();
            break;
        case RENDERING:
            rgb_task_render(effect);
            if (effect) {
                rgb_matrix_indicators();
                rgb_matrix_indicators_advanced(&rgb_effect_params);
            }
            break;
        case FLUSHING:
            rgb_task_flush(effect);
            break;
        case SYNCING:
            rgb_task_sync();
            break;
    }
}

void rgb_matrix_indicators(void) {
    rgb_matrix_indicators_kb();
    rgb_matrix_indicators_user();
}

__attribute__((weak)) void rgb_matrix_indicators_kb(void) {}

__attribute__((weak)) void rgb_matrix_indicators_user(void) {}

void rgb_matrix_indicators_advanced(effect_params_t *params) {
    /* special handling is needed for "params->iter", since it's already been incremented.
     * Could move the invocations to rgb_task_render, but then it's missing a few checks
     * and not sure which would be better. Otherwise, this should be called from
     * rgb_task_render, right before the iter++ line.
     */
#if defined(RGB_MATRIX_LED_PROCESS_LIMIT) && RGB_MATRIX_LED_PROCESS_LIMIT > 0 && RGB_MATRIX_LED_PROCESS_LIMIT < DRIVER_LED_TOTAL
    uint8_t min = RGB_MATRIX_LED_PROCESS_LIMIT * (params->iter - 1);
    uint8_t max = min + RGB_MATRIX_LED_PROCESS_LIMIT;
    if (max > DRIVER_LED_TOTAL) max = DRIVER_LED_TOTAL;
#else
    uint8_t min = 0;
    uint8_t max = DRIVER_LED_TOTAL;
#endif
    rgb_matrix_indicators_advanced_kb(min, max);
    rgb_matrix_indicators_advanced_user(min, max);
}

__attribute__((weak)) void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {}

__attribute__((weak)) void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {}

void rgb_matrix_init(void) {
    rgb_matrix_driver.init();

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

    eeconfig_init_rgb_matrix();
    if (!rgb_matrix_config.mode) {
        dprintf("rgb_matrix_init_drivers rgb_matrix_config.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_rgb_matrix_default();
    }
    eeconfig_debug_rgb_matrix();  // display current eeprom values
}

void rgb_matrix_set_suspend_state(bool state) {
#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
    if (state && !suspend_state) {  // only run if turning off, and only once
        rgb_task_render(0);         // turn off all LEDs when suspending
        rgb_task_flush(0);          // and actually flash led state to LEDs
    }
    suspend_state = state;
#endif
}

bool rgb_matrix_get_suspend_state(void) { return suspend_state; }

void rgb_matrix_toggle_eeprom_helper(bool write_to_eeprom) {
    rgb_matrix_config.enable ^= 1;
    rgb_task_state = STARTING;
    eeconfig_flag_rgb_matrix(write_to_eeprom);
    dprintf("rgb matrix toggle [%s]: rgb_matrix_config.enable = %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", rgb_matrix_config.enable);
}
void rgb_matrix_toggle_noeeprom(void) { rgb_matrix_toggle_eeprom_helper(false); }
void rgb_matrix_toggle(void) { rgb_matrix_toggle_eeprom_helper(true); }

void rgb_matrix_enable(void) {
    rgb_matrix_enable_noeeprom();
    eeconfig_flag_rgb_matrix(true);
}

void rgb_matrix_enable_noeeprom(void) {
    if (!rgb_matrix_config.enable) rgb_task_state = STARTING;
    rgb_matrix_config.enable = 1;
}

void rgb_matrix_disable(void) {
    rgb_matrix_disable_noeeprom();
    eeconfig_flag_rgb_matrix(true);
}

void rgb_matrix_disable_noeeprom(void) {
    if (rgb_matrix_config.enable) rgb_task_state = STARTING;
    rgb_matrix_config.enable = 0;
}

uint8_t rgb_matrix_is_enabled(void) { return rgb_matrix_config.enable; }

void rgb_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
    if (!rgb_matrix_config.enable) {
        return;
    }
    if (mode < 1) {
        rgb_matrix_config.mode = 1;
    } else if (mode >= RGB_MATRIX_EFFECT_MAX) {
        rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX - 1;
    } else {
        rgb_matrix_config.mode = mode;
    }
    rgb_task_state = STARTING;
    eeconfig_flag_rgb_matrix(write_to_eeprom);
    dprintf("rgb matrix mode [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", rgb_matrix_config.mode);
}
void rgb_matrix_mode_noeeprom(uint8_t mode) { rgb_matrix_mode_eeprom_helper(mode, false); }
void rgb_matrix_mode(uint8_t mode) { rgb_matrix_mode_eeprom_helper(mode, true); }

uint8_t rgb_matrix_get_mode(void) { return rgb_matrix_config.mode; }

void rgb_matrix_step_helper(bool write_to_eeprom) {
    uint8_t mode = rgb_matrix_config.mode + 1;
    rgb_matrix_mode_eeprom_helper((mode < RGB_MATRIX_EFFECT_MAX) ? mode : 1, write_to_eeprom);
}
void rgb_matrix_step_noeeprom(void) { rgb_matrix_step_helper(false); }
void rgb_matrix_step(void) { rgb_matrix_step_helper(true); }

void rgb_matrix_step_reverse_helper(bool write_to_eeprom) {
    uint8_t mode = rgb_matrix_config.mode - 1;
    rgb_matrix_mode_eeprom_helper((mode < 1) ? RGB_MATRIX_EFFECT_MAX - 1 : mode, write_to_eeprom);
}
void rgb_matrix_step_reverse_noeeprom(void) { rgb_matrix_step_reverse_helper(false); }
void rgb_matrix_step_reverse(void) { rgb_matrix_step_reverse_helper(true); }

void rgb_matrix_sethsv_eeprom_helper(uint16_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom) {
    if (!rgb_matrix_config.enable) {
        return;
    }
    rgb_matrix_config.hsv.h = hue;
    rgb_matrix_config.hsv.s = sat;
    rgb_matrix_config.hsv.v = (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : val;
    eeconfig_flag_rgb_matrix(write_to_eeprom);
    dprintf("rgb matrix set hsv [%s]: %u,%u,%u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
}
void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) { rgb_matrix_sethsv_eeprom_helper(hue, sat, val, false); }
void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val) { rgb_matrix_sethsv_eeprom_helper(hue, sat, val, true); }

HSV     rgb_matrix_get_hsv(void) { return rgb_matrix_config.hsv; }
uint8_t rgb_matrix_get_hue(void) { return rgb_matrix_config.hsv.h; }
uint8_t rgb_matrix_get_sat(void) { return rgb_matrix_config.hsv.s; }
uint8_t rgb_matrix_get_val(void) { return rgb_matrix_config.hsv.v; }

void rgb_matrix_increase_hue_helper(bool write_to_eeprom) { rgb_matrix_sethsv_eeprom_helper(rgb_matrix_config.hsv.h + RGB_MATRIX_HUE_STEP, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, write_to_eeprom); }
void rgb_matrix_increase_hue_noeeprom(void) { rgb_matrix_increase_hue_helper(false); }
void rgb_matrix_increase_hue(void) { rgb_matrix_increase_hue_helper(true); }

void rgb_matrix_decrease_hue_helper(bool write_to_eeprom) { rgb_matrix_sethsv_eeprom_helper(rgb_matrix_config.hsv.h - RGB_MATRIX_HUE_STEP, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, write_to_eeprom); }
void rgb_matrix_decrease_hue_noeeprom(void) { rgb_matrix_decrease_hue_helper(false); }
void rgb_matrix_decrease_hue(void) { rgb_matrix_decrease_hue_helper(true); }

void rgb_matrix_increase_sat_helper(bool write_to_eeprom) { rgb_matrix_sethsv_eeprom_helper(rgb_matrix_config.hsv.h, qadd8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP), rgb_matrix_config.hsv.v, write_to_eeprom); }
void rgb_matrix_increase_sat_noeeprom(void) { rgb_matrix_increase_sat_helper(false); }
void rgb_matrix_increase_sat(void) { rgb_matrix_increase_sat_helper(true); }

void rgb_matrix_decrease_sat_helper(bool write_to_eeprom) { rgb_matrix_sethsv_eeprom_helper(rgb_matrix_config.hsv.h, qsub8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP), rgb_matrix_config.hsv.v, write_to_eeprom); }
void rgb_matrix_decrease_sat_noeeprom(void) { rgb_matrix_decrease_sat_helper(false); }
void rgb_matrix_decrease_sat(void) { rgb_matrix_decrease_sat_helper(true); }

void rgb_matrix_increase_val_helper(bool write_to_eeprom) { rgb_matrix_sethsv_eeprom_helper(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, qadd8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP), write_to_eeprom); }
void rgb_matrix_increase_val_noeeprom(void) { rgb_matrix_increase_val_helper(false); }
void rgb_matrix_increase_val(void) { rgb_matrix_increase_val_helper(true); }

void rgb_matrix_decrease_val_helper(bool write_to_eeprom) { rgb_matrix_sethsv_eeprom_helper(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, qsub8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP), write_to_eeprom); }
void rgb_matrix_decrease_val_noeeprom(void) { rgb_matrix_decrease_val_helper(false); }
void rgb_matrix_decrease_val(void) { rgb_matrix_decrease_val_helper(true); }

void rgb_matrix_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom) {
    rgb_matrix_config.speed = speed;
    eeconfig_flag_rgb_matrix(write_to_eeprom);
    dprintf("rgb matrix set speed [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", rgb_matrix_config.speed);
}
void rgb_matrix_set_speed_noeeprom(uint8_t speed) { rgb_matrix_set_speed_eeprom_helper(speed, false); }
void rgb_matrix_set_speed(uint8_t speed) { rgb_matrix_set_speed_eeprom_helper(speed, true); }

uint8_t rgb_matrix_get_speed(void) { return rgb_matrix_config.speed; }

void rgb_matrix_increase_speed_helper(bool write_to_eeprom) { rgb_matrix_set_speed_eeprom_helper(qadd8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP), write_to_eeprom); }
void rgb_matrix_increase_speed_noeeprom(void) { rgb_matrix_increase_speed_helper(false); }
void rgb_matrix_increase_speed(void) { rgb_matrix_increase_speed_helper(true); }

void rgb_matrix_decrease_speed_helper(bool write_to_eeprom) { rgb_matrix_set_speed_eeprom_helper(qsub8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP), write_to_eeprom); }
void rgb_matrix_decrease_speed_noeeprom(void) { rgb_matrix_decrease_speed_helper(false); }
void rgb_matrix_decrease_speed(void) { rgb_matrix_decrease_speed_helper(true); }

led_flags_t rgb_matrix_get_flags(void) { return rgb_matrix_config.flags; }

void rgb_matrix_set_flags(led_flags_t flags) { rgb_matrix_config.flags = flags; }
