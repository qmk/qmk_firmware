#include "keymap_common.h"

#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* 0: qwerty
     * ,-----------------------------------------------------------.
     * |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  #|Bsp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
     * |-----------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shft|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Esc|
     * |-----------------------------------------------------------'
     * |Ctrl|Gui |Alt |         Space         |App |Alt |Gui |Ctrl |
     * `-----------------------------------------------------------'
     */
    KEYMAP( \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NUHS, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,  \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,ESC, \
        LCTL,LGUI,LALT,          SPC,                     APP, RALT,RGUI,RCTL),
};
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
    [1]  = ACTION_LAYER_MOMENTARY(2),
    [2]  = ACTION_LAYER_MOMENTARY(3),
    [3]  = ACTION_LAYER_MOMENTARY(4),
    [4]  = ACTION_LAYER_MOMENTARY(5),
    [5]  = ACTION_LAYER_MOMENTARY(6),
    [6]  = ACTION_LAYER_MOMENTARY(7),
    [7]  = ACTION_LAYER_TOGGLE(1),
    [8]  = ACTION_LAYER_TOGGLE(2),
    [9]  = ACTION_LAYER_TOGGLE(3),
    [10] = ACTION_LAYER_TAP_TOGGLE(1),
    [11] = ACTION_LAYER_TAP_TOGGLE(2),
    [12] = ACTION_LAYER_TAP_TOGGLE(3),
    [13] = ACTION_LAYER_TAP_KEY(1, KC_BSLASH),
    [14] = ACTION_LAYER_TAP_KEY(2, KC_TAB),
    [15] = ACTION_LAYER_TAP_KEY(3, KC_ENTER),
    [16] = ACTION_LAYER_TAP_KEY(4, KC_SPACE),
    [17] = ACTION_LAYER_TAP_KEY(5, KC_SCOLON),
    [18] = ACTION_LAYER_TAP_KEY(6, KC_QUOTE),
    [19] = ACTION_LAYER_TAP_KEY(7, KC_SLASH),
    [20] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_SPACE),
    [21] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_SPACE),
    [22] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_QUOTE),
    [23] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENTER),
    [24] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [25] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_BSPACE),
    [26] = ACTION_MODS_ONESHOT(MOD_LCTL),
    [27] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ESC),
    [28] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_BSPACE),
    [29] = ACTION_MODS_ONESHOT(MOD_LSFT),
    [30] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_GRAVE),
    [31] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_BSLASH),
};
#else
const uint16_t fn_actions[] PROGMEM = {};
#endif
