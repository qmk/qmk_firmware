/*
 * Let's Split - Dvorak turkish
 * Keymap by @bbaserdem
 * Dvorak layout with multiple features
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */

#include "lets_split.h"
#include "bbaserdem.h"


void matrix_init_keymap (void) {
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
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
