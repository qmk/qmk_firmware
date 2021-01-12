#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base */
  [_BASE] = LAYOUT(
    KC_1, KC_2,
    KC_3, KC_4,
    KC_5, KC_6,
    KC_7, KC_8,
    KC_9, KC_A,
    KC_B, KC_C
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
