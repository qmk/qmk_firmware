#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|???|BS |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|???|Ret |
     * |-----------------------------------------------------------|
     * |Shif|???|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|???|Shift |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui|Alt  |         Space             |Alt  |Gui|Ctrl |
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NO,  ENT, \
    LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT, \
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL \
    ),
};

const uint16_t PROGMEM fn_actions[] = {
};
