/*
 * PLANCK - Dvorak turkish
 * Keymap by @bbaserdem
 * Dvorak layout with multiple features
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main Dvorak layer
    [_DV] = DVORAK,
    // Turkish and special character overlay
    [_AL] = ALTCHAR,
    // Gaming layer
    [_GA] = GAME,
    // Numbers layer
    [_NU] = NUMBERS,
    // Settings layer
    [_SE] = SETTINGS,
    // Mouse emulation layer
    [_MO] = MOUSE,
#ifdef MUSIC_ENABLE
    // Music mode
    [_MU] = MUSIC,
#endif
};
