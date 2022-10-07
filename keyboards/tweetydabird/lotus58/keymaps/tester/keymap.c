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

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;
	}
    return rotation;
}

bool oled_task_user(void) {
	render_logo();
	return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_LEFT);
		} else {
			tap_code(KC_RIGHT);
            
        }
    }
    return true;
}

#endif