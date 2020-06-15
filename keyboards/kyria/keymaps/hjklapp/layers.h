#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

// forward declaration of keymaps defined in keymap.c
extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];
