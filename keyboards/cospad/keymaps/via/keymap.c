#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: (Base Layer) Default Layer
     * ,-------------------.
     * |Esc |TAB | FN | BS |
     * |----|----|----|----|
     * | NL | /  | *  | -  |
     * |----|----|----|----|
     * | 7  | 8  | 9  |    |
     * |----|----|----| +  |
     * | 4  | 5  | 6  |    |
     * |----|----|----|----|
     * | 1  | 2  | 3  |    |
     * |----|----|----| En |
     * |   0     | .  |    |
     * `-------------------'
     */
    [0] = LAYOUT_numpad_6x4(
        KC_ESC,  KC_TAB,  MO(1),   KC_BSPC,
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,            KC_PDOT, KC_PENT
    ),

    /* Keymap _FL: Function Layer
     * ,-------------------.
     * |RGBT|    |    |    |
     * |----|----|----|----|
     * |RGBM|RGBP|BTOG|    |
     * |----|----|----|----|
     * |HUD |HUI |BON |    |
     * |----|----|----|    |
     * |SAD |SAI |BOFF|    |
     * |----|----|----|----|
     * |VAD |VAS |BSTP|    |
     * |----|----|----|    |
     * |         |RST |    |
     * `-------------------'
    */
    [1] = LAYOUT_numpad_6x4(
        RGB_TOG, _______, _______, _______,
        RGB_MOD, RGB_M_P, BL_TOGG, _______,
        RGB_HUD, RGB_HUI, BL_ON,
        RGB_SAD, RGB_SAI, BL_OFF,  _______,
        RGB_VAD, RGB_VAI, BL_STEP,
        _______,          RESET,   _______
    ),

    [2] = LAYOUT_numpad_6x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS
    ),
    
    [3] = LAYOUT_numpad_6x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS
    )
};
