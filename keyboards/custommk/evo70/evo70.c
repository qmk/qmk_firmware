/* Copyright 2021 customMK
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

#include "evo70.h"
#include <stdbool.h>

/* Encoder Parameters */
uint8_t enc_mode = 0;

#define ENCODER_MATRIX_ROW 5
#define ENCODER_MATRIX_COL 6

#define ENC_VOLUME 0
#define ENC_MEDIA 1
#define ENC_CUSTOM 2
#define ENC_BL_BRIGHT 3
#define ENC_RGB_BRIGHT 4
#define ENC_RGB_MODE 5
#define ENC_RGB_COLOR 6
#define ENC_SCROLL 7

uint8_t num_enc_modes = 8;
uint16_t enc_cw[] =  { KC_VOLU, KC_MEDIA_NEXT_TRACK, 0, 0, 0, 0, 0, KC_WH_D };
uint16_t enc_ccw[] = { KC_VOLD, KC_MEDIA_PREV_TRACK, 0, 0, 0, 0, 0, KC_WH_U };

void matrix_init_kb(void) {
	matrix_init_user();
}

__attribute__((weak)) void set_custom_encoder_mode_user(bool custom_encoder_mode) {}

void handle_encoder_switch_process_record(keyrecord_t *record) {

	if (record->event.pressed) {
		if (get_mods() & MOD_MASK_SHIFT) {
			enc_mode = (enc_mode + (num_enc_modes- 1)) % num_enc_modes;
		} else {
			enc_mode = (enc_mode + 1) % num_enc_modes;
		}
		set_custom_encoder_mode_user(enc_mode == ENC_CUSTOM);
	}
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	if (record->event.key.row == ENCODER_MATRIX_ROW && record->event.key.col == ENCODER_MATRIX_COL){
		handle_encoder_switch_process_record(record);
	}
	return process_record_user(keycode, record);
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    if (enc_mode == ENC_RGB_MODE) {
		if (clockwise) {
		    rgblight_step();
		} else {
            rgblight_step_reverse();
		}
	} else if (enc_mode == ENC_RGB_BRIGHT) {
		if (clockwise) {
		    rgblight_increase_val();
		} else {
            rgblight_decrease_val();
		}
	} else if (enc_mode == ENC_BL_BRIGHT) {
		if (clockwise) {
		    backlight_increase();
		} else {
            backlight_decrease();
		}
	} else if (enc_mode == ENC_RGB_COLOR) {
		if (clockwise) {
		    rgblight_increase_hue();
		} else {
            rgblight_decrease_hue();
		}
	} else {
		if (clockwise) {
			tap_code(enc_cw[enc_mode]);
		} else {
			tap_code(enc_ccw[enc_mode]);
		}
	}
	return true;
}
	

void matrix_scan_kb(void) {
	matrix_scan_user();
}

