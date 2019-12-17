#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5,
    KC_6, KC_7, KC_8, KC_9, KC_0, KC_ENTER),

};

void matrix_init_user(void) {
  debug_config.matrix = 1;
  debug_config.keyboard = 1;
  debug_config.enable = 1;
}

void encoder_update_user(int8_t index, bool clockwise) {
    if (clockwise) {
      tap_code16(C(KC_T));
    } else {
      tap_code16(C(KC_W));
    }
}

