/* Copyright 2023 Your Name (@santy81855)
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

enum layers {
	_DVORAK,
	_GAMING,
	_SHIFT,
	_FN,
	_NUMBER,
	_ARROW,
};

enum custom_keycodes {
	GMAIL = SAFE_RANGE,
	WORK_EMAIL,
	DRAG_SCROLL,
	DRAG_SCROLL_V,
	DRAG_SCROLL_H,
	SB,
	CB,
};

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 15.0
#define SCROLL_DIVISOR_V 40.0

// variable used in the drag scroll functionality
bool set_scrolling = false;
bool set_scrolling_v = false;
bool set_scrolling_h = false;
// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v -= (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
	// Check if drag scrolling vertical is active
    if (set_scrolling_v) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_v -= (float)mouse_report.y / SCROLL_DIVISOR_V;
        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.v = (int8_t)scroll_accumulated_v;
        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
	// Check if drag scrolling horizontal is active
    if (set_scrolling_h) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;        
        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case GMAIL:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING("mynameissantiagogarcia@gmail.com");
			}
			break;
		case WORK_EMAIL:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING("santy@santiago-garcia.com");
			}
			break;
		case SB:
			if (record->event.pressed) {
				SEND_STRING("[]"SS_TAP(X_LEFT));
			}
			break;
		case CB:
			if (record->event.pressed) {
				SEND_STRING("{}"SS_TAP(X_LEFT));
			}
			break;
		case DRAG_SCROLL:
			set_scrolling = record->event.pressed;
			break;
		case DRAG_SCROLL_V:
			set_scrolling_v = record->event.pressed;
			break;
		case DRAG_SCROLL_H:
			set_scrolling_h = record->event.pressed;
			break;
	}
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT(
	KC_F15, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_BSLS), LALT(KC_END), GMAIL, 
	KC_F16, KC_TAB, KC_SCLN, KC_COMMA, KC_DOT, KC_P, KC_Y, 		 		   		KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS, KC_LBRC, KC_RBRC, WORK_EMAIL, 
	KC_F17, KC_BSPC, KC_A, KC_O, KC_E, KC_U, KC_I, 		 						KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT, KC_TRNS, 
	KC_F18, MO(_SHIFT), KC_QUOTE, KC_Q, KC_J, KC_K, KC_X, 						KC_B, KC_M, KC_W, KC_V, KC_Z, MO(_SHIFT), KC_UP, 
	TO(_GAMING), KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), MO(_NUMBER), KC_TRNS,		KC_SPACE, MO(_ARROW), KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	),

	[_GAMING] = LAYOUT(
	LALT(KC_END), KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 						 	KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, LALT(KC_END), KC_TRNS, 
	KC_F9, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 		 		   						KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS, KC_LBRC, KC_RBRC, KC_TRNS, 
	KC_F3, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, 		 								KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOTE, KC_ENT, RGB_TOG, 
	KC_F4, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 										KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSFT, KC_UP, 
	TO(_DVORAK), KC_LCTL, KC_LGUI, KC_LALT, KC_2, KC_SPACE, KC_TRNS,					KC_SPACE, KC_SPACE, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	),

	[_SHIFT] = LAYOUT(
	KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TILD,
	KC_TRNS, LSFT(KC_TAB), KC_COLN, LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_P), LSFT(KC_Y), 	LSFT(KC_F), LSFT(KC_G), LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), LSFT(KC_BSLS), LSFT(KC_LBRC), LSFT(KC_RBRC), KC_GRV,
	KC_TRNS, LCTL(KC_BSPC), LSFT(KC_A), LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I),     LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS, LSFT(KC_ENT), KC_TRNS,
	KC_TRNS, KC_SLASH, KC_DQUO, LSFT(KC_Q), LSFT(KC_J), LSFT(KC_K), LSFT(KC_X), 			LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), KC_EQL, KC_TRNS,
    TO(_GAMING), KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), MO(_NUMBER), KC_TRNS,			 		KC_SPACE, KC_LGUI, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	),

	[_FN] = LAYOUT(
	KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_END), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_SCLN, CB, SB, LALT(KC_F4), LCTL(KC_L), 		 		 	 LCTL(KC_F), KC_PGUP, KC_UP, LCTL(KC_T), LCTL(KC_N), LCTL(LSFT(KC_N)), RGB_TOG, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_BSPC, LCTL(KC_A), LCTL(KC_X), LCTL(KC_C), KC_LSFT, LCTL(KC_V), 				 KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, LCTL(KC_S), KC_END, LCTL(KC_GRV), KC_TRNS,
	KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 						  	 KC_TRNS, KC_PGDN, LCTL(KC_W), LCTL(LSFT(KC_T)), KC_DEL, KC_LGUI, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS,			 				 KC_LCTL, KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(LCTL(KC_LEFT)), KC_TRNS, LGUI(LCTL(KC_RIGHT))
	),

	[_NUMBER] = LAYOUT(
	KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_GRV, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), 		 	LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_BSPC, KC_1, KC_2, KC_3, KC_4, KC_5, 		 								KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_ENTER, KC_TRNS,
	KC_TRNS, LSFT(KC_SLASH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					LSFT(KC_LBRC), LSFT(KC_RBRC), KC_LBRC, KC_RBRC, KC_TRNS, LSFT(KC_EQL), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,			 				KC_SPACE, MO(_ARROW), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[_ARROW] = LAYOUT(
	KC_TRNS, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 							KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LGUI(LSFT(KC_S)), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		 		   		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		 				LCTL(KC_BTN1), KC_BTN1, KC_BTN2, DRAG_SCROLL_V, DRAG_SCROLL_H, KC_TRNS, LCTL(LALT(KC_O)), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 						LCTL(KC_BTN1), LCTL(KC_BTN1), KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI, RGB_TOG,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WBAK, KC_WFWD, KC_TRNS,			 			KC_F5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DVORAK] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(C(KC_PGUP), C(KC_PGDN))  },
    [_GAMING] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_SHIFT] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_FN] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(C(LGUI(KC_QUOTE)), LGUI(KC_QUOTE)) },
	[_NUMBER] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_ARROW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
};
#endif