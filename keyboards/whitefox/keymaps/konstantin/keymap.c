#include QMK_KEYBOARD_H

#define FN      MO(L_FN)
#define FN_CAPS LT(L_FN, KC_CAPS)
#define FN_RCTL TD(TD_FN_RCTL) // Unused
#define RLALT   TD(TD_RLALT)   // Unused

#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)

#define UC_COMM UC(0x002C)
#define UC_LPRN UC(0x0028)
#define UC_RPRN UC(0x0029)
#define UC_EQLS UC(0x003D)
#define UC_MULS UC(0x00D7)
#define UC_DIVS UC(0x00F7)
#define UC_MINS UC(0x2212)

void matrix_init_user(void)
{
  set_unicode_input_mode(UC_WIN);
}

enum layers {
  L_BASE,
  L_FN,
  L_NUMPAD,
};

enum custom_keycodes {
  CLEAR = SAFE_RANGE,
  NUMPAD,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
    }
    return false;

  case NUMPAD:
    if (record->event.pressed) {
      layer_invert(L_NUMPAD);
      bool num_lock = host_keyboard_leds() & 1<<USB_LED_NUM_LOCK;
      if (num_lock != (bool)IS_LAYER_ON(L_NUMPAD)) {
        register_code(KC_NLCK); // Toggle Num Lock to match layer state.
        unregister_code(KC_NLCK);
      }
    }
    return false;

  default:
    return true;
  }
}

enum tap_dance {
  TD_FN_RCTL,
  TD_RLALT,
};

void td_fn_ctrl_finished(qk_tap_dance_state_t *state, void *user_data)
{
  // Single tap → Fn, double tap → RCtrl, triple tap → Fn+RCtrl etc.
  if (state->count & 1) { layer_on(L_FN); }
  if (state->count & 2) { register_code(KC_RCTL); }
}

void td_fn_ctrl_reset(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count & 1) { layer_off(L_FN); }
  if (state->count & 2) { unregister_code(KC_RCTL); }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_FN_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_fn_ctrl_finished, td_fn_ctrl_reset),
  [TD_RLALT]   = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LALT),
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   * ,---------------------------------------------------------------.
   * |Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | \ | ` |PSc|
   * |---------------------------------------------------------------|
   * | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] |Bspc |Del|
   * |---------------------------------------------------------------|
   * |FnCaps| A | S | D | F | G | H | J | K | L | ; | ' | Enter  |PgU|
   * |---------------------------------------------------------------|
   * | LShift | Z | X | C | V | B | N | M | , | . | / |  Fn  | ↑ |PgD|
   * |---------------------------------------------------------------|
   * |LCtl|LGui|LAlt|         Space          |RAlt|RCtl| | ← | ↓ | → |
   * `---------------------------------------------------------------'
   */
  [L_BASE] = LAYOUT_truefox( \
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR, \
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,        KC_DEL,  \
    FN_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,         KC_PGUP, \
    KC_LSFT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,FN,             KC_UP,  KC_PGDN, \
    KC_LCTL,KC_LGUI,KC_LALT,                        KC_SPC,                 KC_RALT,KC_RCTL,                KC_LEFT,KC_DOWN,KC_RGHT  \
  ),

  /* Function layer
   * ,---------------------------------------------------------------.
   * |   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Num|Scr|Pau|
   * |---------------------------------------------------------------|
   * | M4  |M2 |M↑ |M1 |M3 |M5 |   |   |   |Stp|Ply|Prv|Nxt|Clear|Ins|
   * |---------------------------------------------------------------|
   * |      |M← |M↓ |M→ |MW↑|   |   |   |   |   |   |   |        |Top|
   * |---------------------------------------------------------------|
   * |        |MA0|MA2|MW←|MW→|   |   |   |VoD|VoU|Mut|      |PgU|Btm|
   * |---------------------------------------------------------------|
   * |    |    |    |          MW↓           |    |Menu| |Hom|PgD|End|
   * `---------------------------------------------------------------'
   */
  [L_FN] = LAYOUT_truefox( \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, NUMPAD, KC_SLCK,KC_PAUS, \
    KC_BTN4,KC_BTN2,KC_MS_U,KC_BTN1,KC_BTN3,KC_BTN5,_______,_______,_______,KC_MSTP,KC_MPLY,KC_MPRV,KC_MNXT,CLEAR,          KC_INS,  \
    _______,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_U,_______,_______,_______,_______,_______,_______,_______,        _______,        TOP,     \
    _______,        KC_ACL0,KC_ACL2,KC_WH_L,KC_WH_R,_______,_______,_______,KC_VOLD,KC_VOLU,KC_MUTE,_______,        KC_PGUP,BOTTOM,  \
    _______,_______,_______,                        KC_WH_D,                _______,KC_APP,                 KC_HOME,KC_PGDN,KC_END   \
  ),

  /* Numpad layer
   * ,---------------------------------------------------------------.
   * |Num|   |   |   |   |   |   |P7 |P8 |P9 |P- | − | = |Num|   |   |
   * |---------------------------------------------------------------|
   * |     |   |   |   |   |   |   |P4 |P5 |P6 |P+ | ( | ) |     |   |
   * |---------------------------------------------------------------|
   * |      |   |   |   |   |   |   |P1 |P2 |P3 |P* | × | PEnter |   |
   * |---------------------------------------------------------------|
   * |        |   |   |   |   |   |P0 |P0 | , |P. |P/ |  ÷   |   |   |
   * |---------------------------------------------------------------|
   * |    |    |    |                        |    |    | |   |   |   |
   * `---------------------------------------------------------------'
   */
  [L_NUMPAD] = LAYOUT_truefox( \
    NUMPAD, _______,_______,_______,_______,_______,_______,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,UC_MINS,UC_EQLS,NUMPAD, _______,_______, \
    _______,_______,_______,_______,_______,_______,_______,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,UC_LPRN,UC_RPRN,_______,        _______, \
    _______,_______,_______,_______,_______,_______,_______,KC_P1,  KC_P2,  KC_P3,  KC_PAST,UC_MULS,        KC_PENT,        _______, \
    _______,        _______,_______,_______,_______,_______,KC_P0,  KC_P0,  UC_COMM,KC_PDOT,KC_PSLS,UC_DIVS,        _______,_______, \
    _______,_______,_______,                        _______,                _______,_______,                _______,_______,_______  \
  ),
};
