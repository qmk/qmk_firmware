/*
 * Let's Split - Dvorak turkish
 * Keymap by @bbaserdem
 * Dvorak layout with multiple features
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */
#define KEYMAP(...) LAYOUT_ortho_4x12(__VA_ARGS__)

#include "lets_split.h"
#include "bbaserdem.h"


void matrix_init_keymap (void) {
}

uint32_t layer_state_set_keymap(uint32_t state) {
    return state;
}

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
#ifdef AUDIO_ENABLE
    [_MU] = MUSIC,
#endif
};
