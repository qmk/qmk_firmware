// by Matthew Pepers - https://github.com/pepers

#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: dvorak */
  [0] = KEYMAP( ESC, SCLN, COMM,  DOT,    P,    Y,    F,    G,    C,    R,    L, BSPC,   \
                GRV,    A,    O,    E,    U,    I,    D,    H,    T,    N,    S, MINS,   \
                TAB, QUOT,    Q,    J,    K,    X,    B,    M,    W,    V,    Z,  ENT,   \
               LCTL, LGUI, LALT, RALT,  FN1, LSFT,  SPC,  FN2, LEFT, DOWN,   UP, RGHT),

  /* 1: lower (FN1) */
  [1] = KEYMAP( F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,   \
              FN17,    7,    5,    3,    1,    9,    0,    2,    4,    6,    8, FN18,   \
              TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  INS,   \
              TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, HOME, PGDN, PGUP,  END),

  /* 2: raise (FN2) */
  [2] = KEYMAP(PAUS, FN19, FN20, FN21, TRNS, TRNS, TRNS, TRNS, FN22, FN23, FN24,  DEL,   \
               FN10, SLSH, FN11, FN12, LBRC,  EQL, FN13, RBRC, FN14, FN15, BSLS, FN16,   \
               TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PSCR,   \
               TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(1),               // lower Fn layer
    [2] = ACTION_LAYER_MOMENTARY(2),               // raise Fn layer

    // lower row1
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_5),        // %
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_SLASH),    // ?
    
    // raise row0
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_2),        // @
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLASH),   // |
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_6),        // ^
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_8),        // *
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_3),        // #
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_4),        // $
    
    // raise row1
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_7),        // &
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRACKET), // {
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_9),        // (
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_1),        // !
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_0),        // )
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRACKET), // }
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_EQUAL),    // +
};
