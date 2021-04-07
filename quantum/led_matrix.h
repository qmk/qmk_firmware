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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "led_matrix_types.h"
#include "quantum.h"

#ifdef IS31FL3731
#    include "is31fl3731-simple.h"
#endif

#ifndef LED_MATRIX_LED_FLUSH_LIMIT
#    define LED_MATRIX_LED_FLUSH_LIMIT 16
#endif

#ifndef LED_MATRIX_LED_PROCESS_LIMIT
#    define LED_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5
#endif

#if defined(LED_MATRIX_LED_PROCESS_LIMIT) && LED_MATRIX_LED_PROCESS_LIMIT > 0 && LED_MATRIX_LED_PROCESS_LIMIT < DRIVER_LED_TOTAL
#    define LED_MATRIX_USE_LIMITS(min, max)                        \
        uint8_t min = LED_MATRIX_LED_PROCESS_LIMIT * params->iter; \
        uint8_t max = min + LED_MATRIX_LED_PROCESS_LIMIT;          \
        if (max > DRIVER_LED_TOTAL) max = DRIVER_LED_TOTAL;
#else
#    define LED_MATRIX_USE_LIMITS(min, max) \
        uint8_t min = 0;                    \
        uint8_t max = DRIVER_LED_TOTAL;
#endif

enum led_matrix_effects {
    LED_MATRIX_UNIFORM_BRIGHTNESS = 1,
    // All new effects go above this line
    LED_MATRIX_EFFECT_MAX
};

void eeconfig_update_led_matrix_default(void);
void eeconfig_update_led_matrix(void);
void eeconfig_debug_led_matrix(void);

uint8_t led_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i);
uint8_t led_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);

void led_matrix_set_value(int index, uint8_t value);
void led_matrix_set_value_all(uint8_t value);

bool process_led_matrix(uint16_t keycode, keyrecord_t *record);

void led_matrix_task(void);

// This runs after another backlight effect and replaces
// values already set
void led_matrix_indicators(void);
void led_matrix_indicators_kb(void);
void led_matrix_indicators_user(void);

void led_matrix_init(void);

void    led_matrix_set_suspend_state(bool state);
bool    led_matrix_get_suspend_state(void);
void    led_matrix_toggle(void);
void    led_matrix_toggle_noeeprom(void);
void    led_matrix_enable(void);
void    led_matrix_enable_noeeprom(void);
void    led_matrix_disable(void);
void    led_matrix_disable_noeeprom(void);
uint8_t led_matrix_is_enabled(void);
void    led_matrix_mode(uint8_t mode);
void    led_matrix_mode_noeeprom(uint8_t mode);
uint8_t led_matrix_get_mode(void);
void    led_matrix_step(void);
void    led_matrix_step_noeeprom(void);
void    led_matrix_step_reverse(void);
void    led_matrix_step_reverse_noeeprom(void);
void    led_matrix_set_val(uint8_t val);
void    led_matrix_set_val_noeeprom(uint8_t val);
uint8_t led_matrix_get_val(void);
void    led_matrix_increase_val(void);
void    led_matrix_increase_val_noeeprom(void);
void    led_matrix_decrease_val(void);
void    led_matrix_decrease_val_noeeprom(void);
void    led_matrix_set_speed(uint8_t speed);
void    led_matrix_set_speed_noeeprom(uint8_t speed);
uint8_t led_matrix_get_speed(void);
void    led_matrix_increase_speed(void);
void    led_matrix_increase_speed_noeeprom(void);
void    led_matrix_decrease_speed(void);
void    led_matrix_decrease_speed_noeeprom(void);

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

extern const led_matrix_driver_t led_matrix_driver;

extern led_eeconfig_t led_matrix_eeconfig;

extern bool         g_suspend_state;
extern led_config_t g_led_config;
