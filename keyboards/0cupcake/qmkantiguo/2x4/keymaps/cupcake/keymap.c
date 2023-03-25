/*
Copyright 2020 Pabile

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
enum custom_keycodes{
  M1 = SAFE_RANGE,
  SumaPos,
  SumaNeg,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M1:
        if (record->event.pressed) {
            // when keycode M1 is pressed
            SEND_STRING(SS_TAP(X_LALT) SS_DELAY(45) SS_TAP(X_O) SS_DELAY(45) SS_TAP(X_V) SS_DELAY(45) SS_TAP(X_V));
            } else {
            // when keycode M1 is released
        }
        break;
    case SumaPos:
        if (record->event.pressed) {
            // when keycode SumaPos is pressed
            SEND_STRING("=suma(");
            } else {
            // when keycode SumaPos is released
        }
        break;
    case SumaNeg:
        if (record->event.pressed) {
            // when keycode SumaNeg is pressed
            SEND_STRING("-suma(");
            } else {
            // when keycode SumaNeg is released
        }
        break;
    }
    return true; //macro pegar como valor
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x10(
    LSFT(LGUI(KC_S)), LCTL(KC_X), LCTL(KC_V), SumaPos,
    MO(1),            LCTL(KC_C), M1,         SumaNeg
    ),

  [1] = LAYOUT_ortho_4x10(
    KC_TRNS,  KC_TRNS, KC_TRNS, RESET,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    )
};
