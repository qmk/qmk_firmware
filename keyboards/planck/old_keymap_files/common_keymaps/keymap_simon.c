#include "keymap.h"

#define KC_MO1 MO(1)
#define KC_MO2 MO(2)

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Jack */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  TAB,  A,    S,    D,    F,    G,    H,    J,    K,    L,    DOT,  ENT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SCLN, DEL,
  LCTL, ENT,  LALT, CAPS, MO2,    SPC,      MO1,  LEFT, DOWN, UP,   RGHT),
[1] = KEYMAP( /* Jack RAISE */
  TRNS, F1,   F2,   F3,   F4,   NO,   FN11, FN9,  FN12, NO,   FN14, TRNS,
  TRNS, F5,   F6,   F7,   F8,   FN16, SLSH, MINS, EQL,  LBRC, FN8,  TRNS,
  TRNS, F9,   F10,  F11,  F12,  F15,  F16,  FN22, SCLN, MINS, QUOT, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,    TRNS, TRNS, TRNS, TRNS, TRNS),
[2] = KEYMAP( /* Jack LOWER */
  FN22, 1,    2,    3,   FN13, FN14, FN15, FN16, FN17, FN18, FN19, BSPC,
  TRNS, 4,    5,    6,   TRNS, TRNS, TRNS, FN20, FN21, FN23, FN24, FN28,
  TRNS, 7,    8,    9,   0,    FN28, FN15,   F7,   F8,   F9,   F10,  TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,    TRNS, TRNS, TRNS, TRNS, TRNS),
};
const uint16_t PROGMEM fn_actions[] = {
    [8]  = ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),
    [9]  = ACTION_MODS_KEY(MOD_LSFT, KC_QUOT),
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
