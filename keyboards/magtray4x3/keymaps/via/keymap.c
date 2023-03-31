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
     * │Tog│ 
     * ├───┼───┬───┐ 
     * │ 1 │ 2 │ 3 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 7 │ 8 │ 9 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x3(
        LAYER_INC,
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_5,   KC_6,
        KC_7,   KC_8,   KC_9
    ),

    [1] = LAYOUT_ortho_4x3(
        LAYER_INC,
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_5,   KC_6,
        KC_7,   KC_8,   KC_9
    ),

    [2] = LAYOUT_ortho_4x3(
        LAYER_INC,
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_5,   KC_6,
        KC_7,   KC_8,   KC_9
    ),

    [3] = LAYOUT_ortho_4x3(
        LAYER_INC,
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_5,   KC_6,
        KC_7,   KC_8,   KC_9
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
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