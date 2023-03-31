// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//make custom cycle keycode and function in process_user_record
int current_layer = 0;
int current_display_mode = 0;

enum layers {
    NUM_P,
    ARROW,
    NUM2,
    NUM3
};

enum custom_keycodes {
    KC_00 = SAFE_RANGE,
    LAYER_INC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │TOG│
     * ├───┼───┬───┬───┐
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x4(
        LAYER_INC,
        KC_7,   KC_8,   KC_9,   KC_PPLS,
        KC_4,   KC_5,   KC_6,   KC_PERC,
        KC_1,   KC_2,   KC_3,   KC_EQL,
        KC_0,   KC_00,  KC_DOT, KC_PENT
    ),

    /*
     * ┌───┐
     * │TOG│
     * ├───┼───┬───┬───┐
     * │Hom│ ↑ │PgU│ 3 │
     * ├───┼───┼───┼───┤
     * │ ← │   │ → │ 2 │
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│ 1 │
     * ├───┼───┼───┤───┤
     * │Ins│Spc│Del│Ent│
     * └───┴───┴───┘───┘
     */
    [1] = LAYOUT_ortho_5x4(
        LAYER_INC,
        KC_HOME, KC_UP,   KC_PGUP, KC_3,
        KC_LEFT, XXXXXXX, KC_RGHT, KC_2,
        KC_END,  KC_DOWN, KC_PGDN, KC_1,
        KC_INS,  KC_SPC,  KC_DEL,  KC_PENT
    ),

    /*
     * ┌───┐
     * │TOG│
     * ├───┼───┬───┬───┐
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [2] = LAYOUT_ortho_5x4(
        LAYER_INC,
        KC_7,   KC_8,   KC_9,   KC_PPLS,
        KC_4,   KC_5,   KC_6,   KC_PERC,
        KC_1,   KC_2,   KC_3,   KC_EQL,
        KC_0,   KC_00,  KC_DOT, KC_PENT
    ),

    /*
     * ┌───┐
     * │TOG│
     * ├───┼───┬───┬───┐
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [3] = LAYOUT_ortho_5x4(
        LAYER_INC,
        KC_7,   KC_8,   KC_9,   KC_PPLS,
        KC_4,   KC_5,   KC_6,   KC_PERC,
        KC_1,   KC_2,   KC_3,   KC_EQL,
        KC_0,   KC_00,  KC_DOT, KC_PENT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KC_00:
                tap_code(KC_0);
                tap_code(KC_0);
                return false;
            case LAYER_INC:
                layer_move(++current_layer % 4);
                return false;
        }
    }
    return true;
}

// when the layer is changed, flash the layer number on the screen
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            // flash layer 1 on the screen. write function for this
            break;
        case 1:
            // if display != 2 flash layer on screen,
            // else cycle picture (maybe function?)
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        default: // for any other layers, or the default layer
            
            break;
    }
  return state;
}