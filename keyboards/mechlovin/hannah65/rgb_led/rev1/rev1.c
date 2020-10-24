/* Copyright 2020 Mechlovin'
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

#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C2_1,   C3_1,   C4_1}, //D9-00-0
    {0, C5_1,   C6_1,   C7_1}, //D60-01-1
    {0, C1_1,   C3_2,   C4_2}, //D72-02-2
    {0, C5_2,   C6_2,   C7_2}, //D77-03-3
    {0, C1_2,   C2_2,   C4_3}, //D82-04-4
    {0, C5_3,   C6_3,   C7_3}, //D87-05-5
    {0, C1_3,   C2_3,   C3_3}, //D92-06-6
    {0, C5_4,   C6_4,   C7_4}, //D97-07-7
    {0, C1_4,   C2_4,   C3_4}, //D104-08-8
    {0, C4_4,   C6_5,   C7_5}, //D109-09-9
    {0, C1_5,   C2_5,   C3_5}, //D114-0A-10
    {0, C4_5,   C5_5,   C7_6}, //D120-0B-11
    {0, C1_6,   C2_6,   C3_6}, //D126-0C-12
    {0, C4_6,   C5_6,   C6_6}, //D131-0D-13
    {0, C1_7,   C2_7,   C3_7}, //D138-1D-14
    {0, C4_7,   C5_7,   C6_7}, //D165-0E-15

    {0, C2_9,   C3_9,   C4_9},  //D46-10-16
    {0, C5_9,   C6_9,   C7_9},  //D61-11-17
    {0, C1_9,   C3_10,  C4_10}, //D73-12-18
    {0, C5_10,  C6_10,  C7_10}, //D78-13-19
    {0, C1_10,  C2_10,  C4_11}, //D83-14-20
    {0, C5_11,  C6_11,  C7_11}, //D89-15-21
    {0, C1_11,  C2_11,  C3_11}, //D93-16-22
    {0, C5_12,  C6_12,  C7_12}, //D98-17-23
    {0, C1_12,  C2_12,  C3_12}, //D105-18-24
    {0, C4_12,  C6_13,  C7_13}, //D110-19-25
    {0, C1_13,  C2_13,  C3_13}, //D115-1A-26
    {0, C4_13,  C5_13,  C7_14}, //D121-1B-27
    {0, C1_14,  C2_14,  C3_14}, //D127-1C-28
    {0, C4_14,  C5_14,  C6_14}, //D133-2C-29
    {0, C1_8,   C2_8,   C3_8}, //D139-1E-30
    {0, C1_15,  C2_15,  C3_15}, //D51-20-31
    {0, C1_16,  C2_16,  C3_16}, //D63-21-32
    {0, C4_15,  C5_15,  C6_15}, //D74-22-33
    {0, C4_16,  C6_16,  C5_16}, //D79-23-34

    {1, C2_1,   C3_1,   C4_1},  //D84-24-35
    {1, C5_1,   C6_1,   C7_1},  //D90-25-36
    {1, C1_1,   C3_2,   C4_2},  //D94-26-37
    {1, C5_2,   C6_2,   C7_2},  //D99-27-38
    {1, C1_2,   C2_2,   C4_3},  //D106-28-39
    {1, C5_3,   C6_3,   C7_3},  //D111-29-40
    {1, C1_3,   C2_3,   C3_3},  //D116-2A-41
    {1, C5_4,   C6_4,   C7_4},  //D122-2B-42
    {1, C1_4,   C2_4,   C3_4},  //D129-2D-43
    {0, C4_8,   C5_8,   C6_8}, //D140-2E-44
    {1, C1_5,   C2_5,   C3_5},  //D10-30-45
    {1, C4_5,   C5_5,   C7_6},  //D67-31-46
    {1, C1_6,   C2_6,   C3_6},  //D75-32-47
    {1, C4_6,   C5_6,   C6_6},  //D80-33-48
    {1, C1_7,   C2_7,   C3_7},  //D85-34-49
    {1, C4_7,   C5_7,   C6_7},  //D91-35-50
    {1, C1_8,   C2_8,   C3_8},  //D95-36-51
    {1, C4_8,   C5_8,   C6_8},  //D100-37-52 

    {1, C2_9,   C3_9,   C4_9},  //D107-38-53
    {1, C5_9,   C6_9,   C7_9},  //D112-39-54
    {1, C1_9,   C3_10,  C4_10}, //D117-3A-55
    {1, C5_10,  C6_10,  C7_10}, //D123-3B-56
    {1, C1_10,  C2_10,  C4_11}, //D125-3C-57
    {1, C5_11,  C6_11,  C7_11}, //D136-3D-58
    {1, C4_4,   C6_5,   C7_5},  //D158-3E-59
    {1, C1_12,  C2_12,  C3_12}, //D56-40-60
    {1, C4_12,  C6_13,  C7_13}, //D68-41-61
    {1, C1_13,  C2_13,  C3_13}, //D76-42-62
    {1, C1_14,  C2_14,  C3_14}, //D96-46-63
    {1, C1_15,  C2_15,  C3_15}, //D113-4A-64
    {1, C4_15,  C5_15,  C6_15}, //D167-4B-65
    {1, C4_16,  C5_16,  C6_16}, //D128-4C-66
    {1, C1_11,  C2_11,  C3_11}, //D134-4D-67
    {1, C5_12,  C6_12,  C7_12}, //D159-4E-68
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {0,           1,          2,          3,          4,           5,         6,          7,          8,          9,          10,        11,          12,           13,       15},
  {16,         17,         18,         19,         20,          21,        22,         23,         24,         25,          26,        27,          28,           14,       30},
  {31,         32,         33,         34,         35,          36,        37,         38,         39,         40,          41,        42,          29,           43,       44},
  {45,         46,         47,         48,         49,          50,        51,         52,         53,         54,          55,        56,          57,           58,       59},
  {60,         61,         62,         NO_LED,     NO_LED,      NO_LED,    63,         NO_LED,     NO_LED,     NO_LED,      64,        65,          66,           67,       68},
    },
    {
  //LED Index to Physical Positon

  {  0,  0},  { 16,  0},  { 32, 0 },  { 48, 0 },  { 64, 0},   { 80, 0},   { 96, 0},   { 112, 0},  { 128, 0},  { 144, 0},  { 160, 0},  { 176, 0},    {192,  0},   {208,  0},   {208, 16},   {224, 0},
  {  0, 16},  { 16, 16},  { 32,16 },  { 48,16 },  { 64,16},   { 80,16},   { 96,16},   { 112,16},  { 128,16},  { 144,16},  { 160,16},  { 176,16},    {192, 16},   {192, 32},   {224,16},
  {  0, 32},  { 16, 32},  { 32,32 },  { 48,32 },  { 64,32},   { 80,32},   { 96,32},   { 112,32},  { 128,32},  { 144,32},  { 160,32},  { 176,32},    {208, 32},   {224,32},
  {  0, 48},  { 16, 48},  { 32,48 },  { 48,48 },  { 64,48},   { 80,48},   { 96,48},   { 112,48},  { 128,48},  { 144,48},  { 160,48},  { 176,48},    {192, 48},   {208, 48},   {224,48},
  {  0, 64},  { 16, 64},  { 32,64 },                                      { 96,64},                                       { 160,64},  { 176,64},    {192, 64},   {208, 64},   {224,64},
}, {
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,                                              1,                                              1,          1,            1,           1,           1,          
} };

__attribute__((weak)) void rgb_matrix_indicators_user(void) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(31, 255, 255, 255);
        }
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGB_MATRIX_DISABLE_KEYCODES
        case KC_F13: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case KC_F14:
            rgb_matrix_step();
            return false;
        case KC_F15:
            rgb_matrix_increase_speed();
            return false;
        case KC_F16:
            rgb_matrix_decrease_speed();
            return false;
        case KC_F17:
            rgb_matrix_increase_hue();
            return false;
        case KC_F18:
            rgb_matrix_decrease_hue();
            return false;
        case KC_F19:
            rgb_matrix_increase_sat();
            return false;
        case KC_F20:
            rgb_matrix_decrease_sat();
            return false;
        case KC_F21:
            rgb_matrix_increase_val();
            return false;
        case KC_F22:
            rgb_matrix_decrease_val();
            return false;
    #endif
        default:
        break;
    }
  }
  return true;
}
