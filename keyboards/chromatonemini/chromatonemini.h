/* Copyright 2021 3araht
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
        enc,       sustain,                  ccw, cw,                                                             \
        up,                                                                                                       \
    left, right,   k01, k03, k05, k07, k09, k11, k13, k15, k17, k19, k21, k23, k25, k27, k29, k31, k33, k35, k37, \
        down,        k02, k04, k06, k08, k10, k12, k14, k16, k18, k20, k22, k24, k26, k28, k30, k32, k34, k36     \
) { \
    { enc, down, left, right, up,  k01, k02, sustain }, \
    { k03, k04,  k05,  k06,   k07, k08, k09, ccw     }, \
    { k10, k11,  k12,  k13,   k14, k15, k16, cw      }, \
    { k17, k18,  k19,  k20,   k21, k22, k23, KC_NO   }, \
    { k24, k25,  k26,  k27,   k28, k29, k30, KC_NO   }, \
    { k31, k32,  k33,  k34,   k35, k36, k37, KC_NO   }  \
}


#ifdef RGB_MATRIX_ENABLE
extern led_config_t g_led_config;
extern const uint8_t led_scale_indicator[12][12];
extern const uint8_t led_single_col_indicator[37][3];

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
// use this with led_single_col_indicator[37][3], ex. led_single_col_indicator[_FN_C2][0].
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

#ifdef MIDI_ENABLE
extern MidiDevice midi_device;
#endif  //  MIDI_ENABLE

uint8_t shift_led_indicator_left(uint8_t scale_indicator_col);
uint8_t shift_led_indicator_right(uint8_t scale_indicator_col);

void encoder_action_unregister(void);

void encoder_action_register(uint8_t index, bool clockwise);
