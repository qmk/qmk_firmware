/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Clueboard
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

#include "led_matrix.h"
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include <string.h>
#include <math.h>
#include "led_tables.h"

#include <lib/lib8tion/lib8tion.h>

#ifndef LED_MATRIX_CENTER
const led_point_t k_led_matrix_center = {112, 32};
#else
const led_point_t k_led_matrix_center = LED_MATRIX_CENTER;
#endif

// Generic effect runners
#include "led_matrix_runners.inc"

// ------------------------------------------
// -----Begin led effect includes macros-----
#define LED_MATRIX_EFFECT(name)
#define LED_MATRIX_CUSTOM_EFFECT_IMPLS

#include "led_matrix_effects.inc"
#ifdef LED_MATRIX_CUSTOM_KB
#    include "led_matrix_kb.inc"
#endif
#ifdef LED_MATRIX_CUSTOM_USER
#    include "led_matrix_user.inc"
#endif

#undef LED_MATRIX_CUSTOM_EFFECT_IMPLS
#undef LED_MATRIX_EFFECT
// -----End led effect includes macros-------
// ------------------------------------------

#if defined(LED_DISABLE_AFTER_TIMEOUT) && !defined(LED_DISABLE_TIMEOUT)
#    define LED_DISABLE_TIMEOUT (LED_DISABLE_AFTER_TIMEOUT * 1200UL)
#endif

#ifndef LED_DISABLE_TIMEOUT
#    define LED_DISABLE_TIMEOUT 0
#endif

#if !defined(LED_MATRIX_MAXIMUM_BRIGHTNESS) || LED_MATRIX_MAXIMUM_BRIGHTNESS > UINT8_MAX
#    undef LED_MATRIX_MAXIMUM_BRIGHTNESS
#    define LED_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

#if !defined(LED_MATRIX_VAL_STEP)
#    define LED_MATRIX_VAL_STEP 8
#endif

#if !defined(LED_MATRIX_SPD_STEP)
#    define LED_MATRIX_SPD_STEP 16
#endif

#if !defined(LED_MATRIX_STARTUP_MODE)
#    define LED_MATRIX_STARTUP_MODE LED_MATRIX_SOLID
#endif

#if !defined(LED_MATRIX_STARTUP_VAL)
#    define LED_MATRIX_STARTUP_VAL LED_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#if !defined(LED_MATRIX_STARTUP_SPD)
#    define LED_MATRIX_STARTUP_SPD UINT8_MAX / 2
#endif

// globals
led_eeconfig_t led_matrix_eeconfig;  // TODO: would like to prefix this with g_ for global consistancy, do this in another pr
uint32_t       g_led_timer;
#ifdef LED_MATRIX_FRAMEBUFFER_EFFECTS
uint8_t g_led_frame_buffer[MATRIX_ROWS][MATRIX_COLS] = {{0}};
#endif  // LED_MATRIX_FRAMEBUFFER_EFFECTS
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
last_hit_t g_last_hit_tracker;
#endif  // LED_MATRIX_KEYREACTIVE_ENABLED

// internals
static bool            suspend_state     = false;
static uint8_t         led_last_enable   = UINT8_MAX;
static uint8_t         led_last_effect   = UINT8_MAX;
static effect_params_t led_effect_params = {0, LED_FLAG_ALL, false};
static led_task_states led_task_state    = SYNCING;
#if LED_DISABLE_TIMEOUT > 0
static uint32_t led_anykey_timer;
#endif  // LED_DISABLE_TIMEOUT > 0

// double buffers
static uint32_t led_timer_buffer;
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
static last_hit_t last_hit_buffer;
#endif  // LED_MATRIX_KEYREACTIVE_ENABLED

// split led matrix
#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
const uint8_t k_led_matrix_split[2] = LED_MATRIX_SPLIT;
#endif

EECONFIG_DEBOUNCE_HELPER(led_matrix, EECONFIG_LED_MATRIX, led_matrix_eeconfig);

void eeconfig_update_led_matrix(void) { eeconfig_flush_led_matrix(true); }

void eeconfig_update_led_matrix_default(void) {
    dprintf("eeconfig_update_led_matrix_default\n");
    led_matrix_eeconfig.enable = 1;
    led_matrix_eeconfig.mode   = LED_MATRIX_STARTUP_MODE;
    led_matrix_eeconfig.val    = LED_MATRIX_STARTUP_VAL;
    led_matrix_eeconfig.speed  = LED_MATRIX_STARTUP_SPD;
    led_matrix_eeconfig.flags  = LED_FLAG_ALL;
    eeconfig_flush_led_matrix(true);
}

void eeconfig_debug_led_matrix(void) {
    dprintf("led_matrix_eeconfig EEPROM\n");
    dprintf("led_matrix_eeconfig.enable = %d\n", led_matrix_eeconfig.enable);
    dprintf("led_matrix_eeconfig.mode = %d\n", led_matrix_eeconfig.mode);
    dprintf("led_matrix_eeconfig.val = %d\n", led_matrix_eeconfig.val);
    dprintf("led_matrix_eeconfig.speed = %d\n", led_matrix_eeconfig.speed);
    dprintf("led_matrix_eeconfig.flags = %d\n", led_matrix_eeconfig.flags);
}

__attribute__((weak)) uint8_t led_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) { return 0; }

uint8_t led_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i) {
    uint8_t led_count = led_matrix_map_row_column_to_led_kb(row, column, led_i);
    uint8_t led_index = g_led_config.matrix_co[row][column];
    if (led_index != NO_LED) {
        led_i[led_count] = led_index;
        led_count++;
    }
    return led_count;
}

void led_matrix_update_pwm_buffers(void) { led_matrix_driver.flush(); }

void led_matrix_set_value(int index, uint8_t value) {
#ifdef USE_CIE1931_CURVE
    value = pgm_read_byte(&CIE1931_CURVE[value]);
#endif
    led_matrix_driver.set_value(index, value);
}

void led_matrix_set_value_all(uint8_t value) {
#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) led_matrix_set_value(i, value);
#else
#    ifdef USE_CIE1931_CURVE
    led_matrix_driver.set_value_all(pgm_read_byte(&CIE1931_CURVE[value]));
#    else
    led_matrix_driver.set_value_all(value);
#    endif
#endif
}

void process_led_matrix(uint8_t row, uint8_t col, bool pressed) {
#ifndef LED_MATRIX_SPLIT
    if (!is_keyboard_master()) return;
#endif
#if LED_DISABLE_TIMEOUT > 0
    led_anykey_timer = 0;
#endif  // LED_DISABLE_TIMEOUT > 0

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = 0;

#    if defined(LED_MATRIX_KEYRELEASES)
    if (!pressed)
#    elif defined(LED_MATRIX_KEYPRESSES)
    if (pressed)
#    endif  // defined(LED_MATRIX_KEYRELEASES)
    {
        led_count = led_matrix_map_row_column_to_led(row, col, led);
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
#endif  // LED_MATRIX_KEYREACTIVE_ENABLED

#if defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
    if (led_matrix_eeconfig.mode == LED_MATRIX_TYPING_HEATMAP) {
        process_led_matrix_typing_heatmap(row, col);
    }
#endif  // defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
}

static bool led_matrix_none(effect_params_t *params) {
    if (!params->init) {
        return false;
    }

    led_matrix_set_value_all(0);
    return false;
}

static void led_task_timers(void) {
#if defined(LED_MATRIX_KEYREACTIVE_ENABLED) || LED_DISABLE_TIMEOUT > 0
    uint32_t deltaTime = sync_timer_elapsed32(led_timer_buffer);
#endif  // defined(LED_MATRIX_KEYREACTIVE_ENABLED) || LED_DISABLE_TIMEOUT > 0
    led_timer_buffer = sync_timer_read32();

    // Update double buffer timers
#if LED_DISABLE_TIMEOUT > 0
    if (led_anykey_timer < UINT32_MAX) {
        if (UINT32_MAX - deltaTime < led_anykey_timer) {
            led_anykey_timer = UINT32_MAX;
        } else {
            led_anykey_timer += deltaTime;
        }
    }
#endif  // LED_DISABLE_TIMEOUT > 0

    // Update double buffer last hit timers
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    uint8_t count = last_hit_buffer.count;
    for (uint8_t i = 0; i < count; ++i) {
        if (UINT16_MAX - deltaTime < last_hit_buffer.tick[i]) {
            last_hit_buffer.count--;
            continue;
        }
        last_hit_buffer.tick[i] += deltaTime;
    }
#endif  // LED_MATRIX_KEYREACTIVE_ENABLED
}

static void led_task_sync(void) {
    eeconfig_flush_led_matrix(false);
    // next task
    if (sync_timer_elapsed32(g_led_timer) >= LED_MATRIX_LED_FLUSH_LIMIT) led_task_state = STARTING;
}

static void led_task_start(void) {
    // reset iter
    led_effect_params.iter = 0;

    // update double buffers
    g_led_timer = led_timer_buffer;
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    g_last_hit_tracker = last_hit_buffer;
#endif  // LED_MATRIX_KEYREACTIVE_ENABLED

    // next task
    led_task_state = RENDERING;
}

static void led_task_render(uint8_t effect) {
    bool rendering         = false;
    led_effect_params.init = (effect != led_last_effect) || (led_matrix_eeconfig.enable != led_last_enable);
    if (led_effect_params.flags != led_matrix_eeconfig.flags) {
        led_effect_params.flags = led_matrix_eeconfig.flags;
        led_matrix_set_value_all(0);
    }

    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch (effect) {
        case LED_MATRIX_NONE:
            rendering = led_matrix_none(&led_effect_params);
            break;

// ---------------------------------------------
// -----Begin led effect switch case macros-----
#define LED_MATRIX_EFFECT(name, ...)          \
    case LED_MATRIX_##name:                   \
        rendering = name(&led_effect_params); \
        break;
#include "led_matrix_effects.inc"
#undef LED_MATRIX_EFFECT

#if defined(LED_MATRIX_CUSTOM_KB) || defined(LED_MATRIX_CUSTOM_USER)
#    define LED_MATRIX_EFFECT(name, ...)          \
        case LED_MATRIX_CUSTOM_##name:            \
            rendering = name(&led_effect_params); \
            break;
#    ifdef LED_MATRIX_CUSTOM_KB
#        include "led_matrix_kb.inc"
#    endif
#    ifdef LED_MATRIX_CUSTOM_USER
#        include "led_matrix_user.inc"
#    endif
#    undef LED_MATRIX_EFFECT
#endif
            // -----End led effect switch case macros-------
            // ---------------------------------------------
    }

    led_effect_params.iter++;

    // next task
    if (!rendering) {
        led_task_state = FLUSHING;
        if (!led_effect_params.init && effect == LED_MATRIX_NONE) {
            // We only need to flush once if we are LED_MATRIX_NONE
            led_task_state = SYNCING;
        }
    }
}

static void led_task_flush(uint8_t effect) {
    // update last trackers after the first full render so we can init over several frames
    led_last_effect = effect;
    led_last_enable = led_matrix_eeconfig.enable;

    // update pwm buffers
    led_matrix_update_pwm_buffers();

    // next task
    led_task_state = SYNCING;
}

void led_matrix_task(void) {
    led_task_timers();

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool suspend_backlight = suspend_state ||
#if LED_DISABLE_TIMEOUT > 0
                             (led_anykey_timer > (uint32_t)LED_DISABLE_TIMEOUT) ||
#endif  // LED_DISABLE_TIMEOUT > 0
                             false;

    uint8_t effect = suspend_backlight || !led_matrix_eeconfig.enable ? 0 : led_matrix_eeconfig.mode;

    switch (led_task_state) {
        case STARTING:
            led_task_start();
            break;
        case RENDERING:
            led_task_render(effect);
            if (effect) {
                led_matrix_indicators();
                led_matrix_indicators_advanced(&led_effect_params);
            }
            break;
        case FLUSHING:
            led_task_flush(effect);
            break;
        case SYNCING:
            led_task_sync();
            break;
    }
}

void led_matrix_indicators(void) {
    led_matrix_indicators_kb();
    led_matrix_indicators_user();
}

__attribute__((weak)) void led_matrix_indicators_kb(void) {}

__attribute__((weak)) void led_matrix_indicators_user(void) {}

void led_matrix_indicators_advanced(effect_params_t *params) {
    /* special handling is needed for "params->iter", since it's already been incremented.
     * Could move the invocations to led_task_render, but then it's missing a few checks
     * and not sure which would be better. Otherwise, this should be called from
     * led_task_render, right before the iter++ line.
     */
#if defined(LED_MATRIX_LED_PROCESS_LIMIT) && LED_MATRIX_LED_PROCESS_LIMIT > 0 && LED_MATRIX_LED_PROCESS_LIMIT < DRIVER_LED_TOTAL
    uint8_t min = LED_MATRIX_LED_PROCESS_LIMIT * (params->iter - 1);
    uint8_t max = min + LED_MATRIX_LED_PROCESS_LIMIT;
    if (max > DRIVER_LED_TOTAL) max = DRIVER_LED_TOTAL;
#else
    uint8_t min = 0;
    uint8_t max = DRIVER_LED_TOTAL;
#endif
    led_matrix_indicators_advanced_kb(min, max);
    led_matrix_indicators_advanced_user(min, max);
}

__attribute__((weak)) void led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {}

__attribute__((weak)) void led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {}

void led_matrix_init(void) {
    led_matrix_driver.init();

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    g_last_hit_tracker.count = 0;
    for (uint8_t i = 0; i < LED_HITS_TO_REMEMBER; ++i) {
        g_last_hit_tracker.tick[i] = UINT16_MAX;
    }

    last_hit_buffer.count = 0;
    for (uint8_t i = 0; i < LED_HITS_TO_REMEMBER; ++i) {
        last_hit_buffer.tick[i] = UINT16_MAX;
    }
#endif  // LED_MATRIX_KEYREACTIVE_ENABLED

    if (!eeconfig_is_enabled()) {
        dprintf("led_matrix_init_drivers eeconfig is not enabled.\n");
        eeconfig_init();
        eeconfig_update_led_matrix_default();
    }

    eeconfig_init_led_matrix();
    if (!led_matrix_eeconfig.mode) {
        dprintf("led_matrix_init_drivers led_matrix_eeconfig.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_led_matrix_default();
    }
    eeconfig_debug_led_matrix();  // display current eeprom values
}

void led_matrix_set_suspend_state(bool state) {
#ifdef LED_DISABLE_WHEN_USB_SUSPENDED
    if (state && !suspend_state && is_keyboard_master()) {  // only run if turning off, and only once
        led_task_render(0);                                 // turn off all LEDs when suspending
        led_task_flush(0);                                  // and actually flash led state to LEDs
    }
    suspend_state = state;
#endif
}

bool led_matrix_get_suspend_state(void) { return suspend_state; }

void led_matrix_toggle_eeprom_helper(bool write_to_eeprom) {
    led_matrix_eeconfig.enable ^= 1;
    led_task_state = STARTING;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix toggle [%s]: led_matrix_eeconfig.enable = %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.enable);
}
void led_matrix_toggle_noeeprom(void) { led_matrix_toggle_eeprom_helper(false); }
void led_matrix_toggle(void) { led_matrix_toggle_eeprom_helper(true); }

void led_matrix_enable(void) {
    led_matrix_enable_noeeprom();
    eeconfig_flag_led_matrix(true);
}

void led_matrix_enable_noeeprom(void) {
    if (!led_matrix_eeconfig.enable) led_task_state = STARTING;
    led_matrix_eeconfig.enable = 1;
}

void led_matrix_disable(void) {
    led_matrix_disable_noeeprom();
    eeconfig_flag_led_matrix(true);
}

void led_matrix_disable_noeeprom(void) {
    if (led_matrix_eeconfig.enable) led_task_state = STARTING;
    led_matrix_eeconfig.enable = 0;
}

uint8_t led_matrix_is_enabled(void) { return led_matrix_eeconfig.enable; }

void led_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
    if (!led_matrix_eeconfig.enable) {
        return;
    }
    if (mode < 1) {
        led_matrix_eeconfig.mode = 1;
    } else if (mode >= LED_MATRIX_EFFECT_MAX) {
        led_matrix_eeconfig.mode = LED_MATRIX_EFFECT_MAX - 1;
    } else {
        led_matrix_eeconfig.mode = mode;
    }
    led_task_state = STARTING;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix mode [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.mode);
}
void led_matrix_mode_noeeprom(uint8_t mode) { led_matrix_mode_eeprom_helper(mode, false); }
void led_matrix_mode(uint8_t mode) { led_matrix_mode_eeprom_helper(mode, true); }

uint8_t led_matrix_get_mode(void) { return led_matrix_eeconfig.mode; }

void led_matrix_step_helper(bool write_to_eeprom) {
    uint8_t mode = led_matrix_eeconfig.mode + 1;
    led_matrix_mode_eeprom_helper((mode < LED_MATRIX_EFFECT_MAX) ? mode : 1, write_to_eeprom);
}
void led_matrix_step_noeeprom(void) { led_matrix_step_helper(false); }
void led_matrix_step(void) { led_matrix_step_helper(true); }

void led_matrix_step_reverse_helper(bool write_to_eeprom) {
    uint8_t mode = led_matrix_eeconfig.mode - 1;
    led_matrix_mode_eeprom_helper((mode < 1) ? LED_MATRIX_EFFECT_MAX - 1 : mode, write_to_eeprom);
}
void led_matrix_step_reverse_noeeprom(void) { led_matrix_step_reverse_helper(false); }
void led_matrix_step_reverse(void) { led_matrix_step_reverse_helper(true); }

void led_matrix_set_val_eeprom_helper(uint8_t val, bool write_to_eeprom) {
    if (!led_matrix_eeconfig.enable) {
        return;
    }
    led_matrix_eeconfig.val = (val > LED_MATRIX_MAXIMUM_BRIGHTNESS) ? LED_MATRIX_MAXIMUM_BRIGHTNESS : val;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix set val [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.val);
}
void led_matrix_set_val_noeeprom(uint8_t val) { led_matrix_set_val_eeprom_helper(val, false); }
void led_matrix_set_val(uint8_t val) { led_matrix_set_val_eeprom_helper(val, true); }

uint8_t led_matrix_get_val(void) { return led_matrix_eeconfig.val; }

void led_matrix_increase_val_helper(bool write_to_eeprom) { led_matrix_set_val_eeprom_helper(qadd8(led_matrix_eeconfig.val, LED_MATRIX_VAL_STEP), write_to_eeprom); }
void led_matrix_increase_val_noeeprom(void) { led_matrix_increase_val_helper(false); }
void led_matrix_increase_val(void) { led_matrix_increase_val_helper(true); }

void led_matrix_decrease_val_helper(bool write_to_eeprom) { led_matrix_set_val_eeprom_helper(qsub8(led_matrix_eeconfig.val, LED_MATRIX_VAL_STEP), write_to_eeprom); }
void led_matrix_decrease_val_noeeprom(void) { led_matrix_decrease_val_helper(false); }
void led_matrix_decrease_val(void) { led_matrix_decrease_val_helper(true); }

void led_matrix_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom) {
    led_matrix_eeconfig.speed = speed;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix set speed [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.speed);
}
void led_matrix_set_speed_noeeprom(uint8_t speed) { led_matrix_set_speed_eeprom_helper(speed, false); }
void led_matrix_set_speed(uint8_t speed) { led_matrix_set_speed_eeprom_helper(speed, true); }

uint8_t led_matrix_get_speed(void) { return led_matrix_eeconfig.speed; }

void led_matrix_increase_speed_helper(bool write_to_eeprom) { led_matrix_set_speed_eeprom_helper(qadd8(led_matrix_eeconfig.speed, LED_MATRIX_SPD_STEP), write_to_eeprom); }
void led_matrix_increase_speed_noeeprom(void) { led_matrix_increase_speed_helper(false); }
void led_matrix_increase_speed(void) { led_matrix_increase_speed_helper(true); }

void led_matrix_decrease_speed_helper(bool write_to_eeprom) { led_matrix_set_speed_eeprom_helper(qsub8(led_matrix_eeconfig.speed, LED_MATRIX_SPD_STEP), write_to_eeprom); }
void led_matrix_decrease_speed_noeeprom(void) { led_matrix_decrease_speed_helper(false); }
void led_matrix_decrease_speed(void) { led_matrix_decrease_speed_helper(true); }

led_flags_t led_matrix_get_flags(void) { return led_matrix_eeconfig.flags; }

void led_matrix_set_flags(led_flags_t flags) { led_matrix_eeconfig.flags = flags; }
