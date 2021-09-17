#include QMK_KEYBOARD_H

enum layer_names { _BASE, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(LT(_FN, KC_N), LALT(KC_UP), LALT(KC_DOWN), LALT(KC_D)),
    [_FN]   = LAYOUT(KC_TRNS, KC_1, KC_2, BL_STEP),
};
