/* Copyright 2020 Team Mechlovin'
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

#include "rgb_led.h"


#ifdef RGB_MATRIX_ENABLE
const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
// left CA
    {0, C5_2,   C6_2,   C7_2}, //D2-0
    {0, C1_1,   C3_2,   C4_2}, //D20-1
    {0, C5_1,   C6_1,   C7_1}, //D36-2
    {0, C2_1,   C3_1,   C4_1}, //D46-3
    {0, C5_4,   C6_4,   C7_4}, //D65-4
    {0, C1_3,   C2_3,   C3_3}, //D26-5
    {0, C5_3,   C6_3,   C7_3}, //D37-6
    {0, C1_2,   C2_2,   C4_3}, //D47-7
    {0, C4_5,   C5_5,   C7_6}, //D11-8
    {0, C1_5,   C2_5,   C3_5}, //D27-9
    {0, C4_4,   C6_5,   C7_5}, //D38-10
    {0, C1_4,   C2_4,   C3_4}, //D48-11

// left CB
    {0, C2_9,   C3_9,   C4_9},  //D17-12
    {0, C5_9,   C6_9,   C7_9},  //D28-13
    {0, C1_9,   C3_10,  C4_10}, //D39-14
    {0, C5_10,  C6_10,  C7_10}, //D49-15
    {0, C1_10,  C2_10,  C4_11}, //D18-16
    {0, C5_11,  C6_11,  C7_11}, //D29-17
    {0, C1_11,  C2_11,  C3_11}, //D40-18
    {0, C5_12,  C6_12,  C7_12}, //D50-19
    {0, C1_12,  C2_12,  C3_12}, //D19-20
    {0, C1_13,  C2_13,  C3_13}, //D61-21
    {0, C4_13,  C5_13,  C7_14}, //D35-22
    {0, C1_14,  C2_14,  C3_14}, //D41-23
    {0, C4_14,  C5_14,  C6_14}, //D51-24
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {0,           1,         2,           3},
  {4,           5,         6,           7},
  {8,           9,        10,          11},
  {12,         13,        14,          15},
  {16,         17,        18,          19},
  {20,         22,        23,          24}
    },
    {
  //LED Index to Physical Positon
  {  0,  0},  { 75,  0},  {149,  0},  {224,  0},     
  {  0, 13},  { 75, 13},  {149, 13},  {224, 13},     
  {  0, 25},  { 75, 25},  {149, 25},  {224, 25},     
  {  0, 38},  { 75, 38},  {149, 38},  {224, 38},     
  {  0, 51},  { 75, 51},  {149, 51},  {224, 51},     
  {  0, 64},  { 37, 64},  { 75, 64},  {149, 64},  {224, 64},               
}, {
  4,          4,          4,          4,
  4,          1,          1,          4,
  4,          1,          1,          4,
  4,          1,          1,          4,
  4,          1,          1,          4,
  4,          0,          1,          1,          4,
} };

void rgb_matrix_indicators_kb(void) {
        if (host_keyboard_led_state().num_lock) {
            rgb_matrix_set_color(4, 255, 255, 255);
        }
}

__attribute__((weak))
layer_state_t layer_state_set_user(layer_state_t state) {
  // if on layer 1, turn on L1 LED, otherwise off.
    if (get_highest_layer(state) == 0) {
        rgb_matrix_set_color(1, 255, 0, 0);
    } else {
        rgb_matrix_set_color(1, 0, 0, 0);
    }
  // if on layer 2, turn on L2 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        rgb_matrix_set_color(0, 255, 0, 0);
    } else {
        rgb_matrix_set_color(0, 0, 0, 0);
    }

  // if on layer 3, turn on L3 LED, otherwise off.
    if (get_highest_layer(state) == 2) {
        rgb_matrix_set_color(3, 255, 0, 0);
    } else {
        rgb_matrix_set_color(3, 0, 0, 0);
    }

  // if on layer 4, turn on L4 LED, otherwise off.
    if (get_highest_layer(state) == 3) {
        rgb_matrix_set_color(2, 255, 0, 0);
    } else {
        rgb_matrix_set_color(2, 0, 0, 0);
    }

    return state;
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    
  if (record->event.pressed) {
    switch(keycode) {
        #ifdef RGB_MATRIX_ENABLE
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
