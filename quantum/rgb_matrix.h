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

#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include "rgb_matrix_types.h"
#include "color.h"
#include "quantum.h"
#include "rgblight_list.h"

#ifdef IS31FL3731
#    include "is31fl3731.h"
#elif defined(IS31FL3733)
#    include "is31fl3733.h"
#elif defined(IS31FL3737)
#    include "is31fl3737.h"
#elif defined(WS2812)
#    include "ws2812.h"
#endif

#ifndef RGB_MATRIX_LED_FLUSH_LIMIT
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#endif

#ifndef RGB_MATRIX_LED_PROCESS_LIMIT
#    define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5
#endif

#if defined(RGB_MATRIX_LED_PROCESS_LIMIT) && RGB_MATRIX_LED_PROCESS_LIMIT > 0 && RGB_MATRIX_LED_PROCESS_LIMIT < DRIVER_LED_TOTAL
#    define RGB_MATRIX_USE_LIMITS(min, max)                        \
        uint8_t min = RGB_MATRIX_LED_PROCESS_LIMIT * params->iter; \
        uint8_t max = min + RGB_MATRIX_LED_PROCESS_LIMIT;          \
        if (max > DRIVER_LED_TOTAL) max = DRIVER_LED_TOTAL;
#else
#    define RGB_MATRIX_USE_LIMITS(min, max) \
        uint8_t min = 0;                    \
        uint8_t max = DRIVER_LED_TOTAL;
#endif

#define RGB_MATRIX_TEST_LED_FLAGS() \
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue

enum rgb_matrix_effects {
    RGB_MATRIX_NONE = 0,

// --------------------------------------
// -----Begin rgb effect enum macros-----
#define RGB_MATRIX_EFFECT(name, ...) RGB_MATRIX_##name,
#include "rgb_matrix_animations/rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT

#if defined(RGB_MATRIX_CUSTOM_KB) || defined(RGB_MATRIX_CUSTOM_USER)
#    define RGB_MATRIX_EFFECT(name, ...) RGB_MATRIX_CUSTOM_##name,
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
#    undef RGB_MATRIX_EFFECT
#endif
    // --------------------------------------
    // -----End rgb effect enum macros-------

    RGB_MATRIX_EFFECT_MAX
};

void eeconfig_update_rgb_matrix_default(void);

uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i);
uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);

void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record);

void rgb_matrix_task(void);

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
void rgb_matrix_indicators_kb(void);
void rgb_matrix_indicators_user(void);

void rgb_matrix_init(void);

void        rgb_matrix_set_suspend_state(bool state);
void        rgb_matrix_toggle(void);
void        rgb_matrix_enable(void);
void        rgb_matrix_enable_noeeprom(void);
void        rgb_matrix_disable(void);
void        rgb_matrix_disable_noeeprom(void);
void        rgb_matrix_step(void);
void        rgb_matrix_step_reverse(void);
void        rgb_matrix_increase_hue(void);
void        rgb_matrix_decrease_hue(void);
void        rgb_matrix_increase_sat(void);
void        rgb_matrix_decrease_sat(void);
void        rgb_matrix_increase_val(void);
void        rgb_matrix_decrease_val(void);
void        rgb_matrix_increase_speed(void);
void        rgb_matrix_decrease_speed(void);
led_flags_t rgb_matrix_get_flags(void);
void        rgb_matrix_set_flags(led_flags_t flags);
void        rgb_matrix_mode(uint8_t mode);
void        rgb_matrix_mode_noeeprom(uint8_t mode);
uint8_t     rgb_matrix_get_mode(void);
void        rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
void        rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val);

#ifndef RGBLIGHT_ENABLE
#    define rgblight_toggle() rgb_matrix_toggle()
#    define rgblight_enable() rgb_matrix_enable()
#    define rgblight_enable_noeeprom() rgb_matrix_enable_noeeprom()
#    define rgblight_disable() rgb_matrix_disable()
#    define rgblight_disable_noeeprom() rgb_matrix_disable_noeeprom()
#    define rgblight_step() rgb_matrix_step()
#    define rgblight_sethsv(hue, sat, val) rgb_matrix_sethsv(hue, sat, val)
#    define rgblight_sethsv_noeeprom(hue, sat, val) rgb_matrix_sethsv_noeeprom(hue, sat, val)
#    define rgblight_step_reverse() rgb_matrix_step_reverse()
#    define rgblight_increase_hue() rgb_matrix_increase_hue()
#    define rgblight_decrease_hue() rgb_matrix_decrease_hue()
#    define rgblight_increase_sat() rgb_matrix_increase_sat()
#    define rgblight_decrease_sat() rgb_matrix_decrease_sat()
#    define rgblight_increase_val() rgb_matrix_increase_val()
#    define rgblight_decrease_val() rgb_matrix_decrease_val()
#    define rgblight_increase_speed() rgb_matrix_increase_speed()
#    define rgblight_decrease_speed() rgb_matrix_decrease_speed()
#    define rgblight_mode(mode) rgb_matrix_mode(mode)
#    define rgblight_mode_noeeprom(mode) rgb_matrix_mode_noeeprom(mode)
#    define rgblight_get_mode() rgb_matrix_get_mode()
#endif

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);
    /* Set the colour of a single LED in the buffer. */
    void (*set_color)(int index, uint8_t r, uint8_t g, uint8_t b);
    /* Set the colour of all LEDS on the keyboard in the buffer. */
    void (*set_color_all)(uint8_t r, uint8_t g, uint8_t b);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
} rgb_matrix_driver_t;

extern const rgb_matrix_driver_t rgb_matrix_driver;

extern rgb_config_t rgb_matrix_config;

extern bool           g_suspend_state;
extern rgb_counters_t g_rgb_counters;
extern led_config_t   g_led_config;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
extern last_hit_t g_last_hit_tracker;
#endif
#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
extern uint8_t rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS];
#endif

#endif
