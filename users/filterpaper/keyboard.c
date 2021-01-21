/* Copyright (C) 2021 @filterpaper
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
 
#include QMK_KEYBOARD_H

// Layer number reference
enum layers {
  _QWERTY = 0,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};


/////// RGB LIGHTING ///////
#ifdef RGB_MATRIX_ENABLE

void matrix_init_user(void) {
	rgb_matrix_sethsv_noeeprom(HSV_DEFAULT);
	rgb_matrix_mode_noeeprom(MATRIX_NORMAL);
}

#ifdef KEYBOARD_bm40hsrgb
layer_state_t layer_state_set_user(layer_state_t state) {

	// Default layer keypress effects
	switch (get_highest_layer(default_layer_state)) {
		case _COLEMAK:
			rgb_matrix_mode_noeeprom(MATRIX_SPECIAL);
			break;
		case _QWERTY:
			rgb_matrix_mode_noeeprom(MATRIX_NORMAL);
			break;
	}
	return state;
}
#endif // KEYBOARD_bm40hsrgb

void rgb_matrix_indicators_user(void) {

	// Layer lighting
	switch (get_highest_layer(layer_state)) {
#ifdef KEYBOARD_bm40hsrgb
		case _LOWER:
			//rgb_matrix_sethsv_noeeprom(HSV_LOWER);
			rgb_matrix_set_color(40, RGB_LOWER);
			break;
		case _RAISE:
			//rgb_matrix_sethsv_noeeprom(HSV_RAISE);
			rgb_matrix_set_color(42, RGB_RAISE);
			break;
		case _ADJUST:
			//rgb_matrix_sethsv_noeeprom(HSV_ADJUST);
			rgb_matrix_set_color(42, RGB_ADJUST);
			rgb_matrix_set_color(40, RGB_ADJUST);
			break;
		default:
			rgb_matrix_sethsv_noeeprom(HSV_DEFAULT);
			if (host_keyboard_led_state().caps_lock) {
				rgb_matrix_set_color_all(RGB_DEFAULT);
			} else {
				rgb_matrix_set_color(42, RGB_OFF);
				rgb_matrix_set_color(40, RGB_OFF);	
			}
#else // Backlight for non RGB matrix board
		case _LOWER:
			rgb_matrix_set_color_all(RGB_LOWER);
			break;
		case _RAISE:
			rgb_matrix_set_color_all(RGB_RAISE);
			break;
		case _ADJUST:
			rgb_matrix_set_color_all(RGB_ADJUST);
			break;
		default:
			if (host_keyboard_led_state().caps_lock || get_highest_layer(default_layer_state) == _COLEMAK) {
				rgb_matrix_set_color_all(RGB_DEFAULT);
			} else {
				rgb_matrix_set_color_all(RGB_OFF);
			}
#endif // KEYBOARD_bm40hsrgb
	}

/*	// Light up non KC_TRANS / KC_NO on layers
#ifdef KEYBOARD_bm40hsrgb
	uint8_t layer = get_highest_layer(layer_state);
	if (layer >1) {
		for (uint8_t row = 0; row <MATRIX_ROWS; row++) {
			for (uint8_t col = 0; col <MATRIX_COLS; col++) {
				uint8_t led_index = g_led_config.matrix_co[row][col];
				keypos_t pos = { col, row };
				uint16_t keycode = keymap_key_to_keycode(layer, pos);
				if (led_index !=NO_LED && keycode !=KC_TRNS && keycode !=KC_NO) {
					switch (layer) {
						case _ADJUST:
							rgb_matrix_set_color(led_index, RGB_PURPLE);
							break;
						case _RAISE:
							rgb_matrix_set_color(led_index, RGB_YELLOW);
							break;
						case _LOWER:
							rgb_matrix_set_color(led_index, RGB_BLUE);
							break;
					}
				}
			}
		}
	}
#endif // KEYBOARD_bm40hsrgb */

}
#endif // RGB_MATRIX_ENABLE


/////// LEADER KEY MACROS ///////
#ifdef LEADER_ENABLE
LEADER_EXTERNS();
void matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		leading = false;
		leader_end();
		SEQ_ONE_KEY(KC_P) { SEND_STRING("()"); }
		SEQ_ONE_KEY(KC_B) { SEND_STRING("{}"); }
		SEQ_ONE_KEY(KC_Q) { SEND_STRING(":q!"); }
		SEQ_ONE_KEY(KC_W) { SEND_STRING(":wq"); }
		SEQ_ONE_KEY(KC_Z) { SEND_STRING("ZZ"); }
	}
}

// Enable leader key effects
#if defined(RGB_MATRIX_ENABLE) && defined(KEYBOARD_bm40hsrgb)
void leader_start(void) {
	rgb_matrix_mode_noeeprom(MATRIX_SPECIAL);
}
void leader_end(void) { 
	rgb_matrix_mode_noeeprom(MATRIX_NORMAL);
}
#endif // RGB_MATRIX_ENABLE && KEYBOARD_bm40hsrgb
#endif // LEADER_ENABLE


/////// OLED DISPLAY RENDERING ///////
#ifdef OLED_DRIVER_ENABLE
#include "mod-status.c" // For render_mod_status();
#include "bongo-cat.c"  // For animate_cat();

// Orientate OLED display
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	if (is_keyboard_master())    return OLED_ROTATION_270;
	else if (is_keyboard_left()) return OLED_ROTATION_0;
	else                         return OLED_ROTATION_180;
}

// Render status modules on both OLED
void oled_task_user(void) {
	if (is_keyboard_master()) render_mod_status();
	else                      animate_cat();
}
#endif // OLED_DRIVER_ENABLE


/////// INIT AND SUSPENSION ///////
// Handling keyboard suspension
void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
	rgb_matrix_set_suspend_state(true);
#endif

#ifdef OLED_DRIVER_ENABLE
	oled_off();
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
	rgb_matrix_set_suspend_state(false);
#endif
}

