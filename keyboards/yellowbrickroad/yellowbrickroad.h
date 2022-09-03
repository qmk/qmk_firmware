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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    enc, \
    k01, k02, k03, k04, k05, k06, k07, \
    k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, \
    k22, k23, k24, k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, \
    k43, k44, k45, k46, k47, k48, k49, k50, k51, k52, k53, \
    enc2, \
    sustain \
) { \
    { enc,   k01,   k02,   k03,   k04,   k05,   k06,   k07     }, \
    { k08,   k09,   k10,   k11,   k12,   k13,   k14,   k15     }, \
    { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23     }, \
    { k24,   k25,   k26,   k27,   k28,   k29,   k30,   k31     }, \
    { k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39     }, \
    { k40,   k41,   k42,   k43,   k44,   k45,   k46,   k47     }, \
    { k48,   k49,   k50,   k51,   k52,   k53,   enc2,  sustain }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO   } \
}

#ifdef RGB_MATRIX_ENABLE
extern led_config_t g_led_config;
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
