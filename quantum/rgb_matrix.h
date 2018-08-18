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
#include "color.h"
#include "quantum.h"

#ifdef IS31FL3731
    #include "is31fl3731.h"
#elif defined (IS31FL3733)
    #include "is31fl3733.h"
#endif

typedef struct Point {
	uint8_t x;
	uint8_t y;
} __attribute__((packed)) Point;

typedef struct rgb_led {
	union {
		uint8_t raw;
		struct {
			uint8_t row:4; // 16 max
			uint8_t col:4; // 16 max
		};
	} matrix_co;
	Point point;
	uint8_t modifier:1;
} __attribute__((packed)) rgb_led;


extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];

typedef struct
{
	HSV color;
	uint8_t index;
} rgb_indicator;

typedef union {
  uint32_t raw;
  struct {
    bool     enable  :1;
    uint8_t  mode    :6;
    uint16_t hue     :9;
    uint8_t  sat     :8;
    uint8_t  val     :8;
    uint8_t  speed   :8;//EECONFIG needs to be increased to support this
  };
} rgb_config_t;

enum rgb_matrix_effects {
	RGB_MATRIX_SOLID_COLOR = 1,
    RGB_MATRIX_ALPHAS_MODS,
    RGB_MATRIX_DUAL_BEACON,
    RGB_MATRIX_GRADIENT_UP_DOWN,
    RGB_MATRIX_RAINDROPS,
    RGB_MATRIX_CYCLE_ALL,
    RGB_MATRIX_CYCLE_LEFT_RIGHT,
    RGB_MATRIX_CYCLE_UP_DOWN,
    RGB_MATRIX_RAINBOW_BEACON,
    RGB_MATRIX_RAINBOW_PINWHEELS,
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,
    RGB_MATRIX_JELLYBEAN_RAINDROPS,
#ifdef RGB_MATRIX_KEYPRESSES
    RGB_MATRIX_SOLID_REACTIVE,
    RGB_MATRIX_SPLASH,
    RGB_MATRIX_MULTISPLASH,
    RGB_MATRIX_SOLID_SPLASH,
    RGB_MATRIX_SOLID_MULTISPLASH,
#endif
    RGB_MATRIX_EFFECT_MAX
};

void rgb_matrix_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
void rgb_matrix_indicators_kb(void);
void rgb_matrix_indicators_user(void);

void rgb_matrix_single_LED_test(void);

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

void rgb_matrix_test_led( uint8_t index, bool red, bool green, bool blue );
uint32_t rgb_matrix_get_tick(void);

void rgblight_toggle(void);
void rgblight_step(void);
void rgblight_step_reverse(void);
void rgblight_increase_hue(void);
void rgblight_decrease_hue(void);
void rgblight_increase_sat(void);
void rgblight_decrease_sat(void);
void rgblight_increase_val(void);
void rgblight_decrease_val(void);
void rgblight_increase_speed(void);
void rgblight_decrease_speed(void);
void rgblight_mode(uint8_t mode);
uint32_t rgblight_get_mode(void);

#endif
