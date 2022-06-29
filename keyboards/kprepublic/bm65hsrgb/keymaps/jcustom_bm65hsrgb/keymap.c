/* Copyright 2021 bytesapart
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

enum{
	M_JQUERY = SAFE_RANGE,
	M_DIV,
	M_DIVEND,
	M_VDUMP,
	M_JSLOG,
	M_EMAIL_W,
	M_PW_W,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,  KC_BSPC,   KC_DEL,
         KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,  KC_BSLS, KC_PGUP,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_ENT,    KC_PGDN,
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,     KC_RSFT,     KC_UP,  MO(2),
        KC_LCTL,   KC_LGUI,   KC_LALT,                     KC_SPC,                         KC_RALT,   MO(1),          KC_LEFT, KC_DOWN,  KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRAVE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,   _______,
        _______,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,  _______, KC_HOME,
        _______,    M_JQUERY, M_DIV, M_DIVEND, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    KC_END,
        _______,      _______, _______, M_JSLOG, M_VDUMP,   _______, _______, _______, LCTL(KC_Z), LCTL(KC_Y), _______, C(KC_BSPC),KC_VOLU,  TO(0),
        _______,   _______,   _______,                    KC_UNDS,                         _______, _______,                _______, KC_VOLD,  TG(4)
    ),
    [2] = LAYOUT_65_ansi_blocker(
        RESET,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LALT(KC_F4),
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLCK, KC_BRK, KC_INS,  KC_PIPE, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    _______,
        _______,      M_EMAIL_W, M_PW_W, _______, _______,   _______, _______, _______, A(KC_LEFT), A(KC_LEFT), _______, C(KC_T),   _______,  TO(0),
        _______,   _______,   _______,                    _______,                       G(KC_E), TG(3),      C(S(KC_T)), _______,  C(KC_W)
    ),
    [3] = LAYOUT_65_ansi_blocker(
        KC_GRAVE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    _______,
        _______,      _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,   _______,  _______,
        _______,   _______,   _______,                    _______,                         _______, _______,      _______, _______,  _______
    ),
    [4] = LAYOUT_65_ansi_blocker(
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    _______,
        _______,      _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,   _______,  MO(7),
        _______,   KC_LALT,   KC_LGUI,                    _______,                         _______, MO(6),      _______, _______, _______
    ),
    [5] = LAYOUT_65_ansi_blocker(
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    _______,
        _______,      _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,   _______,  _______,
        _______,   _______,   _______,                    _______,                         _______, _______,      _______, _______, _______
    ),
    [6] = LAYOUT_65_ansi_blocker(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_HOME,
        _______,    M_JQUERY, M_DIV, M_DIVEND, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    KC_END,
        _______,      _______, _______, M_JSLOG, M_VDUMP,   _______, _______, _______, LWIN(KC_Z), LSFT(LWIN(KC_Z)), _______, _______,   KC_VOLU,  TO(0),
        _______,   _______,   _______,                    KC_UNDS,                                        _______, _______,      _______, KC_VOLD, TO(0)
    ),
    [7] = LAYOUT_65_ansi_blocker(
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    _______,
        _______,      M_EMAIL_W, M_PW_W, _______, _______,   _______, _______, _______, A(KC_LEFT), A(KC_RIGHT), _______, LGUI(KC_T),   _______,  _______,
        _______,   _______,   _______,                    _______,                         _______, LGUI(A(KC_ESC)),      LGUI(S(KC_T)), _______, LGUI(KC_W)
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	if (record->event.pressed) {
		switch(keycode){
			case M_JQUERY:
				SEND_STRING("$('')");
				return false; break;
			case M_DIV:
				SEND_STRING("<div>");
				return false; break;
			case M_DIVEND:
				SEND_STRING("</div>");
				return false; break;
			case M_VDUMP:
				SEND_STRING("var_dump();");
				return false; break;
			case M_JSLOG:
				SEND_STRING("console.log();");
				return false; break;
			case M_EMAIL_W:
				SEND_STRING("");	//DO NOT COMMIT THESE LINES !!!
				return false; break;
			case M_PW_W:
				SEND_STRING("");	//DO NOT COMMIT THESE LINES !!!
				return false; break;
		}
	}
	return true;
};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

	if (host_keyboard_led_state().caps_lock) {
		RGB_MATRIX_INDICATOR_SET_COLOR(30, 64, 32, 32);          //	caps_lock
	}else{
        RGB_MATRIX_INDICATOR_SET_COLOR(30, 0, 0, 0);          //	caps_lock
    }
	switch(biton32(layer_state)){
		case 1:																						//	layer 1 indicators
			RGB_MATRIX_INDICATOR_SET_COLOR(64, 170, 170, 170); 	        //	left arrow
            RGB_MATRIX_INDICATOR_SET_COLOR(66, 64, 32, 32); 	        //	right arrow

            RGB_MATRIX_INDICATOR_SET_COLOR(19, 64, 32, 32);             // T
            RGB_MATRIX_INDICATOR_SET_COLOR(20, 64, 64, 64);             // Y
            RGB_MATRIX_INDICATOR_SET_COLOR(21, 64, 64, 64);             // U
            RGB_MATRIX_INDICATOR_SET_COLOR(22, 64, 32, 32);             // I

			break;
		case 2:																						//	layer 2 indicators
            if (host_keyboard_led_state().scroll_lock) {
                RGB_MATRIX_INDICATOR_SET_COLOR(25, 255, 255, 255);		//	scroll_lock
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(25, 64, 32, 32);
            }
			RGB_MATRIX_INDICATOR_SET_COLOR(26, 64, 32, 32);		        //	break
			RGB_MATRIX_INDICATOR_SET_COLOR(27, 64, 32, 32);		        //	insert
            RGB_MATRIX_INDICATOR_SET_COLOR(53, 255, 255, 255);	        //	<
            RGB_MATRIX_INDICATOR_SET_COLOR(54, 255, 255, 255);      	//	>
			RGB_MATRIX_INDICATOR_SET_COLOR(55, 255, 255, 255);	        //	right shift
			RGB_MATRIX_INDICATOR_SET_COLOR(64, 255, 255, 255); 	        //	left arrow
			RGB_MATRIX_INDICATOR_SET_COLOR(66, 255, 255, 255);	        //	right arrow
			break;
		case 3:																						//	layer 3 indicators
			// RGB_MATRIX_INDICATOR_SET_COLOR(13, 255, 255, 255);	        //	backspace / `~
            RGB_MATRIX_INDICATOR_SET_COLOR(1, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(2, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(3, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(4, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(5, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(6, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(7, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(8, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(9, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(10, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(11, 64, 32, 32);
            RGB_MATRIX_INDICATOR_SET_COLOR(12, 64, 32, 32);
			break;
		case 4:																						//	layer 4 indicators
			RGB_MATRIX_INDICATOR_SET_COLOR(14, 64, 32, 32);	        //	backspace / `~
			break;
        case 5:																						//	layer 5 indicators
            // if (host_keyboard_led_state().num_lock) {
            //     RGB_MATRIX_INDICATOR_SET_COLOR(1, 255, 255, 255);       //  num_lock or 1

            //     RGB_MATRIX_INDICATOR_SET_COLOR(15, 200, 200, 200);      //  numpad 7 or q
            //     RGB_MATRIX_INDICATOR_SET_COLOR(16, 200, 200, 200);      //  numpad 8 or w1
            //     RGB_MATRIX_INDICATOR_SET_COLOR(17, 200, 200, 200);      //  numpad 9 or e
            //     RGB_MATRIX_INDICATOR_SET_COLOR(29, 200, 200, 200);      //  numpad 4 or q
            //     RGB_MATRIX_INDICATOR_SET_COLOR(30, 200, 200, 200);      //  numpad 5 or w
            //     RGB_MATRIX_INDICATOR_SET_COLOR(31, 200, 200, 200);      //  numpad 6 or e
            //     RGB_MATRIX_INDICATOR_SET_COLOR(42, 200, 200, 200);      //  numpad 1 or z
            //     RGB_MATRIX_INDICATOR_SET_COLOR(43, 200, 200, 200);      //  numpad 2 or x
            //     RGB_MATRIX_INDICATOR_SET_COLOR(44, 200, 200, 200);      //  numpad 3 or c
            //     RGB_MATRIX_INDICATOR_SET_COLOR(56, 200, 200, 200);      //  numpad 0 or l alt
            //     RGB_MATRIX_INDICATOR_SET_COLOR(45, 200, 200, 200);      //  numpad . or v
	        // } else {
            //     RGB_MATRIX_INDICATOR_SET_COLOR(1, 64, 32, 32);          //  num_lock or 1

            //     RGB_MATRIX_INDICATOR_SET_COLOR(15, 64, 32, 32);         //  numpad 7 or q
            //     RGB_MATRIX_INDICATOR_SET_COLOR(16, 64, 32, 32);         //  numpad 8 or w
            //     RGB_MATRIX_INDICATOR_SET_COLOR(17, 64, 32, 32);         //  numpad 9 or e
            //     RGB_MATRIX_INDICATOR_SET_COLOR(29, 64, 32, 32);         //  numpad 4 or q
            //     RGB_MATRIX_INDICATOR_SET_COLOR(30, 64, 32, 32);         //  numpad 5 or w
            //     RGB_MATRIX_INDICATOR_SET_COLOR(31, 64, 32, 32);         //  numpad 6 or e
            //     RGB_MATRIX_INDICATOR_SET_COLOR(42, 64, 32, 32);         //  numpad 1 or z
            //     RGB_MATRIX_INDICATOR_SET_COLOR(43, 64, 32, 32);         //  numpad 2 or x
            //     RGB_MATRIX_INDICATOR_SET_COLOR(44, 64, 32, 32);         //  numpad 3 or c
            //     RGB_MATRIX_INDICATOR_SET_COLOR(56, 64, 32, 32);         //  numpad 0 or l alt
            //     RGB_MATRIX_INDICATOR_SET_COLOR(45, 64, 32, 32);         //  numpad . or v
            // }
			// RGB_MATRIX_INDICATOR_SET_COLOR(14, 255, 255, 255);	        //	tab indicator for numpad

            // RGB_MATRIX_INDICATOR_SET_COLOR(2, 64, 32, 32);              //  numpad divide or 2
            // RGB_MATRIX_INDICATOR_SET_COLOR(3, 64, 32, 32);              //  numpad times or 3
            // RGB_MATRIX_INDICATOR_SET_COLOR(4, 64, 32, 32);              //  backspace or 4
            // RGB_MATRIX_INDICATOR_SET_COLOR(18, 64, 32, 32);             //  numpad minus or r
            // RGB_MATRIX_INDICATOR_SET_COLOR(32, 64, 32, 32);             //  numpad plus or f

			break;
        case 6:
            RGB_MATRIX_INDICATOR_SET_COLOR(14, 64, 32, 32);	            //	backspace / `~
            RGB_MATRIX_INDICATOR_SET_COLOR(66, 255, 32, 32); 	        //	right arrow
            RGB_MATRIX_INDICATOR_SET_COLOR(31, 255, 128, 0);            // A
            RGB_MATRIX_INDICATOR_SET_COLOR(32, 255, 128, 0);            // S
            RGB_MATRIX_INDICATOR_SET_COLOR(33, 255, 128, 0);            // D
            RGB_MATRIX_INDICATOR_SET_COLOR(47, 0, 204, 204);            // C
            RGB_MATRIX_INDICATOR_SET_COLOR(48, 255, 128, 0);            // V
            break;
        case 7:
            RGB_MATRIX_INDICATOR_SET_COLOR(14, 64, 32, 32);	            //	backspace / `~
            RGB_MATRIX_INDICATOR_SET_COLOR(52, 255, 255, 255);	        //	<
            RGB_MATRIX_INDICATOR_SET_COLOR(53, 255, 255, 255);      	//	>
			RGB_MATRIX_INDICATOR_SET_COLOR(54, 255, 255, 255);	        //	right shift
			RGB_MATRIX_INDICATOR_SET_COLOR(64, 255, 255, 255); 	        //	left arrow
			RGB_MATRIX_INDICATOR_SET_COLOR(66, 255, 255, 255);	        //	right arrow
            break;
	}
}
