#include QMK_KEYBOARD_H

// Layers
#define DVORAK 0
#define QWERTY 1
#define RAISE 2
#define LOWER 3
#define BDO 4
#define RESETL 5

#define KC_RAIS MO(RAISE)
#define KC_LOWR MO(LOWER)
#define KC_TGBD TG(BDO)
#define KC_TGRS TG(RESETL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DVORAK] = LAYOUT_kc(
    NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
    NO, QUOT, COMM, DOT,  P,    Y,                F,    G,    C,    R,    L,    NO, \
    NO, A,    O,    E,    U,    I,                D,    H,    T,    N,    S,    NO, \
    NO, SCLN, Q,    J,    K,    X,                B,    M,    W,    V,    Z,    NO, \
    NO, TGBD, LALT, LCTL, LOWR, LSFT, BSPC, ENT,  SPC,  RAIS, LGUI, LEFT, RGHT, NO
  ),

  [QWERTY] = LAYOUT_kc(
    NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
    NO, Q,    W,    E,    R,    T,                Y,    U,    I,    O,    P,    NO, \
    NO, A,    S,    D,    F,    G,                H,    J,    K,    L,    SCLN, NO, \
    NO, Z,    X,    C,    V,    B,                N,    M,    COMM, DOT,  SLSH, NO, \
    NO, TGBD, LALT, LCTL, LOWR, LSFT, BSPC, ENT,  SPC,  RAIS, LGUI, LEFT, RGHT, NO
  ),

  [RAISE] = LAYOUT_kc(
    NO, MRWD, MPRV, MPLY, MNXT, MFFD,             TRNS, MUTE, VOLD, VOLU, DEL,  NO, \
    NO, TILD, GRV,  LCBR, RCBR, DQUO,             QUOT, EQL,  PLUS, MINS, QUES, NO, \
    NO, ESC,  TAB,  LPRN, RPRN, BSLS,             SLSH, LEFT, DOWN, UP,   RGHT, NO, \
    NO, TRNS, TRNS, LBRC, RBRC, TRNS,             INS,  PIPE, UNDS, TRNS, TRNS, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TGRS, NO
  ),

  [LOWER] = LAYOUT_kc(
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
    NO, EXLM, AT,   HASH, DLR,  PERC,             CIRC, AMPR, ASTR, LPRN, RPRN, NO, \
    NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, DOT,  TRNS, TRNS, TRNS, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO
  ),

  [BDO] = LAYOUT_kc(
    NO, ESC,  1,    2,    3,    4,                5,    0,    SLSH, U,    C,    NO, \
    NO, TAB,  Q,    W,    E,    R,                6,    Y,    I,    O,    P,    NO, \
    NO, LSFT, A,    S,    D,    F,                7,    G,    H,    J,    K,    NO, \
    NO, T,    Z,    X,    C,    V,                8,    B,    N,    M,    L,    NO, \
    NO, LCTL, SPC,  SPC,  SPC,  SPC,  COMM, ENT,  9,    NO,   NO,   NO,   TGBD, NO
  ),

  [RESETL] = LAYOUT(
    KC_NO, RESET, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(RESETL),KC_NO
  )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch (id) {
  case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
    }
    else {
      unregister_code(KC_RSFT);
    }
    break;
  }
  return MACRO_NONE;
};

static uint8_t qw_dv_swap_state = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_LGUI) {
    if (record->event.pressed) {
      qw_dv_swap_state |= 0b00000001;
    } else {
      qw_dv_swap_state &= ~(0b00000001);
    }
  }
  if (keycode == KC_LCTL) {
    if (record->event.pressed) {
      qw_dv_swap_state |= 0b00000010;
    } else {
      qw_dv_swap_state &= ~(0b00000010);
    }
  }

  if (qw_dv_swap_state == 0b00000011) {
    layer_invert(DVORAK);
  }
  return true;
}
