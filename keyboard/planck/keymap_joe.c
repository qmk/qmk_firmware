#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Joe colemak */
  ESC,  Q,    W,    F,    P,    G,    J,    L,    U,    Y,    SCLN, MINS,
  BSPC, A,    R,    S,    T,    D,    H,    N,    E,    I,    O,    ENT,
  TAB,  Z,    X,    C,    V,    B,    K,    M,    COMM, DOT,  SLSH, QUOT,
  LCTL, LGUI, LALT, LSFT, FN1,    SPC,      FN0,  LEFT, DOWN, UP,  RGHT),
[1] = KEYMAP( /* Joe qwerty */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    MINS,
  BSPC, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENT,
  TAB,  Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, QUOT,
  LCTL, LGUI, LALT, LSFT, FN1,    SPC,      FN0,  LEFT, DOWN, UP,  RGHT),
[2] = KEYMAP( /* Joe RAISE */
  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,
  DEL,  FN10, FN11, FN12, FN13, FN14, FN15, FN16, FN17, FN18, FN19, TRNS,
  BSLS, FN5,  FN6,  TRNS, TRNS, MENU, CAPS, INS,  PSCR, LBRC, RBRC, FN21,
  TRNS, TRNS, TRNS, TRNS, FN2,     TRNS,    FN0,  FN26, FN27, FN28, FN29),
[3] = KEYMAP( /* Joe LOWER */
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN7, FN8, FN9, FN30, FN31,
  DEL,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    TRNS,
  FN25, FN3,  FN4,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN23, FN24, EQL,
  TRNS, TRNS, TRNS, TRNS, FN1,    TRNS,     FN2,  HOME, PGDN, PGUP, END),
[4] = KEYMAP( /* Joe LOWER + RAISE */
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,     TRNS,   TRNS, MNXT, VOLD, VOLU, MPLY),
};

enum macro_id {
    M_Q0,
    M_Q1,
    M_Q2,
    M_Q3,
    M_Q4
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
    [1] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(4),  // to Fn overlay

    [3] = ACTION_DEFAULT_LAYER_SET(0), 
    [4] = ACTION_DEFAULT_LAYER_SET(1),

    [5] = ACTION_MODS_KEY(MOD_LCTL, KC_PGDN),
    [6] = ACTION_MODS_KEY(MOD_LCTL, KC_PGUP),

    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_1),
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_2),
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_3),
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_4),
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_5),
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_6),
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_7),
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_8),
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_9),
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_0),
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC),
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),
    [25] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),

    [7] = ACTION_MACRO(M_Q0),
    [8] = ACTION_MACRO(M_Q1),
    [9] = ACTION_MACRO(M_Q2),
    [30] = ACTION_MACRO(M_Q3),
    [31] = ACTION_MACRO(M_Q4),

    [26] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_LEFT),
    [27] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_DOWN),
    [28] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_UP),
    [29] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_RGHT),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{ 
    keyevent_t event = record->event;
    switch (id) {
        case M_Q0:
            return event.pressed ?
                MACRO( D(LSFT), T(SCLN), U(LSFT), T(SLSH), END ) :
                MACRO_NONE;
        case M_Q1:
            return event.pressed ?
                MACRO( D(LSFT), T(SCLN), T(9), U(LSFT), END ) :
                MACRO_NONE;
        case M_Q2:
            return event.pressed ?
                MACRO( D(LSFT), T(0), T(SCLN), U(LSFT), END ) :
                MACRO_NONE;
        case M_Q3:
            return event.pressed ?
                MACRO( D(LSFT), T(9), T(SCLN), U(LSFT), END ) :
                MACRO_NONE;
        case M_Q4:
            return event.pressed ?
                MACRO( D(LSFT), T(SCLN), T(0), U(LSFT), END ) :
                MACRO_NONE;

    }
    return MACRO_NONE;
}