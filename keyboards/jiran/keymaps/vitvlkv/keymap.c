#include QMK_KEYBOARD_H

/*
qmk compile -kb jiran -km vitvlkv
qmk flash -kb jiran -km vitvlkv
*/

// Defines names for use in layer keycodes and the keymap
enum jiran_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUMPAD
};

#define LOWER MO(_LOWER)
#define L_RAISE LT(_RAISE, KC_GRV)
#define R_RAISE LT(_RAISE, KC_EQL)

#define KC_BSCT  RCTL_T(KC_BSLS)
#define KC_QTSH  RSFT_T(KC_QUOT)
#define KC_SLSF  RSFT_T(KC_LSCR)
#define KC_NLCT  RCTL_T(KC_LNUM)
#define KC_ETAL  RALT_T(KC_ENT)
#define KC_SPNM  LT(_NUMPAD, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //          ┌────────┬────────┬────────┬────────┬────────┬────────┐   ┌────────┬────────┬────────┬────────┬────────┬────────┐
               KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  // ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
      KC_LGUI, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  // └────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┘
               KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QTSH,
  //          ├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
               KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSCT,
  //          └────────┴────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────┴────────┘
                                          L_RAISE, KC_SPNM, KC_LALT,     KC_ETAL, LOWER,   R_RAISE
                                  //     └────────┴────────┴────────┘   └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //          ┌────────┬────────┬────────┬────────┬────────┬────────┐   ┌────────┬────────┬────────┬────────┬────────┬────────┐
               _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  // ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
      _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_UP,   KC_PGUP, KC_PSCR, XXXXXXX, KC_F12,
  // └────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┘
               _______, KC_APP,  XXXXXXX, KC_HOME, KC_END,  KC_DEL,      KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,  KC_SLSF,
  //          ├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
               _______, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,     XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PAUS, KC_NLCT,
  //          └────────┴────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┴────────┴────────┴────────┴────────┘
                                          _______, _______, _______,     _______, _______, _______
                                    //   └────────┴────────┴────────┘   └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //          ┌────────┬────────┬────────┬────────┬────────┬────────┐   ┌────────┬────────┬────────┬────────┬────────┬────────┐
               _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
      _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_ENT,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // └────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┘
               _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
  //          ├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
               _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //          └────────┴────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┴────────┴────────┴────────┴────────┘
                                          _______, _______, _______,     _______, _______, _______
                                    //   └────────┴────────┴────────┘   └────────┴────────┴────────┘
  ),

  [_NUMPAD] = LAYOUT(
  //          ┌────────┬────────┬────────┬────────┬────────┬────────┐   ┌────────┬────────┬────────┬────────┬────────┬────────┐
               _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
      _______, KC_CAPS, XXXXXXX,    KC_1,    KC_2,    KC_3,  KC_ENT,     XXXXXXX, XXXXXXX, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
  // └────────┼────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┘
               _______, KC_BSPC,    KC_4,    KC_5,    KC_6,  KC_DEL,     KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
  //          ├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
               _______, XXXXXXX,    KC_7,    KC_8,    KC_9,    KC_0,     XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, _______,
  //          └────────┴────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┴────────┴────────┴────────┴────────┘
                                          _______, _______, _______,     _______, _______, _______
                                    //   └────────┴────────┴────────┘   └────────┴────────┴────────┘
  ),
};


void matrix_init_kb(void) {
    led_init_ports();
};
void led_init_ports(void) {
    setPinOutput(B0);
    writePinLow(B0);
}
void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        writePinLow(B0);
    } else {
        writePinHigh(B0);
    }
    led_set_user(usb_led);
}
