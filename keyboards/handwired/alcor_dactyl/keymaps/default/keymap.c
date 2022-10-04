#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_alcor(
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC,
                                        KC_SPC, KC_SPC,
                                            KC_SPC, KC_SPC,
                                            KC_SPC, KC_SPC,
//-----------------------------------------------------------------------
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
                KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
                                KC_SPC, KC_SPC, KC_SPC, KC_SPC,
                KC_SPC, KC_SPC,
            KC_SPC, KC_SPC,
            KC_SPC, KC_SPC
    )
};
