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

#ifdef IS31FL3731
  #include "is31fl3731.h"
#elif defined (IS31FL3733)
  #include "is31fl3733.h"
#elif defined (IS31FL3737)
  #include "is31fl3737.h"
#elif defined (WS2812)
  #include "ws2812.h"
#endif

#ifndef RGB_MATRIX_LED_FLUSH_LIMIT
  #define RGB_MATRIX_LED_FLUSH_LIMIT 16
#endif

#ifndef RGB_MATRIX_LED_PROCESS_LIMIT
  #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5
#endif

#if defined(RGB_MATRIX_LED_PROCESS_LIMIT) && RGB_MATRIX_LED_PROCESS_LIMIT > 0 && RGB_MATRIX_LED_PROCESS_LIMIT < DRIVER_LED_TOTAL
#define RGB_MATRIX_USE_LIMITS(min, max) uint8_t min = RGB_MATRIX_LED_PROCESS_LIMIT * params->iter; \
  uint8_t max = min + RGB_MATRIX_LED_PROCESS_LIMIT; \
  if (max > DRIVER_LED_TOTAL) \
    max = DRIVER_LED_TOTAL;
#else
#define RGB_MATRIX_USE_LIMITS(min, max) uint8_t min = 0; \
  uint8_t max = DRIVER_LED_TOTAL;
#endif

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];

typedef struct
{
	HSV color;
	uint8_t index;
} rgb_indicator;

enum rgb_matrix_effects {
  RGB_MATRIX_NONE = 0,
	RGB_MATRIX_SOLID_COLOR = 1,
#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
  RGB_MATRIX_ALPHAS_MODS,
#endif // DISABLE_RGB_MATRIX_ALPHAS_MODS
#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  RGB_MATRIX_GRADIENT_UP_DOWN,
#endif // DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#ifndef DISABLE_RGB_MATRIX_BREATHING
  RGB_MATRIX_BREATHING,
#endif // DISABLE_RGB_MATRIX_BREATHING
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
  RGB_MATRIX_CYCLE_ALL,
#endif // DISABLE_RGB_MATRIX_CYCLE_ALL
#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  RGB_MATRIX_CYCLE_LEFT_RIGHT,
#endif // DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
  RGB_MATRIX_CYCLE_UP_DOWN,
#endif // DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  RGB_MATRIX_RAINBOW_MOVING_CHEVRON,
#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
  RGB_MATRIX_DUAL_BEACON,
#endif // DISABLE_RGB_MATRIX_DUAL_BEACON
#ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
  RGB_MATRIX_RAINBOW_BEACON,
#endif // DISABLE_RGB_MATRIX_RAINBOW_BEACON
#ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  RGB_MATRIX_RAINBOW_PINWHEELS,
#endif // DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#ifndef DISABLE_RGB_MATRIX_RAINDROPS
  RGB_MATRIX_RAINDROPS,
#endif // DISABLE_RGB_MATRIX_RAINDROPS
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
  RGB_MATRIX_JELLYBEAN_RAINDROPS,
#endif // DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#ifndef DISABLE_RGB_MATRIX_DIGITAL_RAIN
  RGB_MATRIX_DIGITAL_RAIN,
#endif // DISABLE_RGB_MATRIX_DIGITAL_RAIN
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  RGB_MATRIX_SOLID_REACTIVE_SIMPLE,
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
  RGB_MATRIX_SOLID_REACTIVE,
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE
#ifndef DISABLE_RGB_MATRIX_SPLASH
  RGB_MATRIX_SPLASH,
#endif // DISABLE_RGB_MATRIX_SPLASH
#ifndef DISABLE_RGB_MATRIX_MULTISPLASH
  RGB_MATRIX_MULTISPLASH,
#endif // DISABLE_RGB_MATRIX_MULTISPLASH
#ifndef DISABLE_RGB_MATRIX_SOLID_SPLASH
  RGB_MATRIX_SOLID_SPLASH,
#endif // DISABLE_RGB_MATRIX_SOLID_SPLASH
#ifndef DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
  RGB_MATRIX_SOLID_MULTISPLASH,
#endif // DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
  RGB_MATRIX_EFFECT_MAX
};

uint8_t rgb_matrix_map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led_i);

void rgb_matrix_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void rgb_matrix_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
void rgb_matrix_indicators_kb(void);
void rgb_matrix_indicators_user(void);

void rgb_matrix_init(void);
void rgb_matrix_setup_drivers(void);

void rgb_matrix_set_suspend_state(bool state);
void rgb_matrix_set_indicator_state(uint8_t state);


void rgb_matrix_task(void);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void rgb_matrix_update_pwm_buffers(void);

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record);

void rgb_matrix_increase(void);
void rgb_matrix_decrease(void);

// void *backlight_get_key_color_eeprom_address(uint8_t led);
// void backlight_get_key_color( uint8_t led, HSV *hsv );
// void backlight_set_key_color( uint8_t row, uint8_t column, HSV hsv );

void rgb_matrix_toggle(void);
void rgb_matrix_enable(void);
void rgb_matrix_enable_noeeprom(void);
void rgb_matrix_disable(void);
void rgb_matrix_disable_noeeprom(void);
void rgb_matrix_step(void);
void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val);
void rgb_matrix_step_reverse(void);
void rgb_matrix_increase_hue(void);
void rgb_matrix_decrease_hue(void);
void rgb_matrix_increase_sat(void);
void rgb_matrix_decrease_sat(void);
void rgb_matrix_increase_val(void);
void rgb_matrix_decrease_val(void);
void rgb_matrix_increase_speed(void);
void rgb_matrix_decrease_speed(void);
void rgb_matrix_mode(uint8_t mode);
void rgb_matrix_mode_noeeprom(uint8_t mode);
uint8_t rgb_matrix_get_mode(void);

#ifndef RGBLIGHT_ENABLE
#define rgblight_toggle() rgb_matrix_toggle()
#define rgblight_enable() rgb_matrix_enable()
#define rgblight_enable_noeeprom() rgb_matrix_enable_noeeprom()
#define rgblight_disable() rgb_matrix_disable()
#define rgblight_disable_noeeprom() rgb_matrix_disable_noeeprom()
#define rgblight_step() rgb_matrix_step()
#define rgblight_sethsv(hue, sat, val) rgb_matrix_sethsv(hue, sat, val)
#define rgblight_sethsv_noeeprom(hue, sat, val) rgb_matrix_sethsv_noeeprom(hue, sat, val)
#define rgblight_step_reverse() rgb_matrix_step_reverse()
#define rgblight_increase_hue() rgb_matrix_increase_hue()
#define rgblight_decrease_hue() rgb_matrix_decrease_hue()
#define rgblight_increase_sat() rgb_matrix_increase_sat()
#define rgblight_decrease_sat() rgb_matrix_decrease_sat()
#define rgblight_increase_val() rgb_matrix_increase_val()
#define rgblight_decrease_val() rgb_matrix_decrease_val()
#define rgblight_increase_speed() rgb_matrix_increase_speed()
#define rgblight_decrease_speed() rgb_matrix_decrease_speed()
#define rgblight_mode(mode) rgb_matrix_mode(mode)
#define rgblight_mode_noeeprom(mode) rgb_matrix_mode_noeeprom(mode)
#define rgblight_get_mode() rgb_matrix_get_mode()

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

#endif
