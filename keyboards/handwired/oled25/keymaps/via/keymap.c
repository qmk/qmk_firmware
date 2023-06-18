// Copyright 2022 Antoni Malecki (@asdfire1)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_5x5(
        KC_F1,    KC_NUM, KC_PSLS, KC_PAST,  KC_PMNS,
        KC_F2,    KC_P7,  KC_P8,   KC_P9,    KC_PPLS,
        KC_F3,    KC_P4,  KC_P5,   KC_P6,    KC_TAB,
        KC_F4,    KC_P1,  KC_P2,   KC_P3,    KC_F13,
        MO(1),    KC_P0,  KC_DEL, KC_PDOT,   KC_PENT
    ), 

    [1] = LAYOUT_ortho_5x5(
        KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   QK_RBT
    )
};

static void print_status_narrow(void) {

    /* Print current layer */
    oled_write("LAYER", false);

    oled_set_cursor(7, 0);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write("Base ", false);
            break;
        case 1:
            oled_write("Raise", false);
            break;
        default:
            oled_write("Undef", false);
    }

}
bool oled_task_user(void) {
        print_status_narrow();
    return false;
}

