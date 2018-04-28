/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
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
#include "is31fl3731.h"
#include "quantum.h"

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
  };
} rgb_config_t;

// This runs after another backlight effect and replaces
// colors already set
__attribute__((weak))
void backlight_effect_indicators(void) {};

void backlight_effect_single_LED_test(void);

void backlight_config_set_alphas_mods( uint16_t *value );
void backlight_config_load(void);
void backlight_config_save(void);

void backlight_init_drivers(void);

void backlight_timer_init(void);
void backlight_timer_enable(void);
void backlight_timer_disable(void);

void backlight_set_suspend_state(bool state);
void backlight_set_indicator_state(uint8_t state);


void backlight_rgb_task(void);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void backlight_update_pwm_buffers(void);

void backlight_set_key_hit(uint8_t row, uint8_t col);
void backlight_unset_key_hit(uint8_t row, uint8_t col);

void backlight_effect_increase(void);
void backlight_effect_decrease(void);

void *backlight_get_key_color_eeprom_address(uint8_t led);
void backlight_get_key_color( uint8_t led, HSV *hsv );
void backlight_set_key_color( uint8_t row, uint8_t column, HSV hsv );

void backlight_test_led( uint8_t index, bool red, bool green, bool blue );
uint32_t backlight_get_tick(void);
void backlight_debug_led(bool state);

void rgblight_toggle(void);
void rgblight_step(void);
void rgblight_step_reverse(void);
void rgblight_increase_hue(void);
void rgblight_decrease_hue(void);
void rgblight_increase_sat(void);
void rgblight_decrease_sat(void);
void rgblight_increase_val(void);
void rgblight_decrease_val(void);
void rgblight_mode(uint8_t mode);
uint32_t rgblight_get_mode(void);

#endif
