/* Copyright 2021 Valdydesu_
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

enum planck_layers {
  _1,
  _2,
  _3,
  _4

};


enum planck_keycodes {
  L1 = SAFE_RANGE,
  L2,
  L3

};

#define LOWER MO(_4)
#define IND_1          D4
#define IND_2          C6
#define IND_3          D7

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_1] = LAYOUT(
        KC_ESC, KC_F1, KC_F2,
        LOWER, KC_Z, KC_X),

    [_2] = LAYOUT(
        LALT(KC_TAB), LGUI(KC_TAB), LCTL(KC_S),
        LOWER, LCTL(KC_C), LCTL(KC_V)),

    [_3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS),

    [_4] = LAYOUT(
        L1, L2, L3,
        _______, _______, _______),

};


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _4, X_PAUSE, X_PAUSE);
    writePin(IND_1, layer_state_cmp(state, 1));
    writePin(IND_2, layer_state_cmp(state, 2));
    writePin(IND_3, layer_state_cmp(state, 3));
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L1:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_1);
            }
            return false;
        case L2:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_2);
            }
            return false;
        case L3:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_3);
            }
            return false;
    }
    return true;
}

void matrix_init_user(void) {
    //init the Pro Micro on-board LEDs
    setPinOutput(IND_1);
    setPinOutput(IND_2);
    setPinOutput(IND_3);
    //set to off
    writePinHigh(IND_1);
    writePinHigh(IND_2);
    writePinHigh(IND_3);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_state_is(_1)) {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
        tap_code(KC_DOWN);
        }
    } else if (layer_state_is(_2)) {
        if (clockwise) {
            tap_code(KC_RGHT);
        } else {
            tap_code(KC_LEFT);
        }
    } else if (layer_state_is(_3)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
