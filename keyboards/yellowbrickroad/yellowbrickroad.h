/* Copyright 2022 3araht
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

#pragma once

#include "quantum.h"


#ifdef RGB_MATRIX_ENABLE
// C indicator

// Max number of C indicator LEDs
#   define MAXCINDICATORLED 11
extern const uint8_t led_c_indicator[3][12][MAXCINDICATORLED];

//  default base layer color
#   define BASE_LAYER_COLOR  RGB_DARKGOLDENROD

    // flip
#   define FLIPB_LAYER_COLOR RGB_DARKYELLOW

    // trans mode
#   define TRANS_LAYER_COLOR RGB_DARKORANGE

#endif  //  RGB_MATRIX_ENABLE


extern MidiDevice midi_device;
void my_process_midi4Bass(uint8_t channel, keyrecord_t *record,
                          uint8_t *chord_status, uint8_t chord, uint16_t root_note, bool is_single_bass);

void my_process_midi4TriadChords(uint8_t channel, keyrecord_t *record,
                                 uint8_t *chord_status, uint8_t chord, uint16_t root_note,
                                 int8_t offset1, int8_t offset2, int8_t offset3);

uint8_t shift_led_indicator_left(uint8_t scale_indicator_col, uint8_t upperlimit);
uint8_t shift_led_indicator_right(uint8_t scale_indicator_col, uint8_t upperlimit);

void my_process_midi(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status, int8_t offset, bool melody_unison_suppress);
