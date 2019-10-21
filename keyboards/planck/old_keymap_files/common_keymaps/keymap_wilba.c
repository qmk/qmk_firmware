#include "keymap.h"

#define KC_MO2 MO(2)
#define KC_MO3 MO(3)
#define KC_BLTG BL_TOGG
#define KC_BLIN BL_INC
#define KC_BLDE BL_DEC

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Wilba */
  BLTG, BLIN, BLDE, E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  TAB,  A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, ENT,
  LCTL, LGUI, LALT, RSFT, MO2,  SPC,        MO3,  LEFT, DOWN, UP,   RGHT),
[1] = KEYMAP( /* Wilba Alternate */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  TAB,  A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, ENT,
  LCTL, LGUI, LALT, RSFT, MO2,  SPC,        MO3,  LEFT, DOWN, UP,   RGHT),
[2] = KEYMAP( /* Wilba LOWER */
  TRNS, 1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    TRNS,
  TRNS, F11,  F12,  LBRC, RBRC, FN20, EQL,  FN23, FN24, MINS, FN21, TRNS,
  TRNS, BSLS, GRV,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, MO2,  TRNS,       TRNS, MNXT, VOLD, VOLU, MPLY),
[3] = KEYMAP( /* Wilba RAISE */
  TRNS, FN10, FN11, FN12, FN13, FN14, FN15, FN16, FN17, FN18, FN19, TRNS,
  TRNS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  TRNS,  
  TRNS, FN25, FN22, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       MO3,  TRNS, TRNS, TRNS, TRNS),
};
const uint16_t PROGMEM fn_actions[] = {
    [3] = ACTION_DEFAULT_LAYER_SET(0),  
    [4] = ACTION_DEFAULT_LAYER_SET(1),

    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_1), // !
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_2), // @
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_3), // #
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_4), // $
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_5), // %
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_6), // ^
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_7), // &
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_8), // *
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_9), // (
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_0), // )
    
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS), // _
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL), // +
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV), // ~
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC), // {
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC), // }
    [25] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS), // |

    [26] = ACTION_MODS_KEY(MOD_LSFT | MOD_RSFT, KC_PAUSE)
};
