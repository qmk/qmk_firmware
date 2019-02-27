#include QMK_KEYBOARD_H
#include "version.h"

#define _BASE 0 // default layer
#define _FUNC 1 // symbols
#define _MED 2 // media controls

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
  VRSN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------.   ,-------------------------------.
 * |  Ins  | PgUp  | Home  |   | NmLck |   /   |   *   |   -   |
 * |-------+-------+-------|   |-------+-------+-------+-------|
 * |  Del  | PgDn  |  Fn   |   |   7   |   8   |   9   |       |
 * |-------+-------+-------|   |-------+-------+-------+   +   |
 * |       |       |       |   |   4   |   5   |   6   |       |
 * |-------+-------+-------|   |-------+-------+-------+-------|
 * |       |  Up   |       |   |   1   |   2   |   3   |       |
 * |-------+-------+-------|   |-------+-------+-------+ Enter |
 * | Left  | Down  | Right |   |       0       |   .   |       |
 * `-----------------------'   `-------------------------------'
 */
[_BASE] = LAYOUT(  // layer 0 : default
  //   +---------+---------+---------+
        KC_NO    ,KC_HOME  ,KC_PGUP  ,KC_INS   ,
  //   +---------+---------+---------+
        KC_NO    ,MO(_FUNC),KC_PGDN  ,KC_DEL   ,
  //   +---------+---------+---------+
        KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,
  //   +---------+---------+---------+
        KC_NO    ,KC_NO    ,KC_UP    ,KC_NO   ,
  //   +---------+---------+---------+
        KC_NO    ,KC_RIGHT ,KC_DOWN  ,KC_LEFT  ,
  //   +---------+---------+---------+---------+
        KC_NLCK  ,KC_PSLS  ,KC_PAST  ,KC_PMNS  ,
  //   +---------+---------+---------+---------+
        KC_P7    ,KC_P8    ,KC_P9   , KC_NO    ,
  //   +---------+---------+---------+---------+
        KC_P4    ,KC_P5    ,KC_P6    ,KC_PPLS  ,
  //  +---------+---------+---------+---------+
        KC_P1    ,KC_P2    ,KC_P3    ,KC_NO    ,
  //   +---------+---------+---------+---------+
        KC_P0    ,KC_NO    ,KC_PDOT  ,KC_PENT
  //   +---------+---------+---------+---------+
  ),

  /* Keymap 1: 2nd layer
   *
   * ,----------------------.   ,-------------------------------.
   * | Sleep |       |       |   |       |       | BriU  | BriD  |
   * |-------+-------+-------|   |-------+-------+-------+-------|
   * | Wake  |       |       |   | Stop  | VolU  | Mute  | start |
   * |-------+-------+-------|   |-------+-------+-------+Player |
   * |       |       |       |   | Prev  | Play  | Next  |       |
   * |-------+-------+-------|   |-------+-------+-------+-------|
   * |       |       |       |   |       | VolD  |       |       |
   * |-------+-------+-------|   |-------+-------+-------+ Play  |
   * |       |       |       |   |     Calc      |My Comp|       |
   * `-----------------------'   `-------------------------------'
   */
  [_FUNC] = LAYOUT(  // layer 0 : default
    //   +---------+---------+---------+
          KC_SLEP  ,KC_TRNS  ,KC_TRNS  ,KC_NO    ,
    //   +---------+---------+---------+
          KC_WAKE  ,KC_TRNS  ,KC_TRNS  ,KC_NO    ,
    //   +---------+---------+---------+
          KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,
    //   +---------+---------+---------+
          KC_NO    ,KC_TRNS  ,KC_NO   ,KC_NO    ,
    //   +---------+---------+---------+
          KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_NO    ,
    //   +---------+---------+---------+
    //   +---------+---------+---------+---------+
          KC_TRNS  ,KC_TRNS  ,KC_BRIU  ,KC_BRID  ,
    //   +---------+---------+---------+---------+
          KC_MSTP  ,KC_VOLU  ,KC_MUTE, KC_NO    ,
    //   +---------+---------+---------+---------+
          KC_MPRV  ,KC_MPLY  ,KC_MNXT  ,KC_MSEL  ,
    //   +---------+---------+---------+---------+
          KC_TRNS  ,KC_VOLD  ,KC_TRNS  ,KC_NO    ,
    //   +---------+---------+---------+---------+
          KC_CALC  ,KC_NO    ,KC_MYCM  ,KC_MPLY
    //   +---------+---------+---------+---------+
    ),};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOGIN:
      if (record->event.pressed) {
        // when keycode LOGIN is pressed
        SEND_STRING("43110");
      } else {
        // when keycode LOGIN is released
      }
      break;
​
  }
  return true;
};
​
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {
    {LOGIN, KC_ESC}
  }
};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTC |= (1<<6);
    } else {
        PORTC &= ~(1<<6);
  }
}
