// Phantom 7bit
/*
     * 7bit:
     *
     * ,-----------------------------------------------------------. ,-----------.
     * |Esc|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|V- |V+ | |PrS|ScL|Pau|
     * `-----------------------------------------------------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------.
     * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  (|  )| |Ins|Hom|PgU|
     * |-----------------------------------------------------------| |-----------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs| |Del|End|PgD|
     * |-----------------------------------------------------------| |-----------|
     * |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \| Ret| |MSt|Ply|Med|
     * |-----------------------------------------------------------| |-----------|
     * |Cap|Shif|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Cap| |Prv|Up |Nxt|
     * |-----------------------------------------------------------| |-----------|
     * |Ctrl |Gui|Alt  |Spc  |Bspc |Del|Ret  |Alt  |Gui  |App|Ctrl | |Lef|Dow|Rig|
     * `-----------------------------------------------------------' `-----------'
     */
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty + a few media keys */
    KEYMAP(\
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, VOLD,VOLU, PSCR,SLCK,BRK,  \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, FN1, FN2,  INS, HOME,PGUP, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC,      DEL, END, PGDN, \
        FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT,       MSTP,MPLY,MSEL, \
        CAPS,LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,CAPS,      MPRV,UP,  MNXT, \
        LCTL,LGUI,LALT,SPC,      BSPC,DEL, ENT,           RALT,RGUI,APP, RCTL,      LEFT,DOWN,RGHT),
    /* 1: media keys */
    KEYMAP(\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS,TRNS,SLEP, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MUTE,VOLD,VOLU,TRNS,TRNS, TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MSTP,MPLY,MPRV,MNXT,MSEL,      TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,CALC,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,TRNS,      TRNS,TRNS,TRNS)
};
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_MODS_KEY(MOD_LSFT, KC_9),
    [2] = ACTION_MODS_KEY(MOD_LSFT, KC_0)
};
