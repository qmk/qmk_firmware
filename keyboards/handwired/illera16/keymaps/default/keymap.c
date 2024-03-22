// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE, 
    _CAPA1,
    _CAPA2,
    _CAPA3,
};

layer_state_t layer_state_set_user(layer_state_t state);

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    layer_state_set_user(layer_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    switch (layer) {    
        case _CAPA1:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;

        case _CAPA2:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;

        case _CAPA3:
            rgblight_sethsv_noeeprom(HSV_PINK);
            break;

        default:
            rgblight_sethsv_noeeprom(HSV_BLUE); // MI COLOR
            break;
    }
    
    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │c1 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │ * │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ - │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 0 │
     * └───┴───┴───┴───┘
     */
    
    [0] = LAYOUT_ortho_4x4( /* CAPAS BASE */
        KC_DEL, TG(1),  _______,   KC_SLASH,
        KC_7,   KC_8,   KC_9,      KC_PAST,
        KC_4,   KC_5,   KC_6,      KC_PMNS,
        KC_1,   KC_2,   KC_3,      KC_0
    ),
    [1] = LAYOUT_ortho_4x4( /* CAPA1 */
        KC_1,     TG(2),   TG(1),   KC_1,
        KC_1,     KC_1,   KC_1,   KC_1,
        KC_1,     KC_1,   KC_1,   KC_1,
        KC_1,     KC_1,   KC_1,   KC_1
    ),
    [2] = LAYOUT_ortho_4x4( /* CAPA2 */
        KC_2,      TG(3),   TG(2),   KC_2,
        KC_2,       KC_2,   KC_2,   KC_2,
        KC_2,       KC_2,   KC_2,   KC_2,
        KC_2,       KC_2,   KC_2,   KC_2
    ),
    [3] = LAYOUT_ortho_4x4( /* CAPA3 */
        KC_3,      KC_NO,    TG(3),   KC_3,
        KC_3,       KC_3,     KC_3,   KC_3,
        KC_3,       KC_3,     KC_3,   KC_3,
        KC_3,       KC_3,     KC_3,   KC_3
    ),


};
/*
 * ROTARY ENCODER
 */

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),         ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [1] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),         ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [2] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),         ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [3] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),         ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
};

#endif



