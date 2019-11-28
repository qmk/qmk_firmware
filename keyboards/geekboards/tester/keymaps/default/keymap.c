#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( /* Base */
    RGB_MOD,  KC_1,     KC_2,     KC_3,
    KC_4,   KC_5,     KC_6,     MO(1)
    ),
[1] = LAYOUT( /* Base */
    KC_ESC,  KC_F1,     KC_F2,     KC_F3,
    KC_F4,   KC_F5,     KC_F6,     KC_F7
    ),
};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
