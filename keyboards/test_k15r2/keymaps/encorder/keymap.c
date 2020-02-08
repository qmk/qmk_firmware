/* Copyright 2019 e3w2q
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_A1 = SAFE_RANGE,
            SEND_B1,  SEND_C1,  SEND_D1,  SEND_E1,
  SEND_A2,  SEND_B2,  SEND_C2,  SEND_D2,  SEND_E2,
  SEND_A3,  SEND_B3,  SEND_C3,  SEND_D3,  SEND_E3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *  Master Side (USB Cable Connected Side)
   *  ,---------------------------------------------------
   *  |   A1   B1   C1   D1   E1   F1   G1   H1   I1   J1
   *  |   A2   B2   C2   D2   E2   F2   G2   H2   I2   J2
   *  |   A3   B3   C3   D3   E3   F3   G3   H3   I3   J3
   *  |   A4   B4   C4   D4   E4   F4   G4   H4   I4   J4
   *  |   A5   B5   C5   D5   E5   F5   G5   H5   I5   J5
   *  |   A6   B6   C6   D6   E6   F6   G6   H6   I6   J6
   *  `---------------------------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,---------------------------------------------------
   *  |  SA1  SB1  SC1  SD1  SE1  SF1  SG1  SH1  SI1  SJ1
   *  |  SA2  SB2  SC2  SD2  SE2  SF2  SG2  SH2  SI2  SJ2
   *  |  SA3  SB3  SC3  SD3  SE3  SF3  SG3  SH3  SI3  SJ3
   *  |  SA4  SB4  SC4  SD4  SE4  SF4  SG4  SH4  SI4  SJ4
   *  |  SA5  SB5  SC5  SD5  SE5  SF5  SG5  SH5  SI5  SJ5
   *  |  SA6  SB6  SC6  SD6  SE6  SF6  SG6  SH6  SI6  SJ6
   *  `---------------------------------------------------
   */

  [0] = LAYOUT( /* Base */
    SEND_A1,  SEND_B1,  SEND_C1,  SEND_D1,  SEND_E1,
    SEND_A2,  SEND_B2,  SEND_C2,  SEND_D2,  SEND_E2,
    SEND_A3,  SEND_B3,  SEND_C3,  SEND_D3,  SEND_E3
  ),

  [1] = LAYOUT(
    RGB_TOG,  RGB_MOD,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  XXXXXXX,
    RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  RESET
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_A1: if (record->event.pressed) SEND_STRING("A1"); break;
    case SEND_B1: if (record->event.pressed) SEND_STRING("B1"); break;
    case SEND_C1: if (record->event.pressed) SEND_STRING("C1"); break;
    case SEND_D1: if (record->event.pressed) SEND_STRING("D1"); break;
    case SEND_E1: if (record->event.pressed) SEND_STRING("E1"); break;
    case SEND_A2: if (record->event.pressed) SEND_STRING("A2"); break;
    case SEND_B2: if (record->event.pressed) SEND_STRING("B2"); break;
    case SEND_C2: if (record->event.pressed) SEND_STRING("C2"); break;
    case SEND_D2: if (record->event.pressed) SEND_STRING("D2"); break;
    case SEND_E2: if (record->event.pressed) SEND_STRING("E2"); break;
    case SEND_A3: if (record->event.pressed) SEND_STRING("A3"); break;
    case SEND_B3: if (record->event.pressed) SEND_STRING("B3"); break;
    case SEND_C3: if (record->event.pressed) SEND_STRING("C3"); break;
    case SEND_D3: if (record->event.pressed) SEND_STRING("D3"); break;
    case SEND_E3: if (record->event.pressed) SEND_STRING("E3"); break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      SEND_STRING("ENC0+");
      // tap_code(KC_VOLD);
    } else {
      SEND_STRING("ENC0-");
      // tap_code(KC_VOLU);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      SEND_STRING("ENC1+");
    } else {
      SEND_STRING("ENC1-");
    }
  }
}
