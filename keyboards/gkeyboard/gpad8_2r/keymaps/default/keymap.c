#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_MUTE,                RGB_TOG,
        KC_A,   KC_B,   KC_C,   KC_D,
        KC_E,   KC_F,   KC_G,   KC_H
    ),
    [1] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),      ENCODER_CCW_CW(RGB_MOD, RGB_RMOD) },
    [1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
