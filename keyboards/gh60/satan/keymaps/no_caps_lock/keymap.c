#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
  _BL,
  _FL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* Keymap _BL: (Base Layer) Default Layer
    * ,-----------------------------------------------------------.
    * | ~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backsp |
    * |-----------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
    * |-----------------------------------------------------------|
    * |ESC    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
    * |-----------------------------------------------------------|
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
    * |-----------------------------------------------------------|
    * |Ctrl|Gui |Alt |      Space          |Alt |FL |Gui  |FL(tgl)|
    * `-----------------------------------------------------------'
    */
    [_BL] = LAYOUT_60_ansi(
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT, KC_SLSH,                   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                           KC_SPC,                             KC_RALT, MO(_FL), KC_RGUI, TG(_FL)
    ),

   /* Keymap _FL: Function Layer
    * ,-----------------------------------------------------------.
    * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
    * |-----------------------------------------------------------|
    * |     |Home|PgUp|   |  |  |  |  |  |   |   |BR- |BR+ |      |
    * |-----------------------------------------------------------|
    * |      |End|PgDn|  |  |  |Left|Down|Up|Right|Prv|Nxt|Ply    |
    * |-----------------------------------------------------------|
    * |        |   |   |   |   |   |   |   |Vdn|Vup|Mute|         |
    * |-----------------------------------------------------------|
    * |    |    |    |                        |    |    |    |    |
    * `-----------------------------------------------------------'
    * hjkl for arrows because vim
    */
    [_FL] = LAYOUT_60_ansi(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_TRNS, KC_HOME, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_F14,  KC_F15,  KC_TRNS,
        KC_TRNS, KC_END,  KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, KC_MPRV, KC_MNXT,          KC_MPLY,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_VOLD, KC_VOLU, KC_MUTE,                   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
