/*
Copyright 2021 andys8 <andys8@users.noreply.github.com>

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
#include "sendstring_german.h"

enum custom_keycodes {
    GIT_STASH = SAFE_RANGE,
    GIT_STASH_POP,
    GIT_COMMIT,
    COPY_PASTE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GIT_STASH:
            if (record->event.pressed) {
                SEND_STRING("git stash\n");
            }
            break;
        case GIT_STASH_POP:
            if (record->event.pressed) {
                SEND_STRING("git stash pop\n");
            }
            break;
        case GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git add -A && git commit -a\n");
            }
            break;
        case COPY_PASTE:
            if (record->event.pressed) {
                tap_code16(C(KC_C));
            } else {
                tap_code16(C(KC_V));
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(GIT_STASH, GIT_STASH_POP, GIT_COMMIT,
               LCTL(KC_F4), LT(1, KC_SPACE), LCTL(KC_F6),
               COPY_PASTE, LCTL(KC_F2), LCTL(KC_F3)),

  [1] = LAYOUT(RGB_RMOD, RGB_TOG, RGB_MOD,
               RGB_HUI, KC_TRNS, RGB_SAI,
               RGB_HUD, RGB_M_P, RGB_SAD),

};
