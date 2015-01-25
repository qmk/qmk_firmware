#include "keymap_common.h"
#include "backlight.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default */
    KEYMAP_ANSI150(ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,   PSCR,SLCK,PAUS,  \
                   GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,  INS, HOME,PGUP,  \
                   TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,  DEL, END, PGDN,  \
                   CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                    \
                   LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,            UP,         \
                   LCTL,LGUI,LALT,               SPC,                     RALT,FN0, RCTL,  LEFT,DOWN,RGHT),
    /* Layer 1: Space Fn */
    KEYMAP_ANSI150(TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  \
                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  \
                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  \
                    ESC,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,                   \
                   TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,            TRNS,       \
                   TRNS,TRNS,TRNS,               FN1,                     TRNS,FN0, TRNS,  TRNS,TRNS,TRNS),
    /* Layer 2: Functions */
    KEYMAP_ANSI150(SLEP,     MYCM,WSCH,WHOM,MAIL,VOLD,VOLU,MUTE,MSEL,MPLY,MPRV,MNXT,MSTP,  TRNS,TRNS,TRNS,  \
                   TRNS,TRNS,TRNS,TRNS,END, TRNS,TRNS,TRNS,TRNS,TRNS,HOME,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  \
                   TRNS,BTN1,MS_U,BTN3,PSCR,SLCK,TRNS,TRNS,INS, TRNS,TRNS,TRNS,TRNS,FN3,   TRNS,TRNS,TRNS,  \
                   CAPS,MS_L,MS_D,MS_R,PGDN,TRNS,LEFT,DOWN,UP  ,RGHT,TRNS,TRNS,     FN2,                    \
                   TRNS,     TRNS,DEL, TRNS,TRNS,PGUP,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,            TRNS,       \
                   TRNS,TRNS,TRNS,               TRNS,                    TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(2),
    [1] = ACTION_LAYER_TAP_KEY(2, KC_SPACE),
    [2] = ACTION_LAYER_TOGGLE(1),
    [3] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_SWITCH)
};
