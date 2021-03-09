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
            SEND_A2,  SEND_A3,  SEND_A4,  SEND_A5,  SEND_A6,
  SEND_B1,  SEND_B2,  SEND_B3,  SEND_B4,  SEND_B5,  SEND_B6,
  SEND_C1,  SEND_C2,  SEND_C3,  SEND_C4,  SEND_C5,  SEND_C6,
  SEND_D1,  SEND_D2,  SEND_D3,  SEND_D4,  SEND_D5,  SEND_D6,
  SEND_E1,  SEND_E2,  SEND_E3,  SEND_E4,  SEND_E5,  SEND_E6,
  SEND_F1,  SEND_F2,  SEND_F3,  SEND_F4,  SEND_F5,  SEND_F6,
  SEND_G1,  SEND_G2,  SEND_G3,  SEND_G4,  SEND_G5,  SEND_G6,
  SEND_H1,  SEND_H2,  SEND_H3,  SEND_H4,  SEND_H5,  SEND_H6,

  SEND_SA1, SEND_SA2, SEND_SA3, SEND_SA4, SEND_SA5, SEND_SA6,
  SEND_SB1, SEND_SB2, SEND_SB3, SEND_SB4, SEND_SB5, SEND_SB6,
  SEND_SC1, SEND_SC2, SEND_SC3, SEND_SC4, SEND_SC5, SEND_SC6,
  SEND_SD1, SEND_SD2, SEND_SD3, SEND_SD4, SEND_SD5, SEND_SD6,
  SEND_SE1, SEND_SE2, SEND_SE3, SEND_SE4, SEND_SE5, SEND_SE6,
  SEND_SF1, SEND_SF2, SEND_SF3, SEND_SF4, SEND_SF5, SEND_SF6,
  SEND_SG1, SEND_SG2, SEND_SG3, SEND_SG4, SEND_SG5, SEND_SG6,
  SEND_SH1, SEND_SH2, SEND_SH3, SEND_SH4, SEND_SH5, SEND_SH6
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-------------------------------
   *  |   A1   A2   A3   A4   A5   A6 
   *  |   B1   B2   B3   B4   B5   B6 
   *  |   C1   C2   C3   C4   C5   C6 
   *  |   D1   D2   D3   D4   D5   D6 
   *  |   E1   E2   E3   E4   E5   E6 
   *  |   F1   F2   F3   F4   F5   F6 
   *  |   G1   G2   G3   G4   G5   G6 
   *  |   H1   H2   H3   H4   H5   H6 
   *  `-------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-------------------------------
   *  |  SA1  SA2  SA3  SA4  SA5  SA6 
   *  |  SB1  SB2  SB3  SB4  SB5  SB6 
   *  |  SC1  SC2  SC3  SC4  SC5  SC6 
   *  |  SD1  SD2  SD3  SD4  SD5  SD6 
   *  |  SE1  SE2  SE3  SE4  SE5  SE6 
   *  |  SF1  SF2  SF3  SF4  SF5  SF6 
   *  |  SG1  SG2  SG3  SG4  SG5  SG6 
   *  |  SH1  SH2  SH3  SH4  SH5  SH6 
   *  `-------------------------------
   */

  [0] = LAYOUT( /* Base */ 
    SEND_A1,  SEND_A2,  SEND_A3,  SEND_A4,  SEND_A5,  SEND_A6,
    SEND_B1,  SEND_B2,  SEND_B3,  SEND_B4,  SEND_B5,  SEND_B6,
    SEND_C1,  SEND_C2,  SEND_C3,  SEND_C4,  SEND_C5,  SEND_C6,
    SEND_D1,  SEND_D2,  SEND_D3,  SEND_D4,  SEND_D5,  SEND_D6,
    SEND_E1,  SEND_E2,  SEND_E3,  SEND_E4,  SEND_E5,  SEND_E6,
    SEND_F1,  SEND_F2,  SEND_F3,  SEND_F4,  SEND_F5,  SEND_F6,
    SEND_G1,  SEND_G2,  SEND_G3,  SEND_G4,  SEND_G5,  SEND_G6,
    SEND_H1,  SEND_H2,  SEND_H3,  SEND_H4,  SEND_H5,  SEND_H6,

    SEND_SA1, SEND_SA2, SEND_SA3, SEND_SA4, SEND_SA5, SEND_SA6,
    SEND_SB1, SEND_SB2, SEND_SB3, SEND_SB4, SEND_SB5, SEND_SB6,
    SEND_SC1, SEND_SC2, SEND_SC3, SEND_SC4, SEND_SC5, SEND_SC6,
    SEND_SD1, SEND_SD2, SEND_SD3, SEND_SD4, SEND_SD5, SEND_SD6,
    SEND_SE1, SEND_SE2, SEND_SE3, SEND_SE4, SEND_SE5, SEND_SE6,
    SEND_SF1, SEND_SF2, SEND_SF3, SEND_SF4, SEND_SF5, SEND_SF6,
    SEND_SG1, SEND_SG2, SEND_SG3, SEND_SG4, SEND_SG5, SEND_SG6,
    SEND_SH1, SEND_SH2, SEND_SH3, SEND_SH4, SEND_SH5, SEND_SH6
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_A1: if (record->event.pressed) SEND_STRING("A1"); break;
    case SEND_B1: if (record->event.pressed) SEND_STRING("B1"); break;
    case SEND_C1: if (record->event.pressed) SEND_STRING("C1"); break;
    case SEND_D1: if (record->event.pressed) SEND_STRING("D1"); break;
    case SEND_E1: if (record->event.pressed) SEND_STRING("E1"); break;
    case SEND_F1: if (record->event.pressed) SEND_STRING("F1"); break;
    case SEND_G1: if (record->event.pressed) SEND_STRING("G1"); break;
    case SEND_H1: if (record->event.pressed) SEND_STRING("H1"); break;
    case SEND_A2: if (record->event.pressed) SEND_STRING("A2"); break;
    case SEND_B2: if (record->event.pressed) SEND_STRING("B2"); break;
    case SEND_C2: if (record->event.pressed) SEND_STRING("C2"); break;
    case SEND_D2: if (record->event.pressed) SEND_STRING("D2"); break;
    case SEND_E2: if (record->event.pressed) SEND_STRING("E2"); break;
    case SEND_F2: if (record->event.pressed) SEND_STRING("F2"); break;
    case SEND_G2: if (record->event.pressed) SEND_STRING("G2"); break;
    case SEND_H2: if (record->event.pressed) SEND_STRING("H2"); break;
    case SEND_A3: if (record->event.pressed) SEND_STRING("A3"); break;
    case SEND_B3: if (record->event.pressed) SEND_STRING("B3"); break;
    case SEND_C3: if (record->event.pressed) SEND_STRING("C3"); break;
    case SEND_D3: if (record->event.pressed) SEND_STRING("D3"); break;
    case SEND_E3: if (record->event.pressed) SEND_STRING("E3"); break;
    case SEND_F3: if (record->event.pressed) SEND_STRING("F3"); break;
    case SEND_G3: if (record->event.pressed) SEND_STRING("G3"); break;
    case SEND_H3: if (record->event.pressed) SEND_STRING("H3"); break;
    case SEND_A4: if (record->event.pressed) SEND_STRING("A4"); break;
    case SEND_B4: if (record->event.pressed) SEND_STRING("B4"); break;
    case SEND_C4: if (record->event.pressed) SEND_STRING("C4"); break;
    case SEND_D4: if (record->event.pressed) SEND_STRING("D4"); break;
    case SEND_E4: if (record->event.pressed) SEND_STRING("E4"); break;
    case SEND_F4: if (record->event.pressed) SEND_STRING("F4"); break;
    case SEND_G4: if (record->event.pressed) SEND_STRING("G4"); break;
    case SEND_H4: if (record->event.pressed) SEND_STRING("H4"); break;
    case SEND_A5: if (record->event.pressed) SEND_STRING("A5"); break;
    case SEND_B5: if (record->event.pressed) SEND_STRING("B5"); break;
    case SEND_C5: if (record->event.pressed) SEND_STRING("C5"); break;
    case SEND_D5: if (record->event.pressed) SEND_STRING("D5"); break;
    case SEND_E5: if (record->event.pressed) SEND_STRING("E5"); break;
    case SEND_F5: if (record->event.pressed) SEND_STRING("F5"); break;
    case SEND_G5: if (record->event.pressed) SEND_STRING("G5"); break;
    case SEND_H5: if (record->event.pressed) SEND_STRING("H5"); break;
    case SEND_A6: if (record->event.pressed) SEND_STRING("A6"); break;
    case SEND_B6: if (record->event.pressed) SEND_STRING("B6"); break;
    case SEND_C6: if (record->event.pressed) SEND_STRING("C6"); break;
    case SEND_D6: if (record->event.pressed) SEND_STRING("D6"); break;
    case SEND_E6: if (record->event.pressed) SEND_STRING("E6"); break;
    case SEND_F6: if (record->event.pressed) SEND_STRING("F6"); break;
    case SEND_G6: if (record->event.pressed) SEND_STRING("G6"); break;
    case SEND_H6: if (record->event.pressed) SEND_STRING("H6"); break;
    case SEND_SA1: if (record->event.pressed) SEND_STRING("SA1"); break;
    case SEND_SB1: if (record->event.pressed) SEND_STRING("SB1"); break;
    case SEND_SC1: if (record->event.pressed) SEND_STRING("SC1"); break;
    case SEND_SD1: if (record->event.pressed) SEND_STRING("SD1"); break;
    case SEND_SE1: if (record->event.pressed) SEND_STRING("SE1"); break;
    case SEND_SF1: if (record->event.pressed) SEND_STRING("SF1"); break;
    case SEND_SG1: if (record->event.pressed) SEND_STRING("SG1"); break;
    case SEND_SH1: if (record->event.pressed) SEND_STRING("SH1"); break;
    case SEND_SA2: if (record->event.pressed) SEND_STRING("SA2"); break;
    case SEND_SB2: if (record->event.pressed) SEND_STRING("SB2"); break;
    case SEND_SC2: if (record->event.pressed) SEND_STRING("SC2"); break;
    case SEND_SD2: if (record->event.pressed) SEND_STRING("SD2"); break;
    case SEND_SE2: if (record->event.pressed) SEND_STRING("SE2"); break;
    case SEND_SF2: if (record->event.pressed) SEND_STRING("SF2"); break;
    case SEND_SG2: if (record->event.pressed) SEND_STRING("SG2"); break;
    case SEND_SH2: if (record->event.pressed) SEND_STRING("SH2"); break;
    case SEND_SA3: if (record->event.pressed) SEND_STRING("SA3"); break;
    case SEND_SB3: if (record->event.pressed) SEND_STRING("SB3"); break;
    case SEND_SC3: if (record->event.pressed) SEND_STRING("SC3"); break;
    case SEND_SD3: if (record->event.pressed) SEND_STRING("SD3"); break;
    case SEND_SE3: if (record->event.pressed) SEND_STRING("SE3"); break;
    case SEND_SF3: if (record->event.pressed) SEND_STRING("SF3"); break;
    case SEND_SG3: if (record->event.pressed) SEND_STRING("SG3"); break;
    case SEND_SH3: if (record->event.pressed) SEND_STRING("SH3"); break;
    case SEND_SA4: if (record->event.pressed) SEND_STRING("SA4"); break;
    case SEND_SB4: if (record->event.pressed) SEND_STRING("SB4"); break;
    case SEND_SC4: if (record->event.pressed) SEND_STRING("SC4"); break;
    case SEND_SD4: if (record->event.pressed) SEND_STRING("SD4"); break;
    case SEND_SE4: if (record->event.pressed) SEND_STRING("SE4"); break;
    case SEND_SF4: if (record->event.pressed) SEND_STRING("SF4"); break;
    case SEND_SG4: if (record->event.pressed) SEND_STRING("SG4"); break;
    case SEND_SH4: if (record->event.pressed) SEND_STRING("SH4"); break;
    case SEND_SA5: if (record->event.pressed) SEND_STRING("SA5"); break;
    case SEND_SB5: if (record->event.pressed) SEND_STRING("SB5"); break;
    case SEND_SC5: if (record->event.pressed) SEND_STRING("SC5"); break;
    case SEND_SD5: if (record->event.pressed) SEND_STRING("SD5"); break;
    case SEND_SE5: if (record->event.pressed) SEND_STRING("SE5"); break;
    case SEND_SF5: if (record->event.pressed) SEND_STRING("SF5"); break;
    case SEND_SG5: if (record->event.pressed) SEND_STRING("SG5"); break;
    case SEND_SH5: if (record->event.pressed) SEND_STRING("SH5"); break;
    case SEND_SA6: if (record->event.pressed) SEND_STRING("SA6"); break;
    case SEND_SB6: if (record->event.pressed) SEND_STRING("SB6"); break;
    case SEND_SC6: if (record->event.pressed) SEND_STRING("SC6"); break;
    case SEND_SD6: if (record->event.pressed) SEND_STRING("SD6"); break;
    case SEND_SE6: if (record->event.pressed) SEND_STRING("SE6"); break;
    case SEND_SF6: if (record->event.pressed) SEND_STRING("SF6"); break;
    case SEND_SG6: if (record->event.pressed) SEND_STRING("SG6"); break;
    case SEND_SH6: if (record->event.pressed) SEND_STRING("SH6"); break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
