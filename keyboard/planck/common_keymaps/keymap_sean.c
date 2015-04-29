#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP( /* Matrix Dvorak */
      QUOT, COMM,  DOT,    P,    Y, SLSH,  EQL,    F,    G,    C,    R,    L,
         A,    O,    E,    U,    I,  ESC, BSPC,    D,    H,    T,    N,    S,
      SCLN,    Q,    J,    K,    X,  TAB,  ENT,    B,    M,    W,    V,    Z,
      LSFT, LCTL, LALT, LGUI,  FN1,  SPC,        FN2, LEFT, DOWN,   UP, RGHT),

    [1] = KEYMAP( /* Matrix Qwerty */
         Q,    W,    E,    R,    T, QUOT,  EQL,    Y,    U,    I,    O,    P,
         A,    S,    D,    F,    G,  ESC, BSPC,    H,    J,    K,    L, SCLN,
         Z,    X,    C,    V,    B,  TAB,  ENT,    N,    M, COMM,  DOT, SLSH,
      LSFT, LCTL, LALT, LGUI,  FN1,  SPC,        FN2, LEFT, DOWN,   UP, RGHT),
      
    [2] = KEYMAP( /* fn1 lower */
        F1,   F2,   F3,   F4,   F5, TRNS, TRNS,   F6,   F7,   F8,   F9,  F10,
         1,    2,    3,    4,    5,  F18,  DEL,    6,    7,    8,    9,    0,
       FN3,  FN4, TRNS,  GRV, MINS, TRNS, TRNS, BSLS, LBRC, RBRC, TRNS, TRNS,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,        FN5, HOME, PGDN, PGUP,  END),

    [3] = KEYMAP( /* fn2 raise */
        F1,   F2,   F3,   F4,   F5, TRNS, TRNS,   F6,   F7,   F8,   F9,  F10,
       F11,  F12,  F13,  F14,  F15,  F18,  DEL,  F16,  F17,  F18,  F19,  F20,
       FN3,  FN4, TRNS, TRNS, TRNS, TRNS, TRNS, EJCT,  PWR, LSFT,PAUSE, RSFT,
      LEFT, DOWN,   UP, RGHT,  FN5, TRNS,       TRNS, MNXT, VOLD, VOLU, MUTE),

    [4] = KEYMAP( /* lower + raise */
      LEFT, DOWN,   UP, RGHT, TRNS, TRNS, TRNS, TRNS, LEFT, DOWN,   UP, RGHT,
      HOME, PGDN, PGUP,  END, TRNS,  F18,  DEL, TRNS, HOME, PGDN, PGUP,  END,
      FN3,  FN4,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, EJCT,  PWR, MPLY, RSFT,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, MNXT, VOLD, VOLU, MUTE),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay LOWER
    [2] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay RAISE
    [3] = ACTION_DEFAULT_LAYER_SET(0), 
    [4] = ACTION_DEFAULT_LAYER_SET(1),  
    [5] = ACTION_LAYER_MOMENTARY(4),  // to Fn overlay LOWER + RAISE

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
