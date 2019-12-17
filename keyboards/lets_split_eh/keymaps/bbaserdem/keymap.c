#include "lets_split_eh.h"
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
