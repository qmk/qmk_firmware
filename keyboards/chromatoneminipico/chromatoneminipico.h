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
extern led_config_t g_led_config;
extern const uint8_t led_scale_indicator[12][12];
extern const uint8_t led_single_col_indicator[37][3];
extern const uint8_t led_c_indicator[2][12][10];

//  default base layer color
#   define BASE_LAYER_COLOR  RGB_DARKGOLDENROD

//  border color
#   define FLIP_BORDER_COLOR RGB_DARKRED

// flip entirely
#   define FLIPB_LAYER_COLOR RGB_DARKYELLOW

//  channel separation group
#   define SEPALEFT_LAYER_COLOR RGB_DARKGREEN
#   define SEPAHALF_LAYER_COLOR RGB_DARKGREEN
#   define SEPARIGHT_LAYER_COLOR RGB_DARKGREEN

//  Trans group
#   define TRANS_LAYER_COLOR RGB_DARKORANGE
#   define SEPALEFT_T_LAYER_COLOR RGB_DARKORANGE
#   define SEPAHALF_T_LAYER_COLOR RGB_DARKORANGE
#   define SEPARIGHT_T_LAYER_COLOR RGB_DARKORANGE
#   define FLIPT_LAYER_COLOR RGB_DARKORANGE
#endif  //  RGB_MATRIX_ENABLE

// Defines names for use in _FN layer to specify which column to be used to turn on the LEDs.
// use this with led_single_col_indicator[37][3], ex. led_single_col_indicator[_KEY01][_BTM37].
// Also used with select_layer_state_set();
enum my_key_names {
    _KEY01= 0,
    _KEY02,
    _KEY03,
    _KEY04,
    _KEY05,
    _KEY06,
    _KEY07,
    _KEY08,
    _KEY09,
    _KEY10,
    _KEY11,
    _KEY12,
    _KEY13,
    _KEY14,
    _KEY15,
    _KEY16,
    _KEY17,
    _KEY18,
    _KEY19,
    _KEY20,
    _KEY21,
    _KEY22,
    _KEY23,
    _KEY24,
    _KEY25,
    _KEY26,
    _KEY27,
    _KEY28,
    _KEY29,
    _KEY30,
    _KEY31,
    _KEY32,
    _KEY33,
    _KEY34,
    _KEY35,
    _KEY36,
    _KEY37,
};

// Defines names used in the second index of led_single_col_indicator[37][3].
// Ex. led_single_col_indicator[_KEY01][_BTM37].
enum my_led37_layer_names {
    _BTM37= 0,      // bottom 37 LEDs
    _MID37,         // middle 37 LEDs
    _TOP37          // TOP 37 LEDs
};

extern MidiDevice midi_device;
void my_process_midi4Bass(uint8_t channel, keyrecord_t *record,
                          uint8_t *chord_status, uint8_t chord, uint16_t root_note, bool is_single_bass);

void my_process_midi4DiadChords(uint8_t channel, keyrecord_t *record,
                                uint8_t *chord_status, uint8_t chord, uint16_t root_note,
                                int8_t offset1, int8_t offset2);

void my_process_midi4TriadChords(uint8_t channel, keyrecord_t *record,
                                 uint8_t *chord_status, uint8_t chord, uint16_t root_note,
                                 int8_t offset1, int8_t offset2, int8_t offset3);

uint8_t shift_led_indicator_left(uint8_t scale_indicator_col);
uint8_t shift_led_indicator_right(uint8_t scale_indicator_col);
