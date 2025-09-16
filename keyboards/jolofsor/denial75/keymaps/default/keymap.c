/* Copyright 2021 Johannes Paolo Soriano (https://github.com/jolofsor)
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

enum custom_keycodes {
    LEDRED = SAFE_RANGE,
    LEDBLUE,
    LEDYELLOW,
    LEDORANGE,
    LEDGREEN,
    LEDPURPLE,
    LEDWHITE,
    LEDPINK,
    LEDBLACK
};

//this function sets RGB to last set before it was disconnected
void keyboard_post_init_user(void) {
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LEDRED:
        if (record->event.pressed) {
            rgblight_enable();
            rgblight_sethsv(HSV_RED);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        } else {
        }
        break;

    case LEDBLUE:
        if (record->event.pressed) {
            rgblight_enable();
            rgblight_sethsv(HSV_BLUE);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        } else {
        }
        break;

    case LEDYELLOW:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_YELLOW);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;

    case LEDORANGE:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_ORANGE);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;

    case LEDGREEN:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_GREEN);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;

    case LEDPURPLE:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_PURPLE);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;

    case LEDWHITE:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_WHITE);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;

    case LEDPINK:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_PINK);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;

    case LEDBLACK:
        if (record->event.pressed) {
           rgblight_enable();
           rgblight_sethsv(HSV_BLACK);
           rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_75_ansi(
	    KC_ESC,   KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,  KC_INS,   KC_DEL,
    	KC_GRV,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,            KC_BSPC,  KC_HOME,
    	KC_TAB,            KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,  KC_PGUP,
    	KC_CAPS,  	       KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,             KC_PGDN,
   		KC_LSFT,  KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,         KC_RSFT,           KC_UP,    KC_END,
    	KC_LCTL,  KC_LGUI, KC_LALT,                KC_SPC,                          KC_RALT, MO(1),           KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT
	),

	[1] = LAYOUT_75_ansi(
	    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
    	KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,    KC_BRIU,
    	KC_NO,            LEDRED,  LEDBLUE,  LEDYELLOW,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_BRID,
    	KC_NO,  	      LEDORANGE,   LEDGREEN,  LEDPURPLE,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              UG_VALU,
   		 KC_NO,  LEDWHITE,   LEDPINK,  LEDBLACK,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,            KC_NO,    KC_NO,    UG_VALD,
    	KC_NO,   KC_NO, 	   KC_NO,                  KC_NO,                           KC_NO,  KC_TRNS,  UG_TOGG, KC_NO,    KC_NO,    KC_NO
	)
};
