#include "keymap_common.h"

// Poker fix with toggle and bit operation
// Fn + Esc = `
// Fn + {left, down, up, right}  = {home, pgdown, pgup, end}
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP_ANSI(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT, \
        LCTL,LGUI,LALT,          SPC,                     FN0, RGUI,APP, RCTL),
    /* 4: Poker Default + Fn'd */
    [4] = KEYMAP_ANSI(
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS, \
        CAPS,FN2, UP,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,CALC,TRNS,HOME,INS, TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,FN4, END,      TRNS, \
        TRNS,DEL, TRNS,WHOM,MUTE,VOLU,VOLD,TRNS,PGUP,PGDN,DEL,           TRNS, \
        TRNS,TRNS,TRNS,          FN1,                     TRNS,TRNS,TRNS,TRNS),
    /* 5: Poker with Arrow */
    KEYMAP_ANSI(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          PGUP, \
        TRNS,TRNS,TRNS,          TRNS,                    FN3, HOME,PGDN,END),
    /* 6: Poker with Esc */
    KEYMAP_ANSI(
        ESC, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS),
    /* 7: Poker with Arrow + Fn'd */
    KEYMAP_ANSI(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          UP,   \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,LEFT,DOWN,RGHT),
};
const uint16_t PROGMEM fn_actions[] = {
    /* Poker Layout */
    [0] = ACTION_LAYER_BIT_XOR(1, 0b0101, ON_BOTH),   // Poker Fn(with fix for Esc)
    [1] = ACTION_LAYER_TOGGLE(5),                     // Poker Arrow toggle
    [2] = ACTION_LAYER_TOGGLE(6),                     // Poker Esc toggle
    [3] = ACTION_LAYER_BIT_XOR(1, 0b1101, ON_BOTH),   // Poker Fn(with fix for Arrow)
    [4] = ACTION_MODS_KEY(MOD_RCTL|MOD_RSFT, KC_ESC), // FN3 Task(RControl,RShift+Esc)
};
