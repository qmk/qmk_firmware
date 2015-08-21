#include "keymap_common.h"

// JCK: Semi-Standard layout

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    [0] = KEYMAP_JCK(GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,    BSPC, \
                     TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, BSLS, DEL, \
                     ESC,  A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,    ENT,     MPLY, \
                     LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH,    RSFT,    VOLD, VOLU, \
                     LCTL,    LALT,  LGUI,          SPC,                         FN1,  LEFT, DOWN, UP,   RGHT),
    [1] = KEYMAP_JCK(GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,    BSPC, \
                     TAB,  Q,    W,    F,    P,    G,    J,    L,    U,    Y,    SCLN, LBRC, RBRC, BSLS, DEL, \
                     ESC,  A,    R,    S,    T,    D,    H,    N,    E,    I,    O,    QUOT,    ENT,     MPLY, \
                     LSFT, Z,    X,    C,    V,    B,    K,    M,    COMM, DOT,  SLSH,    RSFT,    VOLD, VOLU, \
                     LCTL,    LALT,  LGUI,          SPC,                         FN1,  LEFT, DOWN, UP,   RGHT),
    [2] = KEYMAP_JCK(GRV,  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,    BSPC, \
                     TAB,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    LBRC, RBRC, BSLS, DEL, \
                     ESC,  FN3, FN4, TRNS, TRNS, TRNS, TRNS, MINS, EQL,  LBRC, RBRC,   BSLS,    ENT,     MPLY, \
                     LSFT, FN9,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH,    RSFT,    VOLD, VOLU, \
                     LCTL,    LALT,  LGUI,          SPC,                         TRNS,  MNXT, VOLD, VOLU, MPLY),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
    [3] = ACTION_DEFAULT_LAYER_SET(0), 
    [4] = ACTION_DEFAULT_LAYER_SET(1),  

    [9] = ACTION_MODS_KEY(MOD_LSFT | MOD_RSFT, KC_PAUSE),
 
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
