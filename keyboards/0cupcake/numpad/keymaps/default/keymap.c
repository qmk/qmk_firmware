/* Copyright 2021 Shulin Huang <mumu@x-bows.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H


void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(B3);
  setPinOutput(E6);
  setPinOutput(B2);
  setPinOutput(B4);
  setPinOutput(B6);
  setPinOutput(B5);

};

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (biton32(state)) {
    case 0:
       writePin(B3, false); //R Der.
       writePin(E6, false); //R Izq.
       writePin(B2, false); //G Der.
       writePin(B4, false); //G Izq.
       writePin(B6, false); //B Der.
       writePin(B5, false); //B Izq.
      break;
    case 1:
       writePin(B3, true); //R Der.
       writePin(E6, true); //R Izq.
       writePin(B2, false); //G Der.
       writePin(B4, false); //G Izq.
       writePin(B6, false); //B Der.
       writePin(B5, false); //B Izq.
      break;
//    case 2:
//       writePin(B3, true); //R Der.
//       writePin(E6, true); //R Izq.
//       writePin(B2, false); //G Der.
//       writePin(B4, false); //G Izq.
//       writePin(B6, false); //B Der.
//       writePin(B5, false); //B Izq.
      break;
  }
  return state;  //estados de backlight vs layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//Layer Base
  [0] = LAYOUT(
    KC_NUM,   KC_PSLS,  KC_PAST,  KC_BSPC,
    KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
    KC_P0,    KC_PDOT,  MO(3)
    ),

  [3] = LAYOUT(
    TO(1),      KC_TRNS,  KC_TRNS,    KC_EQL,
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,  KC_TRNS
    ),

//Layer Macros
  [1] = LAYOUT(
    QK_BOOT,   KC_TRNS,    KC_TRNS,   KC_TRNS,
    RGB_MOD,   RGB_VAI,   RGB_HUI,   KC_VOLD,
    RGB_SPD,   RGB_TOG,   RGB_SPI,   KC_VOLU,
    KC_TRNS,   RGB_VAD,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS,   MO(2)
    ),

//Layer Fusion
  [2] = LAYOUT(
    TO(0),   KC_TRNS,    KC_TRNS,   KC_TRNS,
    RGB_MOD,   RGB_VAI,   RGB_HUI,   KC_VOLD,
    RGB_SPD,   RGB_TOG,   RGB_SPI,   KC_VOLU,
    KC_TRNS,   RGB_VAD,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS,   KC_TRNS
    )
};

