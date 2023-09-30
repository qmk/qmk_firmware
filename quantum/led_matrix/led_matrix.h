/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Clueboard
 * Copyright 2021 Leo Deng
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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "led_matrix_types.h"
#include "keyboard.h"

#if defined(LED_MATRIX_IS31FL3218)
#    include "is31fl3218-simple.h"
#elif defined(LED_MATRIX_IS31FL3731)
#    include "is31fl3731-simple.h"
#endif
#ifdef LED_MATRIX_IS31FL3733
#    include "is31fl3733-simple.h"
#endif
#ifdef LED_MATRIX_IS31FL3736
#    include "is31fl3736-simple.h"
#endif
#if defined(IS31FLCOMMON)
#    include "is31flcommon.h"
#endif
#ifdef LED_MATRIX_CKLED2001
#    include "ckled2001-simple.h"
#endif

#ifndef LED_MATRIX_TIMEOUT
#    define LED_MATRIX_TIMEOUT 0
#endif

#ifndef LED_MATRIX_MAXIMUM_BRIGHTNESS
#    define LED_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

#ifndef LED_MATRIX_VAL_STEP
#    define LED_MATRIX_VAL_STEP 8
#endif

#ifndef LED_MATRIX_SPD_STEP
#    define LED_MATRIX_SPD_STEP 16
#endif

#ifndef LED_MATRIX_DEFAULT_ON
#    define LED_MATRIX_DEFAULT_ON true
#endif

#ifndef LED_MATRIX_DEFAULT_MODE
#    define LED_MATRIX_DEFAULT_MODE LED_MATRIX_SOLID
#endif

#ifndef LED_MATRIX_DEFAULT_VAL
#    define LED_MATRIX_DEFAULT_VAL LED_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#ifndef LED_MATRIX_DEFAULT_SPD
#    define LED_MATRIX_DEFAULT_SPD UINT8_MAX / 2
#endif

#ifndef LED_MATRIX_LED_FLUSH_LIMIT
#    define LED_MATRIX_LED_FLUSH_LIMIT 16
#endif

#ifndef LED_MATRIX_LED_PROCESS_LIMIT
#    define LED_MATRIX_LED_PROCESS_LIMIT ((LED_MATRIX_LED_COUNT + 4) / 5)
#endif
#define LED_MATRIX_LED_PROCESS_MAX_ITERATIONS ((LED_MATRIX_LED_COUNT + LED_MATRIX_LED_PROCESS_LIMIT - 1) / LED_MATRIX_LED_PROCESS_LIMIT)

#if defined(LED_MATRIX_LED_PROCESS_LIMIT) && LED_MATRIX_LED_PROCESS_LIMIT > 0 && LED_MATRIX_LED_PROCESS_LIMIT < LED_MATRIX_LED_COUNT
#    if defined(LED_MATRIX_SPLIT)
#        define LED_MATRIX_USE_LIMITS(min, max)                                                   \
            uint8_t min = LED_MATRIX_LED_PROCESS_LIMIT * params->iter;                            \
            uint8_t max = min + LED_MATRIX_LED_PROCESS_LIMIT;                                     \
            if (max > LED_MATRIX_LED_COUNT) max = LED_MATRIX_LED_COUNT;                           \
            uint8_t k_led_matrix_split[2] = LED_MATRIX_SPLIT;                                     \
            if (is_keyboard_left() && (max > k_led_matrix_split[0])) max = k_led_matrix_split[0]; \
            if (!(is_keyboard_left()) && (min < k_led_matrix_split[0])) min = k_led_matrix_split[0];
#    else
#        define LED_MATRIX_USE_LIMITS(min, max)                        \
            uint8_t min = LED_MATRIX_LED_PROCESS_LIMIT * params->iter; \
            uint8_t max = min + LED_MATRIX_LED_PROCESS_LIMIT;          \
            if (max > LED_MATRIX_LED_COUNT) max = LED_MATRIX_LED_COUNT;
#    endif
#else
#    if defined(LED_MATRIX_SPLIT)
#        define LED_MATRIX_USE_LIMITS(min, max)                                                   \
            uint8_t       min                   = 0;                                              \
            uint8_t       max                   = LED_MATRIX_LED_COUNT;                           \
            const uint8_t k_led_matrix_split[2] = LED_MATRIX_SPLIT;                               \
            if (is_keyboard_left() && (max > k_led_matrix_split[0])) max = k_led_matrix_split[0]; \
            if (!(is_keyboard_left()) && (min < k_led_matrix_split[0])) min = k_led_matrix_split[0];
#    else
#        define LED_MATRIX_USE_LIMITS(min, max) \
            uint8_t min = 0;                    \
            uint8_t max = LED_MATRIX_LED_COUNT;
#    endif
#endif

#define LED_MATRIX_TEST_LED_FLAGS() \
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue

enum led_matrix_effects {
    LED_MATRIX_NONE = 0,

// --------------------------------------
// -----Begin led effect enum macros-----
#define LED_MATRIX_EFFECT(name, ...) LED_MATRIX_##name,
#include "led_matrix_effects.inc"
#undef LED_MATRIX_EFFECT

#if defined(LED_MATRIX_CUSTOM_KB) || defined(LED_MATRIX_CUSTOM_USER)
#    define LED_MATRIX_EFFECT(name, ...) LED_MATRIX_CUSTOM_##name,
#    ifdef LED_MATRIX_CUSTOM_KB
#        include "led_matrix_kb.inc"
#    endif
#    ifdef LED_MATRIX_CUSTOM_USER
#        include "led_matrix_user.inc"
#    endif
#    undef LED_MATRIX_EFFECT
#endif
    // --------------------------------------
    // -----End led effect enum macros-------

    LED_MATRIX_EFFECT_MAX
};

void eeconfig_update_led_matrix_default(void);
void eeconfig_update_led_matrix(void);
void eeconfig_debug_led_matrix(void);

uint8_t led_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i);
uint8_t led_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);

void led_matrix_set_value(int index, uint8_t value);
void led_matrix_set_value_all(uint8_t value);

void process_led_matrix(uint8_t row, uint8_t col, bool pressed);

void led_matrix_task(void);

// This runs after another backlight effect and replaces
// values already set
void led_matrix_indicators(void);
bool led_matrix_indicators_kb(void);
bool led_matrix_indicators_user(void);

void led_matrix_indicators_advanced(effect_params_t *params);
bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);

void led_matrix_init(void);

void        led_matrix_set_suspend_state(bool state);
bool        led_matrix_get_suspend_state(void);
void        led_matrix_toggle(void);
void        led_matrix_toggle_noeeprom(void);
void        led_matrix_enable(void);
void        led_matrix_enable_noeeprom(void);
void        led_matrix_disable(void);
void        led_matrix_disable_noeeprom(void);
uint8_t     led_matrix_is_enabled(void);
void        led_matrix_mode(uint8_t mode);
void        led_matrix_mode_noeeprom(uint8_t mode);
uint8_t     led_matrix_get_mode(void);
void        led_matrix_step(void);
void        led_matrix_step_noeeprom(void);
void        led_matrix_step_reverse(void);
void        led_matrix_step_reverse_noeeprom(void);
void        led_matrix_set_val(uint8_t val);
void        led_matrix_set_val_noeeprom(uint8_t val);
uint8_t     led_matrix_get_val(void);
void        led_matrix_increase_val(void);
void        led_matrix_increase_val_noeeprom(void);
void        led_matrix_decrease_val(void);
void        led_matrix_decrease_val_noeeprom(void);
void        led_matrix_set_speed(uint8_t speed);
void        led_matrix_set_speed_noeeprom(uint8_t speed);
uint8_t     led_matrix_get_speed(void);
void        led_matrix_increase_speed(void);
void        led_matrix_increase_speed_noeeprom(void);
void        led_matrix_decrease_speed(void);
void        led_matrix_decrease_speed_noeeprom(void);
led_flags_t led_matrix_get_flags(void);
void        led_matrix_set_flags(led_flags_t flags);
void        led_matrix_set_flags_noeeprom(led_flags_t flags);

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);

    /* Set the brightness of a single LED in the buffer. */
    void (*set_value)(int index, uint8_t value);
    /* Set the brightness of all LEDS on the keyboard in the buffer. */
    void (*set_value_all)(uint8_t value);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
} led_matrix_driver_t;

static inline bool led_matrix_check_finished_leds(uint8_t led_idx) {
#if defined(LED_MATRIX_SPLIT)
    if (is_keyboard_left()) {
        uint8_t k_led_matrix_split[2] = LED_MATRIX_SPLIT;
        return led_idx < k_led_matrix_split[0];
    } else
        return led_idx < LED_MATRIX_LED_COUNT;
#else
    return led_idx < LED_MATRIX_LED_COUNT;
#endif
}

extern const led_matrix_driver_t led_matrix_driver;

extern led_eeconfig_t led_matrix_eeconfig;

extern uint32_t     g_led_timer;
extern led_config_t g_led_config;
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
extern last_hit_t g_last_hit_tracker;
#endif
#ifdef LED_MATRIX_FRAMEBUFFER_EFFECTS
extern uint8_t g_led_frame_buffer[MATRIX_ROWS][MATRIX_COLS];
#endif
