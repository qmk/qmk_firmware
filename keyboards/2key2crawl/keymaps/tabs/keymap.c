#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

KEYMAP(
    KC_1, KC_2, KC_3, KC_4, KC_5,
    KC_6, KC_7, KC_8, KC_9, KC_0, KC_ENTER),

};

void matrix_init_user(void) {
  debug_config.matrix = 1;
  debug_config.keyboard = 1;
  debug_config.enable = 1;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void encoder_update_user(int8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      register_code(KC_LCTRL);
      register_code(KC_T);
      unregister_code(KC_T);
      unregister_code(KC_LCTRL);
    } else {
      register_code(KC_LCTRL);
      register_code(KC_W);
      unregister_code(KC_W);
      unregister_code(KC_LCTRL);
    }
  }
}

