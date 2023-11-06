/* Copyright 2017 Jason Williams (Wilba)
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

#if RGB_BACKLIGHT_ENABLED
#else
#error rgb_backlight.h included when RGB_BACKLIGHT_ENABLED == 0
#endif // RGB_BACKLIGHT_ENABLED

#include <stdint.h>
#include <stdbool.h>

#include "quantum/color.h"

typedef struct PACKED
{
	uint8_t h;
	uint8_t s;
} HS;

typedef struct
{
	HS color;
	uint8_t index;
} backlight_config_indicator;

#if defined(RGB_BACKLIGHT_M6_B)
#define RGB_BACKLIGHT_CUSTOM_COLORS_COUNT 6
#elif defined(RGB_BACKLIGHT_M10_C)
#define RGB_BACKLIGHT_CUSTOM_COLORS_COUNT 10
#endif

typedef struct
{
	bool use_split_backspace:1;         // |
	bool use_split_left_shift:1;        // |
	bool use_split_right_shift:1;       // |
	bool use_7u_spacebar:1;             // |
	bool use_iso_enter:1;               // |
	bool disable_when_usb_suspended:1;  // |
	bool disable_hhkb_blocker_leds:1;   // |
	bool __pad7:1;                      // 1 byte
	uint8_t disable_after_timeout;      // 1 byte
	uint8_t brightness;                 // 1 byte
	uint8_t effect;                     // 1 byte
	uint8_t effect_speed;				// 1 byte
	HS color_1;                         // 2 bytes
	HS color_2;                         // 2 bytes
	backlight_config_indicator caps_lock_indicator;	// 3 bytes
	backlight_config_indicator layer_1_indicator;	// 3 bytes
	backlight_config_indicator layer_2_indicator;	// 3 bytes
	backlight_config_indicator layer_3_indicator;	// 3 bytes
	uint16_t alphas_mods[5];            // 10 bytes
#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_M10_C)
	HS custom_color[RGB_BACKLIGHT_CUSTOM_COLORS_COUNT];                 // 12 or 20 bytes
#endif
} backlight_config;                // = 31 bytes (M6-B = 43 bytes, M10-C 51 bytes)

void backlight_config_load(void);
void backlight_config_save(void);
void backlight_config_set_value( uint8_t *data );
void backlight_config_get_value( uint8_t *data );

void backlight_init_drivers(void);

void backlight_timer_init(void);
void backlight_timer_enable(void);
void backlight_timer_disable(void);

void backlight_set_suspend_state(bool state);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void backlight_update_pwm_buffers(void);

// Handle backlight specific keycodes
bool process_record_backlight(uint16_t keycode, keyrecord_t *record);

void backlight_set_key_hit(uint8_t row, uint8_t col);

void backlight_effect_increase(void);
void backlight_effect_decrease(void);
void backlight_effect_speed_increase(void);
void backlight_effect_speed_decrease(void);

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

void backlight_test_led( uint8_t index, bool red, bool green, bool blue );
void backlight_debug_led(bool state);
void backlight_device_indication(uint8_t value);
