#include "backlight.h"

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(\
        FN0, F1,  DEL, BSPC, \
        NLCK,PSLS,PAST,PMNS, \
        P7,  P8,  P9,  PPLS, \
        P4,  P5,  P6,        \
        P1,  P2,  P3,  PENT, \
        P0,  NO,  PDOT),     \
    KEYMAP(\
        TRNS,PGDN,PGUP,MUTE, \
        MSEL,MPRV,MNXT,VOLD, \
        P7,  P8,  P9,  VOLU, \
        FN4, FN5, FN6,       \
        FN1, FN2, FN3, MPLY, \
        FN7, NO,  MSTP)
};

static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_FN1),
    [2] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_FN2),
    [3] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_FN3),
    [4] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_FN4),
    [5] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_NUMPAD),
    [6] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_REAR),
    [7] = ACTION_BACKLIGHT_TOGGLE()
};
