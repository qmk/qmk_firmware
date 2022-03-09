/*
Copyright 2021 Richard Snijder
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;
uint16_t enter_timer;

//extern rgblight_config_t rgblight_config;

// Define custom keycodes
enum my_keycodes {
	KC_CCCV = SAFE_RANGE,
	KC_2ENTER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        //Layer 0 - Base Layer (F13 to F24, and One Shot Layer 1,2,3,4)
        [0] = LAYOUT_ortho_4x4(
                KC_F13, KC_F14, KC_F15, KC_F16,
                KC_F17, KC_F18, KC_F19, KC_F20,
                KC_F21, KC_F22, KC_F23, KC_F24,
                TO(1), OSL(2), OSL(3),  LCA(KC_J)    //Transparent to let you go between layers
		),

        [1] = LAYOUT_ortho_4x4(
                LALT(KC_KP_1), LALT(KC_KP_2), LALT(KC_KP_3), LALT(KC_KP_4),
                LALT(KC_KP_5), LALT(KC_KP_6), LALT(KC_KP_7), LALT(KC_KP_8),
                LALT(KC_KP_9), LALT(KC_A), LALT(KC_B), LALT(KC_C),
                TO(2),LALT(KC_D),LALT(KC_E),LALT(KC_F)         //Transparent to let you go between layers
        ),

        //Layer 2 - Shift + Function Key Layer
        [2] = LAYOUT_ortho_4x4(
                LCA(KC_F1), LCA(KC_F2), LCA(KC_F3), LCA(KC_F4),
                LCA(KC_F5), LCA(KC_F6), LCA(KC_F7), LCA(KC_F8),
                LCA(KC_F9), LCA(KC_F10),LCA(KC_F11),LCA(KC_F12),
				TO(3),         LCA(KC_D), LCA(KC_E), LCA(KC_F)         //Transparent to let you go between layers
        ),

        //Layer 3 - Control + Function Key
        [3] = LAYOUT_ortho_4x4(
                LCA(KC_F13), LCA(KC_F14), LCA(KC_F15), LCA(KC_F16),
                LCA(KC_F17), LCA(KC_F18), LCA(KC_F19), LCA(KC_F20),
                LCA(KC_F21), LCA(KC_F22),LCA(KC_F23),LCA(KC_F24),
				TO(0),         LCA(KC_G), LCA(KC_H), LCA(KC_I)          //Transparent to let you go between layers
        ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else {  // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            } return true;
		case KC_2ENTER:
		    if (record->event.pressed) {
                enter_timer = timer_read();
            } else {
                if (timer_elapsed(enter_timer) > TAPPING_TERM) {  // Hold, shift+enter
                    tap_code16(LSFT(KC_ENTER));
                } else {  // Tap, enter
                    tap_code16(KC_F24);
                }
            } 
			return true;
        default:
            return true;
    }
}


