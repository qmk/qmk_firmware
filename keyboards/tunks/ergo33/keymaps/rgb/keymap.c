#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
    _BASE = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        RGB_RMOD, RGB_MOD, RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_HUD,  RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_SAD,  RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_VAD,  RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,                                                 KC_TRNS,
                                                KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
};
