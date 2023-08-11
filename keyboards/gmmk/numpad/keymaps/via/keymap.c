/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
Modified 2022 by rustedaperture for qmk_firmware
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
#include "analog.h"
#include "qmk_midi.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       ENCODER
//      1        2       3       RET
//      0                        .

  [0] = LAYOUT(
    MO(1),   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,   KC_P8,     KC_P9,     KC_PPLS,
    KC_P4,   KC_P5,     KC_P6,     KC_CALC,
    KC_P1,   KC_P2,     KC_P3,     KC_PENT,
    KC_P0,                         KC_PDOT
  ),
  [1] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
    RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
    KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
    RGB_TOG,                         QK_BOOT
  ),
  [2] = LAYOUT(
    _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,
    _______,                         _______
  ),
  [3] = LAYOUT(
    _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,
    _______,                         _______
  ),
};
// clang-format on

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};

// Potentiometer Slider, MIDI Control

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }
    midi_send_cc(&midi_device, 2, 0x3E, 0x7F + (analogReadPin(SLIDER_PIN) >> 3));
}

void housekeeping_task_user(void) {
    slider();
}