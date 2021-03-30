/*
Copyright 2018 Jordi Pakey-Rodriguez

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    LT(1, KC_NLCK), KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_P7,          KC_P8,    KC_P9,    KC_PPLS,
    KC_P4,          KC_P5,    KC_P6,    KC_PEQL,
    KC_P1,          KC_P2,    KC_P3,    KC_TAB,
    KC_PCMM,        KC_P0,    KC_PDOT,  KC_PENT
  ),

  [1] = LAYOUT(
    _______,  RESET,    BL_STEP,  RGB_TOG,
    RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_MOD,
    RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_RMOD,
    RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW,
    RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G
  ),

};

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    // Illuminate the LED under the Num Lock key
    rgblight_sethsv_at(0, 0, 127, 1);
  } else {
    rgblight_sethsv_at(0, 0, 0, 1);
  }
}
