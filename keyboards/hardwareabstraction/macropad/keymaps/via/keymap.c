#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT_macro(
        KC_ESC,   KC_ESC,   KC_ESC,   KC_ESC,
        KC_ESC,   KC_ESC,   KC_ESC,   KC_ESC,
        KC_ESC,   KC_ESC,   KC_ESC,   KC_ESC
    )
};
