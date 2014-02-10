#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|???|BS |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #|Ret |
     * |-----------------------------------------------------------|
     * |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|???|Shift |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui|Alt  |         Space             |Alt* |Gui|Ctrl |
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,BSPC, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT, \
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,NO,  FN0, \
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL \
    ),

    /* 1: HHKB */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
    CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS, UP, NO,  INS, \
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,NO,  ENT, \
    LSFT,NO,  NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,NO,  TRNS, \
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL \
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};
