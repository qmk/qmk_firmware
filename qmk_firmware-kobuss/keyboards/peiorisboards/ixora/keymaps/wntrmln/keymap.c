#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------.
   * |RESET|  2  |  3  |
   * |-----------------|
   * |Caps |NmLk |ScLk |
   * `-----------------'
   */
[0] = LAYOUT_full(
  KC_PSCR, KC_MUTE, LGUI(KC_1),
  KC_MPRV, KC_MPLY, KC_MNXT)
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
