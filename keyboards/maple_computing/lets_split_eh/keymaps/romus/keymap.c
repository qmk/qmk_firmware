#include QMK_KEYBOARD_H
#include "romus.h"


void matrix_init_keymap (void) {
}

uint32_t layer_state_set_keymap(uint32_t state) {
	
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main Dvorak layer
    [_DV] = LAYOUT_letssplit_wrapper(DVORAK),
    // Turkish and special character overlay
    [_AL] = LAYOUT_letssplit_wrapper(ALTCHAR),
    // Gaming layer
    [_GA] = LAYOUT_letssplit_wrapper(GAME),
    // Numbers layer
    [_NU] = LAYOUT_letssplit_wrapper(NUMBERS),
    // Settings layer
    [_SE] = LAYOUT_letssplit_wrapper(SETTINGS),
    // Mouse emulation layer
    [_MO] = LAYOUT_letssplit_wrapper(MOUSE),
    // Music layer
    [_MU] = LAYOUT_letssplit_wrapper(MUSIC),
};
