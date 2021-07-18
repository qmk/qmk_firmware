/* Copyright 2021 Benjamin Smith (@Merlin04)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#define TD_TH_COUNT 1
#define TD_TH_MAX_TAP 4

#include QMK_KEYBOARD_H
#include "tdth/tdth_macros.h"

enum {
    TD_FN
};

DEFINE_TD_STATES(TD_STATE(TD_FN));

DEFINE_TD_KEYCODES(TD_DEF(TD_FN, ARRAY_LITERAL({
    KC_ESC,
    KC_UNDEFINED,
    KC_UNDEFINED,
    KC_UNDEFINED
}), ARRAY_LITERAL({
    MO(1),
    MO(2),
    KC_LCTL,
    MO(3)
})));

// Need to include the c file instead of the header file so that it can access things in this file
#include "tdth/tdth.c"

DEFINE_TD_ACTIONS(TD_ACTION(TD_FN));

enum custom_keycodes {
    LOCK = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_BTN1, KC_BTN3, KC_BTN4,
        KC_BTN2, TD(TD_FN)
    ),
    [1] = LAYOUT(
        KC_ENT, KC_PASTE, KC_BTN5,
        KC_COPY, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_DOWN, KC_LEFT, KC_RIGHT,
        KC_UP, KC_TRNS
    ),
    [3] = LAYOUT(
        LOCK, KC_DEL, KC_BSPC,
        RESET, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOCK: {
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("l"));
            }
            break;
        }
    }
    return true;
};
