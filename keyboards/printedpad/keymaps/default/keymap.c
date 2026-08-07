// Copyright 2023 Noah Beidelman (@noahbei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │Tog│ 
     * ├───┼───┬───┐ 
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 
     * └───┴───┴───┘
     */
    [0] = LAYOUT(
        LT(0, KC_NO),
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    ),

    [1] = LAYOUT(
        LT(0, KC_NO),
        KC_A,   KC_B,   KC_C,
        KC_D,   KC_E,   KC_F,
        KC_G,   KC_H,   KC_I
    ),

    [2] = LAYOUT(
        LT(0, KC_NO),
        KC_J,   KC_K,   KC_L,
        KC_M,   KC_N,   KC_O,
        KC_P,   KC_Q,   KC_R
    ),

    [3] = LAYOUT(
        LT(0, KC_NO),
        KC_S,   KC_T,   KC_U,
        KC_V,   KC_W,   KC_X,
        KC_Y,   KC_Z,   KC_ENT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LT(0, KC_NO):
            if (record->event.pressed) {
                // on tap
                if (record->tap.count) {
                    if (get_highest_layer(layer_state) >= 3) {
                        layer_clear(); 
                    } else { 
                        layer_move(get_highest_layer(layer_state) + 1);
                    }
                }
#ifdef OLED_ENABLE
                // on hold
                else {
                    void oled_display_mode_step(void);
                    oled_display_mode_step();
                }
#endif
            }
            return false;
    }
    return true;
}
