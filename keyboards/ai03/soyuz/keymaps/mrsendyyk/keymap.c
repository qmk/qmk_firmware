#include QMK_KEYBOARD_H

// Sendy YK's Keymap
// ai03 Design Studio Soyuz Numpad 5x4
// LAYOUT_Numpad_5x4_mrsendyyk

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default [0]
   * ,-----------------------.
   * |Num L|  /  |  *  |  -  |
   * |-----------------------+
   * |  7  |  8  |  9  |     |
   * |-----------------|  +  |
   * |  4  |  5  |  6  |     |
   * |-----------------------+
   * |  1  |  2  |  3  |     |
   * |-----------------|Enter|
   * |     0     |  .  |     |
   * `-----------------------'
   */

   [0] = LAYOUT_Numpad_5x4_mrsendyyk(KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
	                                 KC_P7, KC_P8, KC_P9,
									 KC_P4, KC_P5, KC_P6, KC_PPLS,
									 KC_P1, KC_P2, KC_P3,
									 KC_P0, KC_PDOT, KC_PENT)
}
