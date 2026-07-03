/*
Copyright 2018 Cole Markham

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

enum custom_keycodes {
    WK_RED = SAFE_RANGE,
    WK_GREEN,
    WK_BLUE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_ESC,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_TAB,
        MO(1),   KC_P0,   KC_PDOT, KC_ENT
    ),

    [1] = LAYOUT(
        _______, BL_STEP, RGB_M_SW, QK_BOOT,
        UG_TOGG, UG_NEXT, RGB_M_P,  RGB_M_SN,
        UG_HUEU, UG_SATU, UG_VALU,  RGB_M_K,
        UG_HUED, UG_SATD, UG_VALD,  RGB_M_X,
        _______, WK_RED,  WK_GREEN, WK_BLUE
    )
};

void keyboard_post_init_user(void) {
    rgblight_setrgb(0, 255, 0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WK_RED:
            if (record->event.pressed) {
                rgblight_show_solid_color(0xFF, 0x00, 0x00);
            } else {
                rgblight_show_solid_color(0xFF, 0xFF, 0xFF);
            }
            return false;
        case WK_GREEN:
            if (record->event.pressed) {
                rgblight_show_solid_color(0x00, 0xFF, 0x00);
            } else {
                rgblight_show_solid_color(0xFF, 0xFF, 0xFF);
            }
            return false;
        case WK_BLUE:
            if (record->event.pressed) {
                rgblight_show_solid_color(0x00, 0x00, 0xFF);
            } else {
                rgblight_show_solid_color(0xFF, 0xFF, 0xFF);
            }
            return false;
    }
    return true;
}
