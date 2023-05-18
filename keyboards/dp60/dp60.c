/**
 * dp60.c
 *
  Copyright 2020 astro <yuleiz@gmail.com>
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
// left CA
    {0, C1_1,   C3_2,   C4_2},
    {0, C1_2,   C2_2,   C4_3},
    {0, C1_3,   C2_3,   C3_3},
    {0, C1_4,   C2_4,   C3_4},
    {0, C1_5,   C2_5,   C3_5},
    {0, C1_6,   C2_6,   C3_6},
    {0, C1_7,   C2_7,   C3_7},
    {0, C1_8,   C2_8,   C3_8},

    {0, C5_1,   C4_1,   C6_1},
    {0, C5_8,   C4_8,   C6_8},

    {0, C9_1,   C8_1,   C7_1},
    {0, C9_2,   C8_2,   C7_2},
    {0, C9_3,   C8_3,   C7_3},
    {0, C9_4,   C8_4,   C7_4},
    {0, C9_5,   C8_5,   C7_5},
    {0, C9_6,   C8_6,   C7_6},
    {0, C9_7,   C8_7,   C6_6},
    {0, C9_8,   C7_7,   C6_7},
// left CB
    {0, C1_9,   C3_10,  C4_10},
    {0, C1_10,  C2_10,  C4_11},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
    {0, C1_13,  C2_13,  C3_13},
    {0, C1_14,  C2_14,  C3_14},
    {0, C1_15,  C2_15,  C3_15},
    {0, C1_16,  C2_16,  C3_16},

    {0, C5_9,   C4_9,   C6_9},
    {0, C5_16,  C4_16,  C6_16},

    {0, C9_9,   C8_9,   C7_9},
    {0, C9_10,  C8_10,  C7_10},
    {0, C9_11,  C8_11,  C7_11},
    {0, C9_12,  C8_12,  C7_12},
    {0, C9_13,  C8_13,  C7_13},
    {0, C9_14,  C8_14,  C7_14},
    {0, C9_15,  C8_15,  C6_14},
    {0, C9_16,  C7_15,  C6_15},

// right CA
    {1, C1_1,   C3_2,   C4_2},
    {1, C1_2,   C2_2,   C4_3},
    {1, C1_3,   C2_3,   C3_3},
    {1, C1_4,   C2_4,   C3_4},
    {1, C1_5,   C2_5,   C3_5},
    {1, C1_6,   C2_6,   C3_6},
    {1, C1_7,   C2_7,   C3_7},
    {1, C1_8,   C2_8,   C3_8},

    {1, C5_1,   C4_1,   C6_1},
    {1, C5_8,   C4_8,   C6_8},

    {1, C9_1,   C8_1,   C7_1},
    {1, C9_2,   C8_2,   C7_2},
    {1, C9_3,   C8_3,   C7_3},
    {1, C9_4,   C8_4,   C7_4},
    {1, C9_5,   C8_5,   C7_5},
    {1, C9_6,   C8_6,   C7_6},
    {1, C9_7,   C8_7,   C6_6},
    {1, C9_8,   C7_7,   C6_7},
// right CB
    {1, C1_9,   C3_10,  C4_10},
    {1, C1_10,  C2_10,  C4_11},
    {1, C1_11,  C2_11,  C3_11},
    {1, C1_12,  C2_12,  C3_12},
    {1, C1_13,  C2_13,  C3_13},
    {1, C1_14,  C2_14,  C3_14},
    {1, C1_15,  C2_15,  C3_15},
    {1, C1_16,  C2_16,  C3_16},

    {1, C5_9,   C4_9,   C6_9},
    {1, C5_16,  C4_16,  C6_16},

    {1, C9_9,   C8_9,   C7_9},
    {1, C9_10,  C8_10,  C7_10},
    {1, C9_11,  C8_11,  C7_11},
    {1, C9_12,  C8_12,  C7_12},
    {1, C9_13,  C8_13,  C7_13},
    {1, C9_14,  C8_14,  C7_14},
    {1, C9_15,  C8_15,  C6_14},
    {1, C9_16,  C7_15,  C6_15},
};

led_config_t g_led_config = {
    {
        {  0,  1,      2,      3,      4,      5,   6,  36,     37,     38,      39,   40,   41, 42},
        {  8,  9,     10,     11,     12,     13,   7,  45,     46,     47,      48,   49,   50, 51},
        {  26,27,     18,     14,     15,     16,  17,  54,     55,     56,      57,   58,   59, 53},
        {  29,30,     31,     19,     20,     21,  22,  23,     62,     63,      64,   65,   66, 61},
        {  35,34,     33, NO_LED, NO_LED, NO_LED,  24,  44, NO_LED, NO_LED,      68,   69,   70, 71},
    },
    {
        { 32, 32},{ 48, 48},{ 64, 48},{ 80, 48},{ 96, 48},{112, 48},{ 96, 64},{ 96, 64},
        {  0, 32},{ 16, 32},
        {  0, 48},{  0, 48},{ 16, 48},{ 32, 48},{ 64, 64},{ 32, 64},{ 16, 64},{  0, 64},
        {  0,  0},{ 16,  0},{ 32,  0},{ 48,  0},{ 64,  0},{ 80,  0},{ 96,  0},{ 96, 16},
        { 0,  16},{ 16, 16},
        { 32, 16},{ 48, 16},{ 64, 16},{ 80, 16},{ 48, 32},{ 64, 32},{ 80, 32},{ 96, 32},

        {128,  0},{144,  0},{160,  0},{176,  0},{192,  0},{208,  0},{216,  0},{224,  0},
        {112,  0},{128, 16},
        {144, 16},{160, 16},{176, 16},{192, 16},{208, 16},{224, 16},{224, 32},{216, 32},
        {128, 32},{144, 32},{160, 32},{176, 32},{192, 32},{208, 32},{208, 48},{224, 48},
        {128, 48},{144, 48},
        {160, 48},{176, 48},{192, 48},{142, 64},{160, 64},{176, 64},{208, 64},{224, 64}
    },
    {
        4, 4, 4, 4, 4, 4, 4, 4,
        1, 4,
        4, 4, 1, 1, 1, 4, 4, 4,

        1, 4, 4, 4, 4, 4, 4, 4,
        1, 4,
        4, 4, 4, 4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4, 1, 1,
        4, 4,
        4, 4, 4, 4, 4, 1, 1, 1,

        4, 4, 4, 4, 4, 4, 4, 1,
        1, 4,
        4, 4, 4, 4, 1, 1, 1, 1,
    }
};

#endif

#ifdef WEBUSB_ENABLE
#include "webusb.h"
#include "dynamic_keymap.h"


webusb_pos_t webusb_keymap[] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {4, 7}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0, 13},

    {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10}, {1, 11}, {1, 12}, {1, 13},

    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 13},

    {3, 0}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, {3, 13},

    {4, 0}, {4, 1}, {4, 2}, {4, 6}, {4, 10}, {4, 11}, {4, 12}, {4, 13},
};
#endif

#ifndef RAW_ENABLE
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#else
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#endif
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGBLIGHT_ENABLE
        #ifdef RGB_MATRIX_ENABLE
        case KC_F13: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case KC_F14:
            rgb_matrix_step();
            return false;
        #endif
    #endif
        default:
        break;
    }
  }
  return true;
}
