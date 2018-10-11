#include "lets_split_eh.h"
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main Dvorak layer
    [_DV] = LAYOUT_letssplit_wrapper(DVORAK),
    // Main Qwerty layer
    [_QW] = LAYOUT_letssplit_wrapper(QWERTY),
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
