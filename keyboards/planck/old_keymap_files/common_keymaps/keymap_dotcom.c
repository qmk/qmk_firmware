#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( 
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  FN1,  A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, LBRC,
  LCTL, BSLS, QUOT, LALT, FN22,    SPC,     LEFT, UP, DOWN, RGHT,  RBRC),
[1] = KEYMAP( 
  GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    DEL,
  TRNS, FN10, FN11, FN12, FN13, FN14, FN15, FN16, FN17,  TRNS, TRNS, TRNS,
  TRNS, FN18,  FN19,  FN22,  EQL,  MINS,  FN20,  TRNS,  TRNS,  TRNS,  TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,   FN1,  TRNS, VOLD, VOLU, TRNS),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay

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
