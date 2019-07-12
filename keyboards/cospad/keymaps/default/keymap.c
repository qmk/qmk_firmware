#include QMK_KEYBOARD_H
#include "led.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * |Esc |TAB | FN | BS |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |   0     | .  |    |
   * `-------------------'
   */

[_BL] = LAYOUT_numpad_6x4(
  KC_ESC,   KC_TAB,   MO(_FL),   KC_BSPC, \
  KC_NLCK,  KC_PSLS,  KC_PAST,   KC_PMNS, \
  KC_P7,    KC_P8,    KC_P9,              \
  KC_P4,    KC_P5,    KC_P6,     KC_PPLS, \
  KC_P1,    KC_P2,    KC_P3,              \
  KC_P0,              KC_PDOT,   KC_PENT),

  /* Keymap _FL: Function Layer
   * ,-------------------.
   * |RGBT|TAB | FN | BS |
   * |----|----|----|----|
   * |RGBM|RGBP|BTOG| -  |
   * |----|----|----|----|
   * |HUD |HUI |BON |    |
   * |----|----|----| +  |
   * |SAD |SAI |BOFF|    |
   * |----|----|----|----|
   * |VAD |VAS | 3  |    |
   * |----|----|----| En |
   * |   0     |RST |    |
   * `-------------------'
   */
[_FL] = LAYOUT_numpad_6x4(
  RGB_TOG,  KC_TAB,   KC_TRNS,   KC_BSPC, \
  RGB_MOD,  RGB_M_P,  BL_TOGG,   KC_PMNS, \
  RGB_HUD,  RGB_HUI,  BL_ON,              \
  RGB_SAD,  RGB_SAI,  BL_OFF,    KC_PPLS, \
  RGB_VAD,  RGB_VAI,  KC_P3,              \
  KC_P0,              RESET,     KC_PENT),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case BL_TOGG:
         if (record->event.pressed) {
            cospad_bl_led_togg();
         }
         return false;
      case BL_ON:
         if (record->event.pressed) {
            cospad_bl_led_on();
         }
         return false;
      case BL_OFF:
         if(record->event.pressed) {
            cospad_bl_led_off();
         }
         return false;
      default:
         return true;
   }
}
