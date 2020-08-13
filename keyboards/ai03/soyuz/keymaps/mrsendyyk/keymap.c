#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* [0]
   * ,-------------------.
   * |Nm L|/   |*   |-   |
   * |-------------------+
   * |7   |8   |9   |    |
   * |--------------|+   |
   * |4   |5   |6   |    |
   * |-------------------+
   * |1   | 2  |3   |    |
   * |--------------|Entr|
   * |0        |.   |    |
   * `-------------------'
   */

  [0] = LAYOUT_5x4(LT(1, KC_NLCK), KC_PSLS, KC_PAST, KC_PMNS,
	                 KC_P7, KC_P8, KC_P9,
									 KC_P4, KC_P5, KC_P6, KC_PPLS,
									 KC_P1, KC_P2, KC_P3,
									 KC_P0, KC_PDOT, KC_PENT)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
};

void matrix_init_user(void) {

};

void matrix_scan_user(void) {

};

void led_set_user(uint8_t usb_led) {

}
