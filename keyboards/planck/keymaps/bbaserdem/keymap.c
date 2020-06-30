/*
 * PLANCK - Dvorak turkish
 * Keymap by @bbaserdem
 * Dvorak layout with multiple features
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */

#include "planck.h"
#include "bbaserdem.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main Dvorak layer
    [_DV] = LAYOUT_planck_wrapper(DVORAK),
    // Turkish and special character overlay
    [_AL] = LAYOUT_planck_wrapper(ALTCHAR),
    // Gaming layer
    [_GA] = LAYOUT_planck_wrapper(GAME),
    // Numbers layer
    [_NU] = LAYOUT_planck_wrapper(NUMBERS),
    // Settings layer
    [_SE] = LAYOUT_planck_wrapper(SETTINGS),
    // Mouse emulation layer
    [_MO] = LAYOUT_planck_wrapper(MOUSE),
    // Music mode
    [_MU] = LAYOUT_planck_wrapper(MUSIC),
};
