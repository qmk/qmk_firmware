/*
 * Let's Split - Dvorak turkish
 * Keymap by @bbaserdem
 * Dvorak layout with multiple features
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */
#include "lets_split.h"
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer
    [_BA] = LAYOUT_ortho_4x12_wrapper(BASE),
    // Gaming layer
    [_GA] = LAYOUT_ortho_4x12_wrapper(GAME),
    // Numbers layer
    [_NU] = LAYOUT_ortho_4x12_wrapper(NUMBERS),
    // Settings layer
    [_SE] = LAYOUT_ortho_4x12_wrapper(SETTINGS),
    // Mouse emulation layer
    [_MO] = LAYOUT_ortho_4x12_wrapper(MOUSE),
    // Music layer
    [_MU] = LAYOUT_ortho_4x12_wrapper(MUSIC),
};
