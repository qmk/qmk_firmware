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
#include "eeconfig.h"
#include "keyboard.h"
#include "sync_timer.h"
#include "debug.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
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
#ifdef COMMUNITY_MODULES_ENABLE
#    include "led_matrix_community_modules.inc"
#endif
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

// globals
led_eeconfig_t led_matrix_eeconfig; // TODO: would like to prefix this with g_ for global consistancy, do this in another pr
uint32_t       g_led_timer;
#ifdef LED_MATRIX_FRAMEBUFFER_EFFECTS
uint8_t g_led_frame_buffer[MATRIX_ROWS][MATRIX_COLS] = {{0}};
#endif // LED_MATRIX_FRAMEBUFFER_EFFECTS
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
last_hit_t g_last_hit_tracker;
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

#ifndef LED_MATRIX_FLAG_STEPS
#    define LED_MATRIX_FLAG_STEPS {LED_FLAG_ALL, LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER, LED_FLAG_NONE}
#endif
static const uint8_t led_matrix_flag_steps[] = LED_MATRIX_FLAG_STEPS;
#define LED_MATRIX_FLAG_STEPS_COUNT ARRAY_SIZE(led_matrix_flag_steps)

// internals
static bool            suspend_state      = false;
static uint8_t         led_last_enable    = UINT8_MAX;
static uint8_t         led_last_effect    = UINT8_MAX;
static uint8_t         led_current_effect = 0;
static effect_params_t led_effect_params  = {0, LED_FLAG_ALL, false};
static led_task_states led_task_state     = SYNCING;

// double buffers
static uint32_t led_timer_buffer;
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
static last_hit_t last_hit_buffer;
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

// split led matrix
#if defined(LED_MATRIX_SPLIT)
const uint8_t k_led_matrix_split[2] = LED_MATRIX_SPLIT;
#endif

EECONFIG_DEBOUNCE_HELPER(led_matrix, led_matrix_eeconfig);

void eeconfig_force_flush_led_matrix(void) {
    eeconfig_flush_led_matrix(true);
}

void eeconfig_update_led_matrix_default(void) {
    dprintf("eeconfig_update_led_matrix_default\n");
    led_matrix_eeconfig.enable = LED_MATRIX_DEFAULT_ON;
    led_matrix_eeconfig.mode   = LED_MATRIX_DEFAULT_MODE;
    led_matrix_eeconfig.val    = LED_MATRIX_DEFAULT_VAL;
    led_matrix_eeconfig.speed  = LED_MATRIX_DEFAULT_SPD;
    led_matrix_eeconfig.flags  = LED_MATRIX_DEFAULT_FLAGS;
    eeconfig_flush_led_matrix(true);
}

void eeconfig_debug_led_matrix(void) {
    dprintf("led_matrix_eeconfig EEPROM\n");
    dprintf("led_matrix_eeconfig.enable = %d\n", led_matrix_eeconfig.enable);
#ifdef LED_MATRIX_MODE_NAME_ENABLE
    dprintf("led_matrix_eeconfig.mode = %d (%s)\n", led_matrix_eeconfig.mode, led_matrix_get_mode_name(led_matrix_eeconfig.mode));
#else
    dprintf("led_matrix_eeconfig.mode = %d\n", led_matrix_eeconfig.mode);
#endif // LED_MATRIX_MODE_NAME_ENABLE
    dprintf("led_matrix_eeconfig.val = %d\n", led_matrix_eeconfig.val);
    dprintf("led_matrix_eeconfig.speed = %d\n", led_matrix_eeconfig.speed);
    dprintf("led_matrix_eeconfig.flags = %d\n", led_matrix_eeconfig.flags);
}

void led_matrix_reload_from_eeprom(void) {
    led_matrix_disable_noeeprom();
    /* Reset back to what we have in eeprom */
    eeconfig_init_led_matrix();
    eeconfig_debug_led_matrix(); // display current eeprom values
    if (led_matrix_eeconfig.enable) {
        led_matrix_mode_noeeprom(led_matrix_eeconfig.mode);
    }
}

__attribute__((weak)) uint8_t led_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
    return 0;
}

uint8_t led_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i) {
    uint8_t led_count = led_matrix_map_row_column_to_led_kb(row, column, led_i);
    uint8_t led_index = g_led_config.matrix_co[row][column];
    if (led_index != NO_LED) {
        led_i[led_count] = led_index;
        led_count++;
    }
    return led_count;
}

void led_matrix_update_pwm_buffers(void) {
    led_matrix_driver.flush();
}

__attribute__((weak)) int led_matrix_led_index(int index) {
#if defined(LED_MATRIX_SPLIT)
    if (!is_keyboard_left() && index >= k_led_matrix_split[0]) {
        return index - k_led_matrix_split[0];
    }
#endif
    return index;
}

void led_matrix_set_value(int index, uint8_t value) {
#ifdef USE_CIE1931_CURVE
    value = pgm_read_byte(&CIE1931_CURVE[value]);
#endif
    led_matrix_driver.set_value(led_matrix_led_index(index), value);
}

void led_matrix_set_value_all(uint8_t value) {
#if defined(LED_MATRIX_SPLIT)
    for (uint8_t i = 0; i < LED_MATRIX_LED_COUNT; i++)
        led_matrix_set_value(i, value);
#else
#    ifdef USE_CIE1931_CURVE
    led_matrix_driver.set_value_all(pgm_read_byte(&CIE1931_CURVE[value]));
#    else
    led_matrix_driver.set_value_all(value);
#    endif
#endif
}

void led_matrix_handle_key_event(uint8_t row, uint8_t col, bool pressed) {
#ifndef LED_MATRIX_SPLIT
    if (!is_keyboard_master()) return;
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = 0;

#    if defined(LED_MATRIX_KEYRELEASES)
    if (!pressed)
#    elif defined(LED_MATRIX_KEYPRESSES)
    if (pressed)
#    endif // defined(LED_MATRIX_KEYRELEASES)
    {
        led_count = led_matrix_map_row_column_to_led(row, col, led);
    }

    if (last_hit_buffer.count + led_count > LED_HITS_TO_REMEMBER) {
        memcpy(&last_hit_buffer.x[0], &last_hit_buffer.x[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.y[0], &last_hit_buffer.y[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.tick[0], &last_hit_buffer.tick[led_count], (LED_HITS_TO_REMEMBER - led_count) * 2); // 16 bit
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
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

#if defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
    if (led_matrix_eeconfig.mode == LED_MATRIX_TYPING_HEATMAP) {
        process_led_matrix_typing_heatmap(row, col);
    }
#endif // defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
}

static bool led_matrix_none(effect_params_t *params) {
    if (!params->init) {
        return false;
    }

    led_matrix_set_value_all(0);
    return false;
}

static void led_task_timers(void) {
#if defined(LED_MATRIX_KEYREACTIVE_ENABLED)
    uint32_t deltaTime = sync_timer_elapsed32(led_timer_buffer);
#endif // defined(LED_MATRIX_KEYREACTIVE_ENABLED)
    led_timer_buffer = sync_timer_read32();

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
#endif // LED_MATRIX_KEYREACTIVE_ENABLED
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
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool suspend_backlight = suspend_state ||
#if LED_MATRIX_TIMEOUT > 0
                             (last_input_activity_elapsed() > (uint32_t)LED_MATRIX_TIMEOUT) ||
#endif // LED_MATRIX_TIMEOUT > 0
                             false;

    // Set effect to be renedered
    led_current_effect = suspend_backlight || !led_matrix_eeconfig.enable ? 0 : led_matrix_eeconfig.mode;

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

#ifdef COMMUNITY_MODULES_ENABLE
#    define LED_MATRIX_EFFECT(name, ...)          \
        case LED_MATRIX_COMMUNITY_MODULE_##name:  \
            rendering = name(&led_effect_params); \
            break;
#    include "led_matrix_community_modules.inc"
#    undef LED_MATRIX_EFFECT
#endif

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

    uint8_t effect = led_current_effect;

    switch (led_task_state) {
        case STARTING:
            led_task_start();
            break;
        case RENDERING:
            led_task_render(effect);
            if (effect) {
                if (led_task_state == FLUSHING) {
                    led_matrix_indicators(); // ensure we only draw basic indicators once rendering is finished
                }
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

__attribute__((weak)) bool led_matrix_indicators_modules(void) {
    return true;
}

void led_matrix_indicators(void) {
    led_matrix_indicators_modules();
    led_matrix_indicators_kb();
}

__attribute__((weak)) bool led_matrix_indicators_kb(void) {
    return led_matrix_indicators_user();
}

__attribute__((weak)) bool led_matrix_indicators_user(void) {
    return true;
}

__attribute__((weak)) bool led_matrix_indicators_advanced_modules(uint8_t led_min, uint8_t led_max) {
    return true;
}

void led_matrix_indicators_advanced(effect_params_t *params) {
    /* special handling is needed for "params->iter", since it's already been incremented.
     * Could move the invocations to led_task_render, but then it's missing a few checks
     * and not sure which would be better. Otherwise, this should be called from
     * led_task_render, right before the iter++ line.
     */
    LED_MATRIX_USE_LIMITS_ITER(min, max, params->iter - 1);
    led_matrix_indicators_advanced_modules(min, max);
    led_matrix_indicators_advanced_kb(min, max);
}

__attribute__((weak)) bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    return led_matrix_indicators_advanced_user(led_min, led_max);
}

__attribute__((weak)) bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return true;
}

struct led_matrix_limits_t led_matrix_get_limits(uint8_t iter) {
    struct led_matrix_limits_t limits = {0};
#if defined(LED_MATRIX_LED_PROCESS_LIMIT) && LED_MATRIX_LED_PROCESS_LIMIT > 0 && LED_MATRIX_LED_PROCESS_LIMIT < LED_MATRIX_LED_COUNT
#    if defined(LED_MATRIX_SPLIT)
    limits.led_min_index = LED_MATRIX_LED_PROCESS_LIMIT * (iter);
    limits.led_max_index = limits.led_min_index + LED_MATRIX_LED_PROCESS_LIMIT;
    if (limits.led_max_index > LED_MATRIX_LED_COUNT) limits.led_max_index = LED_MATRIX_LED_COUNT;
    if (is_keyboard_left() && (limits.led_max_index > k_led_matrix_split[0])) limits.led_max_index = k_led_matrix_split[0];
    if (!(is_keyboard_left()) && (limits.led_min_index < k_led_matrix_split[0])) limits.led_min_index = k_led_matrix_split[0];
#    else
    limits.led_min_index = LED_MATRIX_LED_PROCESS_LIMIT * (iter);
    limits.led_max_index = limits.led_min_index + LED_MATRIX_LED_PROCESS_LIMIT;
    if (limits.led_max_index > LED_MATRIX_LED_COUNT) limits.led_max_index = LED_MATRIX_LED_COUNT;
#    endif
#else
#    if defined(LED_MATRIX_SPLIT)
    limits.led_min_index = 0;
    limits.led_max_index = LED_MATRIX_LED_COUNT;
    if (is_keyboard_left() && (limits.led_max_index > k_led_matrix_split[0])) limits.led_max_index = k_led_matrix_split[0];
    if (!(is_keyboard_left()) && (limits.led_min_index < k_led_matrix_split[0])) limits.led_min_index = k_led_matrix_split[0];
#    else
    limits.led_min_index = 0;
    limits.led_max_index = LED_MATRIX_LED_COUNT;
#    endif
#endif
    return limits;
}

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
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

    eeconfig_init_led_matrix();
    if (!led_matrix_eeconfig.mode) {
        dprintf("led_matrix_init_drivers led_matrix_eeconfig.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_led_matrix_default();
    }
    eeconfig_debug_led_matrix(); // display current eeprom values
}

void led_matrix_set_suspend_state(bool state) {
#ifdef LED_MATRIX_SLEEP
    if (state && !suspend_state && is_keyboard_master()) { // only run if turning off, and only once
        led_task_render(0);                                // turn off all LEDs when suspending
        led_task_flush(0);                                 // and actually flash led state to LEDs
    }
    suspend_state = state;
#endif
}

bool led_matrix_get_suspend_state(void) {
    return suspend_state;
}

void led_matrix_toggle_eeprom_helper(bool write_to_eeprom) {
    led_matrix_eeconfig.enable ^= 1;
    led_task_state = STARTING;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix toggle [%s]: led_matrix_eeconfig.enable = %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.enable);
}
void led_matrix_toggle_noeeprom(void) {
    led_matrix_toggle_eeprom_helper(false);
}
void led_matrix_toggle(void) {
    led_matrix_toggle_eeprom_helper(true);
}

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

uint8_t led_matrix_is_enabled(void) {
    return led_matrix_eeconfig.enable;
}

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
#ifdef LED_MATRIX_MODE_NAME_ENABLE
    dprintf("led matrix mode [%s]: %u (%s)\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", (unsigned)led_matrix_eeconfig.mode, led_matrix_get_mode_name(led_matrix_eeconfig.mode));
#else
    dprintf("led matrix mode [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", (unsigned)led_matrix_eeconfig.mode);
#endif // LED_MATRIX_MODE_NAME_ENABLE
}
void led_matrix_mode_noeeprom(uint8_t mode) {
    led_matrix_mode_eeprom_helper(mode, false);
}
void led_matrix_mode(uint8_t mode) {
    led_matrix_mode_eeprom_helper(mode, true);
}

uint8_t led_matrix_get_mode(void) {
    return led_matrix_eeconfig.mode;
}

void led_matrix_step_helper(bool write_to_eeprom) {
    uint8_t mode = led_matrix_eeconfig.mode + 1;
    led_matrix_mode_eeprom_helper((mode < LED_MATRIX_EFFECT_MAX) ? mode : 1, write_to_eeprom);
}
void led_matrix_step_noeeprom(void) {
    led_matrix_step_helper(false);
}
void led_matrix_step(void) {
    led_matrix_step_helper(true);
}

void led_matrix_step_reverse_helper(bool write_to_eeprom) {
    uint8_t mode = led_matrix_eeconfig.mode - 1;
    led_matrix_mode_eeprom_helper((mode < 1) ? LED_MATRIX_EFFECT_MAX - 1 : mode, write_to_eeprom);
}
void led_matrix_step_reverse_noeeprom(void) {
    led_matrix_step_reverse_helper(false);
}
void led_matrix_step_reverse(void) {
    led_matrix_step_reverse_helper(true);
}

void led_matrix_set_val_eeprom_helper(uint8_t val, bool write_to_eeprom) {
    if (!led_matrix_eeconfig.enable) {
        return;
    }
    led_matrix_eeconfig.val = (val > LED_MATRIX_MAXIMUM_BRIGHTNESS) ? LED_MATRIX_MAXIMUM_BRIGHTNESS : val;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix set val [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.val);
}
void led_matrix_set_val_noeeprom(uint8_t val) {
    led_matrix_set_val_eeprom_helper(val, false);
}
void led_matrix_set_val(uint8_t val) {
    led_matrix_set_val_eeprom_helper(val, true);
}

uint8_t led_matrix_get_val(void) {
    return led_matrix_eeconfig.val;
}

void led_matrix_increase_val_helper(bool write_to_eeprom) {
    led_matrix_set_val_eeprom_helper(qadd8(led_matrix_eeconfig.val, LED_MATRIX_VAL_STEP), write_to_eeprom);
}
void led_matrix_increase_val_noeeprom(void) {
    led_matrix_increase_val_helper(false);
}
void led_matrix_increase_val(void) {
    led_matrix_increase_val_helper(true);
}

void led_matrix_decrease_val_helper(bool write_to_eeprom) {
    led_matrix_set_val_eeprom_helper(qsub8(led_matrix_eeconfig.val, LED_MATRIX_VAL_STEP), write_to_eeprom);
}
void led_matrix_decrease_val_noeeprom(void) {
    led_matrix_decrease_val_helper(false);
}
void led_matrix_decrease_val(void) {
    led_matrix_decrease_val_helper(true);
}

void led_matrix_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom) {
    led_matrix_eeconfig.speed = speed;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix set speed [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.speed);
}
void led_matrix_set_speed_noeeprom(uint8_t speed) {
    led_matrix_set_speed_eeprom_helper(speed, false);
}
void led_matrix_set_speed(uint8_t speed) {
    led_matrix_set_speed_eeprom_helper(speed, true);
}

uint8_t led_matrix_get_speed(void) {
    return led_matrix_eeconfig.speed;
}

void led_matrix_increase_speed_helper(bool write_to_eeprom) {
    led_matrix_set_speed_eeprom_helper(qadd8(led_matrix_eeconfig.speed, LED_MATRIX_SPD_STEP), write_to_eeprom);
}
void led_matrix_increase_speed_noeeprom(void) {
    led_matrix_increase_speed_helper(false);
}
void led_matrix_increase_speed(void) {
    led_matrix_increase_speed_helper(true);
}

void led_matrix_decrease_speed_helper(bool write_to_eeprom) {
    led_matrix_set_speed_eeprom_helper(qsub8(led_matrix_eeconfig.speed, LED_MATRIX_SPD_STEP), write_to_eeprom);
}
void led_matrix_decrease_speed_noeeprom(void) {
    led_matrix_decrease_speed_helper(false);
}
void led_matrix_decrease_speed(void) {
    led_matrix_decrease_speed_helper(true);
}

void led_matrix_set_flags_eeprom_helper(led_flags_t flags, bool write_to_eeprom) {
    led_matrix_eeconfig.flags = flags;
    eeconfig_flag_led_matrix(write_to_eeprom);
    dprintf("led matrix set flags [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.flags);
}

led_flags_t led_matrix_get_flags(void) {
    return led_matrix_eeconfig.flags;
}

void led_matrix_set_flags(led_flags_t flags) {
    led_matrix_set_flags_eeprom_helper(flags, true);
}

void led_matrix_set_flags_noeeprom(led_flags_t flags) {
    led_matrix_set_flags_eeprom_helper(flags, false);
}

void led_matrix_flags_step_helper(bool write_to_eeprom) {
    led_flags_t flags = led_matrix_get_flags();

    uint8_t next = 0;
    for (uint8_t i = 0; i < LED_MATRIX_FLAG_STEPS_COUNT; i++) {
        if (led_matrix_flag_steps[i] == flags) {
            next = i == LED_MATRIX_FLAG_STEPS_COUNT - 1 ? 0 : i + 1;
            break;
        }
    }

    led_matrix_set_flags_eeprom_helper(led_matrix_flag_steps[next], write_to_eeprom);
}

void led_matrix_flags_step_noeeprom(void) {
    led_matrix_flags_step_helper(false);
}

void led_matrix_flags_step(void) {
    led_matrix_flags_step_helper(true);
}

void led_matrix_flags_step_reverse_helper(bool write_to_eeprom) {
    led_flags_t flags = led_matrix_get_flags();

    uint8_t next = 0;
    for (uint8_t i = 0; i < LED_MATRIX_FLAG_STEPS_COUNT; i++) {
        if (led_matrix_flag_steps[i] == flags) {
            next = i == 0 ? LED_MATRIX_FLAG_STEPS_COUNT - 1 : i - 1;
            break;
        }
    }

    led_matrix_set_flags_eeprom_helper(led_matrix_flag_steps[next], write_to_eeprom);
}

void led_matrix_flags_step_reverse_noeeprom(void) {
    led_matrix_flags_step_reverse_helper(false);
}

void led_matrix_flags_step_reverse(void) {
    led_matrix_flags_step_reverse_helper(true);
}

// LED Matrix naming
#undef LED_MATRIX_EFFECT
#ifdef LED_MATRIX_MODE_NAME_ENABLE
const char *led_matrix_get_mode_name(uint8_t mode) {
    switch (mode) {
        case LED_MATRIX_NONE:
            return "NONE";

#    define LED_MATRIX_EFFECT(name, ...) \
        case LED_MATRIX_##name:          \
            return #name;
#    include "led_matrix_effects.inc"
#    undef LED_MATRIX_EFFECT

#    ifdef COMMUNITY_MODULES_ENABLE
#        define LED_MATRIX_EFFECT(name, ...)         \
            case LED_MATRIX_COMMUNITY_MODULE_##name: \
                return #name;
#        include "led_matrix_community_modules.inc"
#        undef LED_MATRIX_EFFECT
#    endif // COMMUNITY_MODULES_ENABLE

#    if defined(LED_MATRIX_CUSTOM_KB) || defined(LED_MATRIX_CUSTOM_USER)
#        define LED_MATRIX_EFFECT(name, ...) \
            case LED_MATRIX_CUSTOM_##name:   \
                return #name;

#        ifdef LED_MATRIX_CUSTOM_KB
#            include "led_matrix_kb.inc"
#        endif // LED_MATRIX_CUSTOM_KB

#        ifdef LED_MATRIX_CUSTOM_USER
#            include "led_matrix_user.inc"
#        endif // LED_MATRIX_CUSTOM_USER

#        undef LED_MATRIX_EFFECT
#    endif // LED_MATRIX_CUSTOM_KB || LED_MATRIX_CUSTOM_USER

        default:
            return "UNKNOWN";
    }
}
#    undef LED_MATRIX_EFFECT
#endif // LED_MATRIX_MODE_NAME_ENABLE
