#include "ps2avrGB.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP( \
        ESC, NO,  NO,  NO,  NO,  NO,  NO,  MPRV,MPLY,MNXT,MUTE,VOLD,VOLU,PSCR,HOME,END, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     DEL, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     FN1, \
        FN2, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,           PGUP,\
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,          UP,  PGDN,\
        FN0, LALT,LGUI,          SPC,                     RGUI,RALT,RCTL,LEFT,DOWN,RGHT \
    ),
    KEYMAP( \
        NO,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  NO,  NO,  \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  MPRV,MPLY,MNXT,MUTE,VOLD,VOLU,DEL,      NO,  \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  PGUP,NO,  NO,  NO,  NO,  NO,  NO,       TRNS,\
        FN2, NO,  NO,  PGDN,NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  NO,            NO,  \
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  TRNS,          NO,  NO,  \
        TRNS,TRNS,TRNS,          NO,                      TRNS,TRNS,TRNS,NO,  NO,  NO   \
    ),
    KEYMAP( \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
        NO,  NO,  NO,  NO,  END, NO,  NO,  NO,  NO,  NO,  HOME,NO,  NO,  NO,       NO,  \
        NO,  BTN1,MS_U,BTN2,NO,  NO,  NO,  PGUP,FN1, NO,  NO,  NO,  NO,  NO,       TRNS,\
        FN2, MS_L,MS_D,MS_R,NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  NO,            NO,  \
        TRNS,NO,  DEL, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  TRNS,          NO,  NO,  \
        TRNS,TRNS,TRNS,          NO,                      TRNS,TRNS,TRNS,NO,  NO,  NO   \
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_TOGGLE(2),
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
};
