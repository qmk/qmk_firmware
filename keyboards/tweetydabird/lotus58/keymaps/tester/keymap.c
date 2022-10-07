/* Copyright 2021 TweetyDaBird
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
    _QWERTY
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
//      											         _______       _______
//.----------.--------.--------.--------.--------.--------. /       \     /       \ .--------.--------.--------.--------.--------.----------.
//|  Esc     |   1    |   2    |   3    |   4    |   5    ||  Media  |   |  Media  ||   6    |   7    |   8    |   9    |   0    |    -     |
	KC_ESC,		KC_1,	KC_2,    KC_3,	  KC_4,	    KC_5,  	 KC_MPLY,      KC_MPLY,   KC_6, 	KC_7,	  KC_8,	  KC_9,		KC_0,	KC_MINS,
//|----------+--------+--------+--------+--------+--------| \_______/     \_______/ |--------+--------+--------+--------+--------+----------|
//|   Tab    |   Q    |   W    |   E    |   R    |   T    |                         |   Y    |   U    |   I    |   O    |   P    |   [ (Å)  |
    KC_TAB,		KC_Q,	KC_W,	 KC_E,	  KC_R,		KC_T,							  KC_Y,		KC_U,	  KC_I,	  KC_O,		KC_P,	 KC_LBRC,
//|----------+--------+--------+--------+--------+--------|                         |--------+--------+--------+--------+--------+----------|
//|  Capslk  |   A    |   S    |   D    |   F    |   G    |                         |   H    |   J    |   K    |   L    |  ; (Ö) |   ' (Ä)  |
	KC_CAPS,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,								 KC_H,	KC_J,	   KC_K,	KC_L,	KC_SCLN,  KC_QUOT,
//|----------+--------+--------+--------+--------+--------+----------.   .----------+--------+--------+--------+--------+--------+----------|
//|   Ctrl   |   Z    |   X    |   C    |   V    |   B    |   RGB    |   |   RGB    |   N    |   M    |   ,    |   .    |   /    |   Ctrl   |
	KC_LCTRL, 	KC_Z, 	 KC_X,    KC_C,   KC_V,    KC_B, 	RGB_TOG,       RGB_TOG,   KC_N,		KC_M,   KC_COMM, KC_DOT, KC_SLSH,  KC_RCTRL,
//'----------'--------'--------+--------+--------+--------+-.--------'   '--------.-+--------+--------+--------+--------'--------'----------'
//                             |  Win   | Down   |  Alt   |/ Space  /     \  Enter \|  AltGr |   Up   |  Bksp  |
								KC_LGUI, KC_DOWN, KC_LALT,  KC_SPC,          KC_ENT,  KC_RALT, KC_UP,   KC_BSPC
//                             '--------'--------'--------'--------'       '--------'--------'--------'--------'
	)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NUM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_SYS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif
