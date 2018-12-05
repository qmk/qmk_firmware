#include "lets_split_eh.h"
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer
    [_BA] = LAYOUT_letssplit_wrapper(BASE),
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
