#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(
  TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, FN3,
  ESC,  DEL,  LALT, LGUI, FN2,  SPC,        FN1,  LEFT, DOWN, UP,   RGHT),
[1] = KEYMAP(
  GRV,  GRV,  FN22, FN19, FN10, TRNS, TRNS, 7,    8,    9,    0,    BSPC,
  TRNS, LBRC, RBRC, FN23, FN24, TRNS, TRNS, 4,    5,    6,    TRNS, BSLS,
  TRNS, MINS, FN20, EQL,  FN21, TRNS, TRNS, 1,    2,    3,    TRNS, ENT,
  TRNS, TRNS, TRNS, TRNS, TRNS, SPC,        FN1,  TRNS, PGDN, PGUP, TRNS),
[2] = KEYMAP(
  FN26, FN10, FN11, FN12, FN13, FN14, FN15, FN17, FN18, FN19, FN10, DEL,
  TRNS, TRNS, MUTE, VOLD, VOLU, TRNS, BSPC, FN14, FN15, FN16, TRNS, FN25,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN11, FN12, FN13, TRNS, ENT,
  TRNS, TRNS, TRNS, TRNS, FN2,  ENT,        TRNS, TRNS, PGDN, PGUP, TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_MOMENTARY(1),  // Switch layer raise
  [2] = ACTION_LAYER_MOMENTARY(2),  // Switch layer lower

  [3] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT), // Right shift serves as Enter on tap

  // Numeric shift modifiers
  [10] = ACTION_MODS_KEY(MOD_LSFT, KC_0),
  [11] = ACTION_MODS_KEY(MOD_LSFT, KC_1),
  [12] = ACTION_MODS_KEY(MOD_LSFT, KC_2),
  [13] = ACTION_MODS_KEY(MOD_LSFT, KC_3),
  [14] = ACTION_MODS_KEY(MOD_LSFT, KC_4),
  [15] = ACTION_MODS_KEY(MOD_LSFT, KC_5),
  [16] = ACTION_MODS_KEY(MOD_LSFT, KC_6),
  [17] = ACTION_MODS_KEY(MOD_LSFT, KC_7),
  [18] = ACTION_MODS_KEY(MOD_LSFT, KC_8),
  [19] = ACTION_MODS_KEY(MOD_LSFT, KC_9),

  // Other shift modifiers
  [20] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS), // _
  [21] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),  // +
  [22] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),  // ~
  [23] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC), // {
  [24] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC), // }
  [25] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS), // |

  // Switch windows in app
  [26] = ACTION_MODS_KEY(MOD_LGUI, KC_GRV),
};
