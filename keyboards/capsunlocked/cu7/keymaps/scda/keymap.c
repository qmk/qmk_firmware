#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
             MO(1),
    KC_1,    KC_2,    KC_3,
    KC_4,    KC_5,    KC_6
  ),
  [1] = LAYOUT(
             MO(0),
    RGB_MOD, KC_UP,   RESET,
    KC_LEFT, KC_DOWN, KC_RGHT
  ),
};

// Volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code_delay(KC_VOLU, 10);
  }
  else {
    tap_code_delay(KC_VOLD, 10);
  }

  return true;
}
