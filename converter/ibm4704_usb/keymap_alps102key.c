#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0:
     * ,---------------------------------------------------------------.  ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|BS |BS |F21|  |PSC|SLK|PAU| |F1 |F2 |F3 |F4 |
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|F22|  |Ins|Hom|PgU| |F5 |F6 |F7 |F8 |
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Ret|Ret |F23|  |Del|End|PgD| |F9 |F10|F11|F12|
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shf|Shift |F24|  |   |Up |   | |F13|F14|F15|F16|
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Fn0  |Gui|Alt  |         Space             |Alt* |Gui|Fn0      |  |Lef|Dow|Rig| |F17|F18|F19|F20|
     * `---------------------------------------------------------------'  `-----------' `---------------'
     */
    KEYMAP_ALPS102(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,BSPC,F21,      PSCR,SLCK,PAUS,     F1,  F2,  F3,  F4,  \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     F22,      INS, HOME,PGUP,     F5,  F6,  F7,  F8,  \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT,      F23,      DEL, END, PGDN,     F9,  F10, F11, F12, \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,RSFT,          F24,      NO,  UP,  NO,       F13, F14, F15, F16, \
    FN0, LGUI,LALT,          SPC,                     RALT,RGUI,               FN0,      LEFT,DOWN,RGHT,     F17, F18, F19, F20  \
    ),

    /* Layer 1:
     * ,---------------------------------------------------------------.  ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|BS |BS |F21|  |VoD|VoU|Mut| |F1 |F2 |F3 |F4 |
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|F22|  |Ins|Hom|PgU| |F5 |F6 |F7 |F8 |
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Ret|Ret |F23|  |Del|End|PgD| |F9 |F10|F11|F12|
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shf|Shift |F24|  |   |PgU|   | |F13|F14|F15|F16|
     * |---------------------------------------------------------------|  |-----------| |---------------|
     * |Fn0  |Gui|Alt  |         Space             |Alt* |Gui|Fn0      |  |Hom|PgD|End| |F17|F18|F19|F20|
     * `---------------------------------------------------------------'  `-----------' `---------------'
     */
    KEYMAP_ALPS102(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     VOLD,VOLU,MUTE,     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,     TRNS,PGUP,TRNS,     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,               TRNS,     HOME,PGDN,END,      TRNS,TRNS,TRNS,TRNS  \
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};
