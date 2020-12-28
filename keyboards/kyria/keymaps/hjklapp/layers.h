#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _ALT,
    _QWERTY,
    _SYMBOLS,
    _NAVIGATION,
    _VISUALSTUDIO,
    _FUNCTIONKEYS,
    _MOUSE
};

// forward declaration of keymaps defined in keymap.c
extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];
