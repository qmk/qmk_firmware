// hid_liber alaricljs
// this was the standard layout when hid_liber was merged into tmk's firmware

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default ANSI
 *
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |FN1   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shft|iso|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 */

  KEYMAP(\
    ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10,  F11,  F12,       PSCR, SLCK,  BRK, \
    GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0, MINS,  EQL, BSPC,  INS, HOME, PGUP, \
    TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P, LBRC, RBRC, BSLS,  DEL,  END, PGDN, \
    FN1,   A,   S,   D,   F,   G,   H,   J,   K,   L, SCLN, QUOT,       ENT,                   \
    LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M, COMM, DOT, SLSH,      RSFT,         UP,       \
    LCTL, LGUI, LALT,             SPC,                RALT, RGUI, APP, RCTL, LEFT, DOWN, RGHT),

/* Layer 1:
 *
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Slp|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|Mut|V- |V+ |Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|MSt|Ply|Prv|Nxt|Media| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |FN1   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shft|iso|  Z|  X|Clc|  V|  B|  N|  M|  ,|  .|  /|Caps      |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 */

 KEYMAP(\
    ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10,  F11,  F12,       PSCR, SLCK, SLEP, \
    GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,MUTE, VOLD, VOLU, BSPC,  INS, HOME, PGUP, \
    TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,MSTP,MPLY, MPRV, MNXT, MSEL,  DEL,  END, PGDN, \
    FN1,   A,   S,   D,   F,   G,   H,   J,   K,   L, SCLN, QUOT,       ENT,                   \
    LSFT, NUBS, Z,   X,CALC,   V,   B,   N,   M, COMM, DOT, SLSH,      CAPS,         UP,       \
    LCTL, LGUI, LALT,             SPC,                RALT, RGUI, APP, RCTL, LEFT, DOWN, RGHT),

};

static const uint16_t PROGMEM fn_actions[] = {
	[1] = ACTION_LAYER_MOMENTARY(1),		// activate layer 1 when FN1 pressed
};
