#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_ESC,  KC_INS,  KC_COLN, KC_MPLY, KC_MNXT, KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_CAPS, KC_LALT, KC_LGUI, RAISE,   KC_SPC,  KC_SPC,  LOWER,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

[_LOWER] = LAYOUT_ortho_4x12( \
  KC_1,       KC_2,    KC_3,    KC_4,    KC_5,    KC_6, \
  KC_GRV ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL, \
  KC_ESC , KC_BSLS, KC_QUOT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,    KC_4,    KC_5,    KC_6, _______,  _______, \
  _______, _______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_VOLU,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD,  KC_MNXT \
),

[_RAISE] = LAYOUT_ortho_4x12( \
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, \
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_DEL, \
  KC_ESC , KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, _______, _______,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD,  KC_MNXT \
),

[_ADJUST] =  LAYOUT_ortho_4x12( \
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, \
  KC_F1  ,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
  RESET  , _______,  MU_MOD,   AU_ON,  AU_OFF, _______, _______, _______, _______, _______, _______, _______, \
  _______,  MUV_DE,  MUV_IN,   MU_ON,  MU_OFF,   MI_ON,  MI_OFF, TERM_ON,TERM_OFF, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#define LED_A_PIN F5
#define LED_B_PIN C6
#define LED_C_PIN D4

void matrix_scan_user(void) {
  if (IS_LAYER_ON(_LOWER)) {
    writePinHigh(LED_A_PIN);
  } else {
    writePinLow(LED_A_PIN);
  }

  if (IS_LAYER_ON(_RAISE)) {
    writePinHigh(LED_B_PIN);
  } else {
    writePinLow(LED_B_PIN);
  }

  if (IS_LAYER_ON(_ADJUST)) {
    writePinHigh(LED_C_PIN);
  } else {
    writePinLow(LED_C_PIN);
  }
}

/*
void matrix_slave_scan_user(void) {
    setPinOutput(LED_A_PIN);
    writePinHigh(LED_A_PIN);
}
*/
