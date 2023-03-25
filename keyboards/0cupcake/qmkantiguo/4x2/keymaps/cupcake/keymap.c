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
  pdf = SAFE_RANGE,
  buscarx,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case pdf:
        if (record->event.pressed) {
            // when keycode pdf is pressed
            SEND_STRING(SS_TAP(X_LALT) SS_DELAY(15) SS_TAP(X_A) SS_DELAY(15) SS_TAP(X_X) SS_DELAY(15) SS_TAP(X_P) SS_DELAY(15) SS_TAP(X_V) SS_DELAY(15));
            SEND_STRING(SS_TAP(X_TAB) SS_DELAY(15) SS_TAP(X_TAB) SS_DELAY(15) SS_TAP(X_TAB) SS_DELAY(15) SS_TAP(X_TAB) SS_DELAY(15));
            SEND_STRING(SS_TAP(X_SPC) SS_DELAY(15) SS_TAP(X_TAB) SS_DELAY(15) SS_TAP(X_UP) SS_DELAY(15) SS_TAP(X_UP) SS_DELAY(15));
            SEND_STRING(SS_TAP(X_ENT) SS_DELAY(350));
        } else {
            // when keycode pdf is released
        }
        break;
    case buscarx:
        if (record->event.pressed) {
            // when keycode buscarx is pressed
            SEND_STRING("]buscarx*");
            } else {
            // when keycode buscarx is released
        }
        break;
    }
    return true; //macro pegar como valor
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x10(
    LCTL(KC_C),       LCTL(KC_V), 
    LCTL(KC_E),       LCTL(KC_N), 
    buscarx,          pdf,
    LSFT(LGUI(KC_S)), KC_MUTE         
    ),


  [1] = LAYOUT_ortho_4x10(
    KC_TRNS,  KC_TRNS,
    KC_TRNS, RESET,
    KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS
    )
};
