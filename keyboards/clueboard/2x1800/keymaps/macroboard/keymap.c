/* Copyright 2017 Zach White <skullydazed@gmail.com>
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
#include "2x1800.h"

enum custom_keycodes {
    MACRO01 = SAFE_RANGE,
    MACRO02,
    MACRO03,
    MACRO04,
    MACRO05,
    MACRO06,
    MACRO07,
    MACRO08,
    MACRO09,
    MACRO10,
    MACRO11,
    MACRO12,
    MACRO13,
    MACRO14,
    MACRO15,
    MACRO16,
    MACRO17,
    MACRO18,
    MACRO19,
    MACRO20,
    MACRO21,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
      MACRO01, MACRO02, MACRO03, MACRO04,       KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,   KC_F11,  KC_F12,        KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,  \
                                                                                                                                                                                                                      \
      MACRO05, MACRO06, MACRO07, MACRO08,      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,     KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
      MACRO09, MACRO10, MACRO11, MACRO12,      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS,       KC_P7, KC_P8, KC_P9, KC_PSLS,       \
               MACRO13, MACRO14, MACRO15,      KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_QUOT, KC_ENT,         KC_P4, KC_P5, KC_P6,                \
      MACRO16, MACRO17, MACRO18, MACRO19,   KC_UP,  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_SLSH, KC_COMM, KC_DOT,   KC_RSFT,      KC_UP,      KC_P1, KC_P2, KC_P3, KC_PENT,       \
               MACRO20, MACRO21,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_RGUI, KC_APP, KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_P0, KC_PDOT               \
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case MACRO01:
                SEND_STRING("This is macro 01");
                return false;
            case MACRO02:
                SEND_STRING("This is macro 02");
                return false;
            case MACRO03:
                SEND_STRING("This is macro 03");
                return false;
            case MACRO04:
                SEND_STRING("This is macro 04");
                return false;
            case MACRO05:
                SEND_STRING("This is macro 05");
                return false;
            case MACRO06:
                SEND_STRING("This is macro 06");
                return false;
            case MACRO07:
                SEND_STRING("This is macro 07");
                return false;
            case MACRO08:
                SEND_STRING("This is macro 08");
                return false;
            case MACRO09:
                SEND_STRING("This is macro 09");
                return false;
            case MACRO10:
                SEND_STRING("This is macro 10");
                return false;
            case MACRO11:
                SEND_STRING("This is macro 11");
                return false;
            case MACRO12:
                SEND_STRING("This is macro 12");
                return false;
            case MACRO13:
                SEND_STRING("This is macro 13");
                return false;
            case MACRO14:
                SEND_STRING("This is macro 14");
                return false;
            case MACRO15:
                SEND_STRING("This is macro 15");
                return false;
            case MACRO16:
                SEND_STRING("This is macro 16");
                return false;
            case MACRO17:
                SEND_STRING("This is macro 17");
                return false;
            case MACRO18:
                SEND_STRING("This is macro 18");
                return false;
            case MACRO19:
                SEND_STRING("This is macro 19");
                return false;
            case MACRO20:
                SEND_STRING("This is macro 20");
                return false;
            case MACRO21:
                SEND_STRING("This is macro 21");
                return false;
        }
    }
    return true;
};
