#include "keymap.h"

/*
 * BUILD:
 * Simply run the command below in the keyboards/planck directory
 * to build against this keymap
 *
 *    make KEYMAP=reed COMMON_KEYMAP=true
 *
 *
 * DETAILS:
 *
 * This layout works off of Jack's layout, making some changes that I
 * feel significantly improve the function of the keyboard. Major changes
 * include adding a "gaming mode" that will allow users to still access
 * the number keys 1 through 4 easily for games that require it. Also
 * included is the ability to use the tap/hold function for easy use of
 * right shift and thumb shift with their tapped companions.
 *
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP_GRID( /* Reed */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  TAB,  A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, FN5,
  LCTL, CAPS, LALT, LGUI, FN2, FN7,  SPC,  FN1,   LEFT, DOWN, UP,  RGHT),

[1] = KEYMAP_GRID( /* Reed EXTREME GAMING */
  ESC,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  TAB,  A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, FN5,
  LCTL, 1,    2,    3,    4,   SPC,  FN2,  FN1,   LEFT, DOWN, UP,  RGHT),

[2] = KEYMAP_GRID( /* Reed RAISE */
  GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    BSPC,
  TRNS, FN3, FN4, PAUSE, TRNS, TRNS, TRNS, MINS, EQL,  LBRC, RBRC,  BSLS,
  TRNS, F1,   F2,    F3,   F4,   F5,   F6,   F7,  F8,    F9,  F10,  TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN1, MNXT, VOLD, VOLU, MPLY),

[3] = KEYMAP_GRID( /* Reed LOWER */
  TRNS,  FN10, FN11, FN12, FN13, FN14, FN15, FN16, FN17, FN18, FN19, DEL,
  TRNS,  TRNS, INS, HOME, PGUP, TRNS, TRNS, FN20, FN21, FN23, FN24, FN28,
  TRNS,  TRNS, DEL,  END, PGDN,  F11,  F12,  F13,  TRNS, VOLD, VOLU, TRNS,
  TRNS,  TRNS, TRNS, TRNS, FN2,  TRNS, TRNS, TRNS, MPRV, MUTE, MPLY, MNXT),
};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay - RAISE
    [2] = ACTION_LAYER_MOMENTARY(3),  // to Fn overlay - LOWER

    [3] = ACTION_DEFAULT_LAYER_SET(0),
    [4] = ACTION_DEFAULT_LAYER_SET(1),
	// Actions for the tap/hold modifiers listed above
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
    [7] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_BSPC),
	
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
