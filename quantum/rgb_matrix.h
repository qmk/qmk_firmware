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
} zeal_indicator;

typedef struct
{
	bool enabled:1;                     // |
	bool use_split_left_shift:1;        // |
	bool use_split_right_shift:1;       // |
	bool use_7u_spacebar:1;             // |
	bool use_iso_enter:1;               // |
	bool disable_when_usb_suspended:1;  // |
	bool __pad6:1;                      // |
	bool __pad7:1;                      // 1 byte
	uint8_t disable_after_timeout;      // 1 byte
	uint8_t brightness;                 // 1 byte
	uint8_t effect;                     // 1 byte
	HSV color_1;                        // 3 bytes
	HSV color_2;                        // 3 bytes
	zeal_indicator caps_lock_indicator;	// 4 bytes
	zeal_indicator layer_1_indicator;	// 4 bytes
	zeal_indicator layer_2_indicator;	// 4 bytes
	zeal_indicator layer_3_indicator;	// 4 bytes
	uint16_t alphas_mods[5];            // 10 bytes
} rgb_matrix_config;                // = 36 bytes

#define EEPROM_BACKLIGHT_CONFIG_ADDR ((void*)35)
// rgb_matrix_config uses 36 bytes
// 35+36=71
#define EEPROM_BACKLIGHT_KEY_COLOR_ADDR ((void*)71)


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

void backlight_brightness_increase(void);
void backlight_brightness_decrease(void);

void backlight_color_1_hue_increase(void);
void backlight_color_1_hue_decrease(void);
void backlight_color_1_sat_increase(void);
void backlight_color_1_sat_decrease(void);
void backlight_color_2_hue_increase(void);
void backlight_color_2_hue_decrease(void);
void backlight_color_2_sat_increase(void);
void backlight_color_2_sat_decrease(void);

void *backlight_get_key_color_eeprom_address(uint8_t led);
void backlight_get_key_color( uint8_t led, HSV *hsv );
void backlight_set_key_color( uint8_t row, uint8_t column, HSV hsv );

void backlight_test_led( uint8_t index, bool red, bool green, bool blue );
uint32_t backlight_get_tick(void);
void backlight_debug_led(bool state);

void rgblight_toggle(void);
void rgblight_step(void);
void rgblight_increase_hue(void);
void rgblight_decrease_hue(void);
void rgblight_increase_sat(void);
void rgblight_decrease_sat(void);
void rgblight_increase_val(void);
void rgblight_decrease_val(void);
void rgblight_mode(uint8_t mode);
uint32_t rgblight_get_mode(void);

#endif