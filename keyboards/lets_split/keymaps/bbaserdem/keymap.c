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

uint32_t layer_state_set_keymap(uint32_t state) {
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main Dvorak layer
    [_DV] = KM(
        DVORAK_L1,      DVORAK_R1,
        DVORAK_L2,      DVORAK_R2,
        DVORAK_L3,      DVORAK_R3,
        DVORAK_L4,      DVORAK_R4 ),
    // Turkish and special character overlay
    [_AL] = KM(
        ALTCHAR_L1,     ALTCHAR_R1,
        ALTCHAR_L2,     ALTCHAR_R2,
        ALTCHAR_L3,     ALTCHAR_R3,
        ALTCHAR_L4,     ALTCHAR_R4 ),
    // Gaming layer
    [_GA] = KM(
        GAME_L1,        GAME_R1,
        GAME_L2,        GAME_R2,
        GAME_L3,        GAME_R3,
        GAME_L4,        GAME_R4 ),
    // Numbers layer
    [_NU] = KM(
        NUMBERS_L1,     NUMBERS_R1,
        NUMBERS_L2,     NUMBERS_R2,
        NUMBERS_L3,     NUMBERS_R3,
        NUMBERS_L4,     NUMBERS_R4 ),
    // Settings layer
    [_SE] = KM(
        SETTINGS_L1,    SETTINGS_R1,
        SETTINGS_L2,    SETTINGS_R2,
        SETTINGS_L3,    SETTINGS_R3,
        SETTINGS_L4,    SETTINGS_R4 ),
    // Mouse emulation layer
    [_MO] = KM(
        MOUSE_L1,       MOUSE_R1,
        MOUSE_L2,       MOUSE_R2,
        MOUSE_L3,       MOUSE_R3,
        MOUSE_L4,       MOUSE_R4 ),
};



