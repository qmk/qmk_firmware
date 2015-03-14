#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Charlie querty */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT,
  FN3, LCTL, LGUI, LALT, FN1,    SPC,     FN2, LEFT, DOWN, UP,  RGHT),
[1] = KEYMAP( /* Charlie workman */
  ESC,   Q,    D,    R,    W,    B,    J,    F,    U,    P,    SCLN, BSPC,
  LCTL,  A,    S,    H,    T,    G,    Y,    N,    E,    O,    I,    ENT,
  LSFT,  Z,    X,    M,    C,    V,    K,    L,    COMM, DOT,  SLSH, RSFT,
  FN3, LCTL, LALT, LGUI, FN1,   SPC,  FN2, LEFT, DOWN, UP,  RGHT),
[2] = KEYMAP( /* Charlie RAISE */
  TAB,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    TRNS,
  TRNS, FN4,  FN5,  FN6,  FN7,  FN8,  FN9,  FN10, FN11, FN12, FN13, TRNS,
  TRNS, F11,  F12,  F13,  F14,  F15,  F16,  F17,  F18,  F19,  F20,  TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,   FN1,  MNXT, VOLD, VOLU, MPLY),
[3] = KEYMAP( /* Charlie LOWER */
  GRV, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, BSLS,
  TRNS, FN14, FN15, TRNS, TRNS, TRNS, TRNS, MINS, EQL, LBRC, RBRC, QUOT,
  TRNS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  TRNS,
  TRNS, TRNS, TRNS, TRNS, FN2,    TRNS,    TRNS, MNXT, VOLD, VOLU, MPLY),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay

    [3] = ACTION_MODS_KEY(MOD_LGUI, KC_TAB), // switch windows
    [4] = ACTION_MODS_KEY(MOD_LSFT, KC_1), // !
    [5] = ACTION_MODS_KEY(MOD_LSFT, KC_2), // @
    [6] = ACTION_MODS_KEY(MOD_LSFT, KC_3), // #
    [7] = ACTION_MODS_KEY(MOD_LSFT, KC_4), // $
    [8] = ACTION_MODS_KEY(MOD_LSFT, KC_5), // %
    [9] = ACTION_MODS_KEY(MOD_LSFT, KC_6), // ^
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_7), // &
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_8), // *
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_9), // (
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_0), // )
    [14] = ACTION_DEFAULT_LAYER_SET(1), // change to workman
    [15] = ACTION_DEFAULT_LAYER_SET(0), // change to querty
};
