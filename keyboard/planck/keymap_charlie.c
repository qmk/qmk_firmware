#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Charlie workman */
  ESC,   Q,    D,    R,    W,    B,    J,    F,    U,    P,    SCLN, BSLS,
  LCTL,  A,    S,    H,    T,    G,    Y,    N,    E,    O,    QUOT, BSPC,
  LSFT,  Z,    X,    M,    C,    V,    K,    L,    COMM, DOT,  SLSH, ENT,
  RSFT, LALT, LGUI, RCTL, FN2,    SPC,     FN1, LEFT, DOWN, UP,  RGHT),
[1] = KEYMAP( /* Charlie RAISE */
  TAB,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    BSPC,
  TRNS, FN3, FN4, PAUSE, TRNS, TRNS, TRNS, MINS, EQL,  LBRC, RBRC, BSLS,
  TRNS, F11,  F12,  F13,  F14,  F15,  F16,  F17,  F18,  F19,  F20, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,   FN1,  MNXT, VOLD, VOLU, MPLY),
[2] = KEYMAP( /* Charlie LOWER */
  GRV, FN10, FN11, FN12, FN13, FN14, FN15, FN16, FN17, FN18, FN19, BSPC,
  TRNS, FN3, FN4, PAUSE, TRNS, TRNS, TRNS, FN20, FN21, FN23, FN24, FN28,
  TRNS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  TRNS,
  TRNS, TRNS, TRNS, TRNS, FN2,    TRNS,    TRNS, MNXT, VOLD, VOLU, MPLY),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
};
