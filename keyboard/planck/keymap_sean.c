#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP( /* Matrix Dvorak */
      QUOT, COMM, DOT,  P,    Y,    SLSH, EQL,  F,    G,    C,    R,   L,
      A,    O,    E,    U,    I,    ESC,  BSPC, D,    H,    T,    N,   S,
      SCLN, Q,    J,    K,    X,    TAB,  ENT,  B,    M,    W,    V,   Z,
      LSFT, LCTL, LALT, LGUI, FN1,  SPC,        FN2,  LEFT, DOWN, UP,  RGHT),

    [1] = KEYMAP( /* Matrix Qwerty */
      Q,    W,    E,    R,    T,    SLSH, EQL,  Y,    U,    I,    O,    P,
      A,    S,    D,    F,    G,    ESC,  BSPC, H,    J,    K,    L,    SCLN,
      Z,    X,    C,    V,    B,    TAB,  ENT,  N,    M,    COMM, DOT,  SLSH,
      LSFT, LCTL, LALT, LGUI, FN1,  SPC,        FN2,  LEFT, DOWN, UP,  RGHT),
      
    [2] = KEYMAP( /* fn1 lower */
      F1,   F2,   F3,   F4,   F5,   TRNS, TRNS, F6,   F7,   F8,   F9,   F10,
      1,    2,    3,    4,    5,    ESC,  DEL,  6,    7,    8,    9,    0,
      FN3,  FN4,  TRNS,   GRV,  MINS, TRNS, TRNS, BSLS, LBRC, RBRC, TRNS, TRNS,
      TRNS, TRNS, TRNS, TRNS, FN1,  TRNS,       TRNS, HOME, PGDN, PGUP, END),

    [3] = KEYMAP( /* fn2 raise */
      F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,
      FN10, FN11, FN12, FN13, FN14, ESC,  DEL,  FN15, FN16, FN17, FN18, FN19,
      FN3,  FN4,  TRNS,   FN22, FN20, TRNS, TRNS, FN28, FN23, FN24, TRNS, TRNS,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       FN2,  MNXT, VOLD, VOLU, MPLY),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay 
    [3] = ACTION_DEFAULT_LAYER_SET(0), 
    [4] = ACTION_DEFAULT_LAYER_SET(1),  

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
    [28] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),
};