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
// Set default RGB effect
// void matrix_init_user(void) { rgb_matrix_mode_noeeprom(RGB_MATRIX_SPLASH); }

uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(default_layer_state)) {
	case _COLEMAK: // Reactive key effects on Colemak layer
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_WHITE);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
		break;
	default: // Switch off RGB if no CAPS lock
		if (!(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) rgb_matrix_disable_noeeprom();
		break;
	}
	// Reactive key colour for layers
	switch (biton32(state)) {
	case _ADJUST:
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
		break;
	case _RAISE:
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
		break;
	case _LOWER:
		rgb_matrix_enable_noeeprom();
		rgb_matrix_sethsv_noeeprom(HSV_BLUE);
		rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
		break;
	}
	return state;
}

void rgb_matrix_indicators_user(void) {
	// Light up held layer keys
	#if defined(KEYBOARD_bm40hsrgb)
	switch (get_highest_layer(layer_state)) {
	case _ADJUST: // purple
		rgb_matrix_set_color(40, 255, 0, 255);
		rgb_matrix_set_color(42, 255, 0, 255);
		break;
	case _RAISE: // yellow
		rgb_matrix_set_color(42, 255, 255, 0);
		break;
	case _LOWER: // blue
		rgb_matrix_set_color(40, 0, 0, 255);
		break;
	default: // off
		rgb_matrix_set_color(40, 0, 0, 0);
		rgb_matrix_set_color(42, 0, 0, 0);
		break;
	}
	#endif // defined(KEYBOARD_bm40hsrgb)

	// Light all keys for CAPS lock
	if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) rgb_matrix_set_color_all(255, 0, 0);

/*	// Light up non KC_TRANS or KC_NO on layers
	uint8_t layer = get_highest_layer(layer_state);
	if (layer != 0) {
		for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
			for (uint8_t col = 0; col < MATRIX_COLS; col++) {
				uint8_t led_index = g_led_config.matrix_co[row][col];
				keypos_t pos = { col, row };
				uint16_t keycode = keymap_key_to_keycode(layer, pos);
				bool keycode_set_on_layer = keycode != KC_TRNS && keycode != KC_NO;
				if (led_index != NO_LED && keycode_set_on_layer) rgb_matrix_set_color(led_index, 0xFF, 0xFF, 0xFF);
			}
		}
	} */
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
#ifdef RGB_MATRIX_ENABLE
void leader_start(void) { // Leader key effect
	rgb_matrix_enable_noeeprom();
	rgb_matrix_sethsv_noeeprom(HSV_BLUE);
	rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
}

void leader_end(void) { rgb_matrix_disable_noeeprom(); }
#endif // RGB_MATRIX_ENABLE
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

