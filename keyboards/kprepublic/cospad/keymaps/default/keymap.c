#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BL,
    _FL
};

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
    [_BL] = LAYOUT_numpad_6x4(
        KC_ESC,  KC_TAB,  MO(_FL), KC_BSPC,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
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
    [_FL] = LAYOUT_numpad_6x4(
        UG_TOGG, _______, _______, _______,
        UG_NEXT, RGB_M_P, BL_TOGG, _______,
        UG_HUED, UG_HUEU, BL_ON,
        UG_SATD, UG_SATU, BL_OFF,  _______,
        UG_VALD, UG_VALU, BL_STEP,
        _______,          QK_BOOT, _______
    )
};
