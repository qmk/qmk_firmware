#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|???|BS |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Ret|Ret |
     * |-----------------------------------------------------------|
     * |Shif|Shf|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|???|Shift |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui|Alt  |         Space             |Alt* |Gui|Fn   |
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    F1,  F2,    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,     INS, HOME,PGUP,     NLCK,PSLS,PAST,PMNS, \
    F3,  F4,    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL, END, PGDN,     P7,  P8,  P9,  PPLS, \
    F5,  F6,    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT, ENT,           PSCR,SLCK,PAUS,     P4,  P5,  P6,  PPLS, \
    F7,  F8,    LSFT,LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,NO,  RSFT,          F11, UP,  F12,      P1,  P2,  P3,  PENT, \
    F9,  F10,   LCTL,LGUI,LALT,          SPC,                               RGUI,FN0,           LEFT,DOWN,RGHT,     P0,  P0,  PDOT,PENT  \
    ),

    /* 1: HHKB
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|???|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pau| Up|   |  Ins|
     * |-----------------------------------------------------------|
     * |Ctrl  |VoD|VoU|VoM|   |   |  *|  /|Hom|PgU|Lef|Rig|Ret|Ret |
     * |-----------------------------------------------------------|
     * |Shif|Shi|   |   |   |   |   |  +|  -|End|PgD|Dow|???|Shift |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui|Alt  |         Space             |Alt* |Gui|Fn   |
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    F1,  F2,    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  DEL,      INS, HOME,PGUP,     NLCK,PSLS,PAST,PMNS, \
    F3,  F4,    CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS, UP, NO,  INS,           DEL, END, PGDN,     P7,  P8,  P9,  PPLS, \
    F5,  F6,    TRNS,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, ENT,           PSCR,SLCK,PAUS,     P4,  P5,  P6,  PPLS, \
    F7,  F8,    TRNS,TRNS,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,NO,  TRNS,          F11, UP,  F12,      P1,  P2,  P3,  PENT, \
    F9,  F10,   TRNS,TRNS,TRNS,          TRNS,                              TRNS,TRNS,          LEFT,DOWN,RGHT,     P0,  P0,  PDOT,PENT  \
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};
