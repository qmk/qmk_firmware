#include QMK_KEYBOARD_H

enum whitefox_layers {
  _QWERTY,
  _WORKMAN,
  _COLEMAK,
  _DVORAK,
  _FUNC,
};

enum whitefox_keycodes {
  QWERTY = SAFE_RANGE,
  WORKMAN,
  COLEMAK,
  DVORAK,
  FUNC,
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY (Default Layer)
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Prt|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|Del|
     * |---------------------------------------------------------------|
     * |Fn/CL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctrl|Alt |Gui |         Space    |Gui |Alt |Ctrl|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT( \
      KC_ESC,           KC_1,   KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR, \
      KC_TAB,           KC_Q,   KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,        KC_DEL, \
      LT(_FUNC,KC_CAPS),KC_A,   KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,         KC_PGUP,\
      KC_LSFT,          KC_NUBS,KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        KC_UP,  KC_PGDN,\
      KC_LCTL,          KC_LALT,KC_LGUI,                 KC_SPC,             KC_RGUI,KC_RALT,KC_RCTL,        KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Workman
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Prt|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  D|  R|  W|  B|  J|  F|  U|  P|  ;|  [|  ]|Backs|Del|
     * |---------------------------------------------------------------|
     * |Fn/CL |  A|  S|  H|  T|  G|  Y|  N|  E|  O|  I|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shif|   |  Z|  X|  M|  C|  V|  K|  L|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctrl|Alt |Gui |         Space    |Gui |Alt |Ctrl|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [_WORKMAN] = LAYOUT( \
      KC_ESC,           KC_1,   KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR, \
      KC_TAB,           KC_Q,   KC_D,    KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P,   KC_SCLN,KC_LBRC,KC_RBRC,KC_BSPC,        KC_DEL, \
      LT(_FUNC,KC_CAPS),KC_A,   KC_S,    KC_H, KC_T, KC_G, KC_Y, KC_N, KC_E, KC_O,   KC_I,   KC_QUOT,KC_NUHS,KC_ENT,         KC_PGUP,\
      KC_LSFT,          KC_NUBS,KC_Z,    KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        KC_UP,  KC_PGDN,\
      KC_LCTL,          KC_LALT,KC_LGUI,                 KC_SPC,             KC_RGUI,KC_RALT,KC_RCTL,        KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Dvorak
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|  `|  \|Prt|
     * |---------------------------------------------------------------|
     * |Tab  |  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|Backs|Del|
     * |---------------------------------------------------------------|
     * |Fn/CL |  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shif|   |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctrl|Alt |Gui |         Space    |Gui |Alt |Ctrl|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [_DVORAK] = LAYOUT( \
      KC_ESC,           KC_1,   KC_2,    KC_3,   KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9, KC_0, KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR, \
      KC_TAB,           KC_QUOT,KC_COMM, KC_DOT, KC_P,  KC_Y,  KC_F,  KC_G,  KC_C,  KC_R, KC_L, KC_SLSH,KC_EQL, KC_BSPC,        KC_DEL, \
      LT(_FUNC,KC_CAPS),KC_A,   KC_O,    KC_E,   KC_U,  KC_I,  KC_D,  KC_H,  KC_T,  KC_N, KC_S, KC_MINS,KC_NUHS,KC_ENT,         KC_PGUP,\
      KC_LSFT,          KC_NUBS,KC_SCLN, KC_Q,   KC_J,  KC_K,  KC_X,  KC_B,  KC_M,  KC_W, KC_V, KC_Z,KC_RSFT,        KC_UP,  KC_PGDN,\
      KC_LCTL,          KC_LALT,KC_LGUI,                 KC_SPC,             KC_RGUI,KC_RALT,KC_RCTL,        KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Colemak
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  +|  `|  \|Prt|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|Backs|Del|
     * |---------------------------------------------------------------|
     * |Fn/CL |  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctrl|Alt |Gui |         Space    |Gui |Alt |Ctrl|  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT( \
      KC_ESC,           KC_1,   KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR, \
      KC_TAB,           KC_Q,   KC_W,    KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y,   KC_SCLN,KC_LBRC,KC_RBRC,KC_BSPC,        KC_DEL, \
      LT(_FUNC,KC_CAPS),KC_A,   KC_R,    KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I,   KC_O,   KC_QUOT,KC_NUHS,KC_ENT,         KC_PGUP,\
      KC_LSFT,          KC_NUBS,KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        KC_UP,  KC_PGDN,\
      KC_LCTL,          KC_LALT,KC_LGUI,                 KC_SPC,             KC_RGUI,KC_RALT,KC_RCTL,        KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Function
     * ,---------------------------------------------------------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |   |
     * |---------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |
     * |---------------------------------------------------------------|
     * |    |   |   |   |   |   |   |   |   |   |   |   |      |   |   |
     * |---------------------------------------------------------------|
     * |    |    |    |                  |    |    |    |  |   |   |   |
     * `---------------------------------------------------------------'
     */
    [_FUNC] = LAYOUT( \
      QK_BOOT,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,_______,\
      _______,KC_WH_D,KC_BTN2,KC_MS_U,KC_BTN1,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
      _______,KC_WH_U,KC_MS_L,KC_MS_D,KC_MS_R,AG_NORM,AG_SWAP,QWERTY, WORKMAN,DVORAK, COLEMAK,_______,_______,_______,        _______,\
      _______,_______,KC_WH_L,KC_BTN3,KC_WH_R,_______,_______,_______,_______,_______,_______,_______,_______,        KC_VOLU,_______,\
      _______,_______,_______,                   KC_MPLY,                     _______,_______,_______,        KC_MPRV,KC_VOLD,KC_MNXT \
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
  }
  return true;
}
