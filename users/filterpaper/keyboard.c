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

#ifdef RGB_MATRIX_ENABLE

#ifdef KEYBOARD_bm40hsrgb
layer_state_t layer_state_set_user(layer_state_t state) {

	switch (biton32(default_layer_state)) {
	case _COLEMAK: // RGB effect for Colemak default layer
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_WHITE);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
		break;
	default: // Disable RGB if no CAPS lock on
		if (!host_keyboard_led_state().caps_lock) rgb_matrix_disable_noeeprom();
	}

	// RGB effects for layers
	switch (biton32(state)) {
	case _ADJUST:
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_TEAL);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_WIDE);
		break;
	case _RAISE:
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_WIDE);
		break;
	case _LOWER:
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_BLUE);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_WIDE);
		break;
	}
	
	return state;
}
#endif // KEYBOARD_bm40hsrgb


void rgb_matrix_indicators_user(void) {

	// Light up held layer layers
	switch (get_highest_layer(layer_state)) {
#ifdef KEYBOARD_bm40hsrgb
	case _ADJUST:
		rgb_matrix_set_color(42, RGB_TEAL);
		rgb_matrix_set_color(40, RGB_TEAL);
		break;
	case _RAISE:
		rgb_matrix_set_color(42, RGB_YELLOW);
		break;
	case _LOWER:
		rgb_matrix_set_color(40, RGB_BLUE);
		break;
	default:
		if (host_keyboard_led_state().caps_lock) {
			rgb_matrix_set_color_all(RGB_ORANGE);
		} else {
			rgb_matrix_set_color(42, RGB_OFF);
			rgb_matrix_set_color(40, RGB_OFF);	
		}		
#else
	case _ADJUST:
		rgb_matrix_set_color_all(RGB_TEAL);
		break;
	case _RAISE:
		rgb_matrix_set_color_all(RGB_YELLOW);
		break;
	case _LOWER:
		rgb_matrix_set_color_all(RGB_BLUE);
		break;
	default:
		if (host_keyboard_led_state().caps_lock) rgb_matrix_set_color_all(RGB_ORANGE);
		else                                     rgb_matrix_set_color_all(RGB_OFF);
#endif // KEYBOARD_bm40hsrgb
	}

/*	// Light up non KC_TRANS / KC_NO on layers
	#if defined(KEYBOARD_bm40hsrgb)
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
					default:
						break;
					}
				}
			}
		}
	}
	#endif */
}
#endif // RGB_MATRIX_ENABLE


// Leader key macros
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

// Enable leader key light effects
#if defined(RGB_MATRIX_ENABLE) && defined(KEYBOARD_bm40hsrgb)
void leader_start(void) { // Leader key effect
	rgb_matrix_enable_noeeprom();
	rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
	rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_WIDE);
}
// Turn off leader key effect is no capslock
void leader_end(void) { if (!host_keyboard_led_state().caps_lock) rgb_matrix_disable_noeeprom(); }
#endif // RGB_MATRIX_ENABLE && KEYBOARD_bm40hsrgb

#endif // LEADER_ENABLE


// Render OLED display
#ifdef OLED_DRIVER_ENABLE
#include "mod-status.c"
#include "bongo-cat.c"

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

// Setup defaults when EEPROM is reset
void eeconfig_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
	rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
#endif

#ifdef RGBLIGHT_ENABLE
	rgblight_mode(RGBLIGHT_MODE_BREATHING);
#endif

#ifdef BACKLIGHT_ENABLE
	backlight_enable();
	backlight_level(BACKLIGHT_LEVELS);
#endif
}
