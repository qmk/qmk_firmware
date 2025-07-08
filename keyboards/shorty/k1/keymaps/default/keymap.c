// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,
        KC_B,
        KC_C,
        LT(0,KC_NO)
    ),
    [1] = LAYOUT(
        KC_1,
        KC_2,
        KC_3,
        LT(0,KC_NO)
    ),
    [2] = LAYOUT(
        KC_Q,
        KC_W,
        KC_E,
        LT(0,KC_NO)
    ),
    [3] = LAYOUT(
        KC_ENT,
        KC_ESC,
        KC_TAB,
        LT(0,KC_NO)
    )
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [2] =   { ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
    [3] =   { ENCODER_CCW_CW(KC_MUTE, KC_MPLY) }
};
#endif
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
            }
            return false;
    }
    return true;
}
