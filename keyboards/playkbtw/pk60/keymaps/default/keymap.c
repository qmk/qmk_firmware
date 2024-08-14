#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_all(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_ENT,
    KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_RSFT, MO(1),
    KC_LCTL, KC_LGUI, KC_LALT, MO(1),                              KC_SPC,  MO(1),   KC_RALT, MO(1),   KC_NO,   KC_APP,  KC_RCTL
  ),

  [1] = LAYOUT_all(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
    QK_BOOT, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PSCR, KC_CALC,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_SCRL, _______,
    _______, _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______
  ),

};

bool led_update_user(led_t led_state) {
  if (led_state.caps_lock) {
    gpio_set_pin_output(F4);
    gpio_write_pin_low(F4);
  } else {
    gpio_set_pin_input(F4);
    gpio_write_pin_low(F4);
  }
  return false;
}
