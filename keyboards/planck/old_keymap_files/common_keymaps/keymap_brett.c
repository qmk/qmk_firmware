#include "keymap.h"

#define KC_MO1 MO(1)
#define KC_MO2 MO(2)

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( 
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT,
  TAB, LGUI,  RSFT, LALT, MO2,     SPC,     MO1,  LEFT, DOWN, UP,   RGHT),
[1] = KEYMAP( /* RAISE */
  GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    DEL,
  TRNS, F1,   F2,   F3,   F4,   F5,   F6,   4,    5,    6,   QUOT, TRNS,
  TRNS, F7,   F8,   F9,   F10,  F11,  F12,  1,    2,    3,   TRNS, PGUP,
  MPRV, MNXT, TRNS, MUTE, TRNS,    TRNS,    MO1,  0,  0,  TRNS, PGDN),
[2] = KEYMAP( /* LOWER */
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, MINS,
  TRNS, TRNS, TRNS, PAUSE, TRNS, TRNS, TRNS, TRNS, LBRC, RBRC, BSLS, EQL,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  MPLY, MSTP, VOLU, VOLD, MO2,     TRNS,    TRNS, TRNS, TRNS, TRNS, TRNS),
};
const uint16_t PROGMEM fn_actions[] = {
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

    [29] = ACTION_MODS_KEY(MOD_LSFT | MOD_RSFT, KC_PAUSE),
};
