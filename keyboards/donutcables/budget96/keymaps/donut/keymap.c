/*
Copyright 2020 DonutCables

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

enum layer_names {
    _BASE,
    _B,
    _FN1,
    _FN2,
};

enum custom_keycodes {
    img = SAFE_RANGE,
    xkcd,
    CD,
    AES,
    /* Unicode strings maps */
    ALT0,
    ALT1,
    ALT2,
    ALT3,
    ALT4,
    ALT5,
    ALT6,
    ALT7,
    /* Discord emotes maps */
    B,
    X,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_96_ansi(
	KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_INS, KC_END, KC_MPRV, KC_MPLY, KC_MNXT, 
	KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL, KC_PSCR, KC_PSLS, KC_PAST, 
	KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_P7, KC_P8, KC_P9, KC_PMNS, 
	MO(3), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS, 
	KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, 
	KC_LCTL, MO(2), KC_RALT, KC_SPC, KC_CALC, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT),

    /* (1) Bmode layer */
    [_B] = LAYOUT_96_ansi(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, B, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* (2) Fn 1 */
    [_FN1] = LAYOUT_96_ansi(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, TG(1), KC_PGUP, KC_VOLD, KC_MUTE, KC_VOLU, 
	ALT0, KC_TRNS, KC_TRNS, ALT1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ALT2, KC_TRNS, KC_TRNS, KC_NLCK, KC_TRNS, KC_TRNS, 
	KC_TRNS, CD, KC_TRNS, KC_TRNS, KC_TRNS, ALT3, KC_TRNS, KC_TRNS, KC_TRNS, ALT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, AES, xkcd, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_CLCK, KC_TRNS, X, KC_TRNS, img, B, KC_TRNS, ALT7, ALT5, ALT6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* (3) Fn 2 */
    [_FN2] = LAYOUT_96_ansi(
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UC_M_WC, EEP_RST, QK_BOOT, 
	VLK_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
	RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
	KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case xkcd:
            if (record->event.pressed) {
                SEND_STRING("https://xkcd.com/927/");
            }
            return true;
        case CD:
            if (record->event.pressed) {
                SEND_STRING("cd d:/keyboard_stuff/gits/qmk_firmware");
            }
            return true;
        case AES:
            if (record->event.pressed) {
                SEND_STRING("***A E S T H E T I C S***");
            }
            return true;
        case img:
            if (record->event.pressed) {
                SEND_STRING("[url=" SS_LCTL("v") "][img]" SS_LCTL("v") "[/img][/url]");
            }
            return true;
        case ALT0:
            if (record->event.pressed) {
                send_unicode_string("≈");
            }
            return true;
        case ALT1:
            if (record->event.pressed) {
                send_unicode_string("π");
            }
            return true;
        case ALT2:
            if (record->event.pressed) {
                send_unicode_string("±");
            }
            return true;
        case ALT3:
            if (record->event.pressed) {
                send_unicode_string("™");
            }
            return true;
        case ALT4:
            if (record->event.pressed) {
                send_unicode_string("Ω");
            }
            return true;
        case ALT5:
            if (record->event.pressed) {
                send_unicode_string("≤");
            }
            return true;
        case ALT6:
            if (record->event.pressed) {
                send_unicode_string("≥");
            }
            return true;
        case ALT7:
            if (record->event.pressed) {
                send_unicode_string("ゴ");
            }
            return true;
        case B:
            if (record->event.pressed) {
                SEND_STRING(":b:");
            }
            return true;
        case X:
            if (record->event.pressed) {
                SEND_STRING(":x:");
            }
            return true;
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
            if (layer_state_is(1)) {
                if (record->event.pressed) {
                    register_code(KC_F13);
                    tap_code(keycode);
                    unregister_code(KC_F13);
                }
            } else {
                return true;
            }
            return false;
    }
    return true;
}
