#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP_50(
    F1,  F2,  F3,   F4,  F5,  F6,   F7,  F8,  F9,  F10,  \
    1,   2,   3,    4,   5,   6,    7,   8,   9,   0,    \
    Q,   W,   E,    R,   T,   Y,    U,   I,   O,   P,    \
    A,   S,   D,    F,   G,   H,    J,   K,   L,   SCLN, \
    Z,   X,   C,    V,   B,   N,    M,   COMM,DOT, SLSH  \
    ),
};

const uint16_t PROGMEM fn_actions[] = {
};


