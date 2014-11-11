#include "keymap_common.h"
#include "action_layer.h"
#include "backlight.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default */
    KEYMAP_ANSI150(GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
                   TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
                   ESC, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
                   LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,      \
                   LCTL,LGUI,LALT,          SPC,                          RALT,FN0 ,RCTL),
    /* Layer 1: Arrow keys */
    KEYMAP_ANSI150(TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
                   UP,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      \
                   LEFT,DOWN,RGHT,          TRNS,                         TRNS,TRNS,TRNS),
    /* Layer 2: Space Fn */
    KEYMAP_ANSI150(TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
                   TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      \
                   TRNS,TRNS,TRNS,          FN1,                          TRNS,TRNS,TRNS),
    /* Layer 3: Functions */
    KEYMAP_ANSI150(SLEP,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, FN4,  \
                   TRNS,TRNS,UP,  END, PSCR,SLCK,BRK, TRNS,INS, HOME,TRNS,VOLD,VOLU,FN5,  \
                   CAPS,LEFT,DOWN,RGHT,PGDN,TRNS,LEFT,DOWN,UP  ,RGHT,TRNS,TRNS,     TRNS, \
                   TRNS,     TRNS,DEL, TRNS,TRNS,PGUP,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      \
                   MPRV,MPLY,MNXT,          TRNS,                          FN2,TRNS,FN3),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(3),                // Switch to function layer
    [1] = ACTION_LAYER_TAP_KEY(3, KC_SPACE),        // Switch to function layer (Space Fn)
    [2] = ACTION_LAYER_TOGGLE(1),                   // Toggle "Arrow keys" layer
    [3] = ACTION_LAYER_TOGGLE(2),                   // Toggle "Space fn" layer
    [4] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_SWITCH), // Toggle switch leds
    [5] = ACTION_BACKLIGHT_LEVEL(BACKLIGHT_PCB),    // Toggle pcb leds
};
