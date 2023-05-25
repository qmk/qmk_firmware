/* Copyright 2023 ziptyze
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
#include "analog.h"
#include "qmk_midi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_2x4(
                                   RGB_TOG,
        KC_1,     KC_2,     KC_3,     KC_4,
        KC_5,     KC_6,     KC_7,     KC_8
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(RGB_MOD,  RGB_RMOD)}
};
#endif

uint8_t divisor = 0;
void slider(void){
  if (divisor++) { // only run the slider function 1/256 times it's called
      return;
  }
  midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
  uprintf("%d string", analogReadPin(SLIDER_PIN) );
}

void matrix_scan_user(void) {
  slider();
}
