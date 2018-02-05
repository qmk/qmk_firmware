#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Joe qwerty */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    MINS,
  BSPC, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENTER,
  FN7,  Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, QUOT,
  LCTL, LGUI, LALT, LSFT, FN1,    SPC,      FN0,  LEFT, UP,   DOWN, RGHT),
[1] = KEYMAP( /* Joe colemak */
  ESC,  Q,    W,    F,    P,    G,    J,    L,    U,    Y,    SCLN, MINS,
  BSPC, A,    R,    S,    T,    D,    H,    N,    E,    I,    O,    ENTER,
  FN7,  Z,    X,    C,    V,    B,    K,    M,    COMM, DOT,  SLSH, QUOT,
  LCTL, LGUI, LALT, LSFT, FN1,    SPC,      FN0,  LEFT, UP,   DOWN, RGHT),
[2] = KEYMAP( /* Joe UPPER */
  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,
  DEL,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, MENU, CAPS, INS,  PSCR, TRNS, FN5,  FN6,
  TRNS, TRNS, TRNS, TRNS, FN2,     TRNS,    FN0,  FN26, FN27, FN28, FN29),
[3] = KEYMAP( /* Joe LOWER */
  GRV,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN8,  FN9,  FN30,
  BSPC, 1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    TRNS,
  BSLS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LBRC, RBRC, TRNS, EQL,
  TRNS, TRNS, TRNS, TRNS, FN1,     TRNS,    FN2,  HOME, PGUP, PGDN, END),
[4] = KEYMAP( /* Joe LOWER + UPPER */
  FN3,  FN4,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, SLEP,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,     TRNS,   TRNS, MUTE, VOLD, VOLU, MPLY),
};

enum macro_id {
    M_Q0,
    M_Q1,
    M_Q2
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
    [1] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(4),  // to Fn overlay

    [3] = ACTION_DEFAULT_LAYER_SET(0), 
    [4] = ACTION_DEFAULT_LAYER_SET(1),

    [5] = ACTION_MODS_KEY(MOD_LCTL, KC_PGUP),
    [6] = ACTION_MODS_KEY(MOD_LCTL, KC_PGDN),

    /* tab on tap, shift on hold */
    [7] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_TAB),

    [8] = ACTION_MACRO(M_Q0),
    [9] = ACTION_MACRO(M_Q1),

    [26] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_LEFT),
    [27] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_UP),
    [28] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_DOWN),
    [29] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_RGHT),

    [30] = ACTION_MACRO(M_Q2),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    switch (id) {
        case M_Q0:
            /* :( | ): */
            return event.pressed ?
                MACRO( D(LSFT), T(P), T(9), T(SPC), T(SPC), T(0), T(P), U(LSFT), T(LEFT), T(LEFT), T(LEFT), END ) :
                MACRO_NONE;
        case M_Q1:
            /* (: | :) */
            return event.pressed ?
                MACRO( D(LSFT), T(9), T(P), T(SPC), T(SPC), T(P), T(0), U(LSFT), T(LEFT), T(LEFT), T(LEFT), END ) :
                MACRO_NONE;
        case M_Q2:
            /* :) */
            return event.pressed ?
                MACRO( D(LSFT), T(P), T(0), U(LSFT), END ) :
                MACRO_NONE;
    }
    return MACRO_NONE;
}
