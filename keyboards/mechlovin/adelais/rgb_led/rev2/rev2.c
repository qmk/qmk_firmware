/* Copyright 2020 Team Mechlovin
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {

    {0, C2_1,   C3_1,   C4_1}, //D102-A0-0
    {0, C5_1,   C6_1,   C7_1}, //D108-A1-1
    {0, C1_1,   C3_2,   C4_2}, //D115-A2-2
    {0, C5_2,   C6_2,   C7_2}, //D121-A3-3
    {0, C1_2,   C2_2,   C4_3}, //D126-A4-4
    {0, C5_3,   C6_3,   C7_3}, //D132-A5-5
    {0, C1_3,   C2_3,   C3_3}, //D138-A6-6
    {0, C5_4,   C6_4,   C7_4}, //D144-A7-7
    {0, C1_4,   C2_4,   C3_4}, //D149-A8-8
    {0, C4_4,   C6_5,   C7_5}, //D155-A9-9
    {0, C1_5,   C2_5,   C3_5}, //D160-A10-10
    {0, C4_5,   C5_5,   C7_6}, //D166-A11-11
    {0, C1_6,   C2_6,   C3_6}, //D173-A12-12
    {0, C4_6,   C5_6,   C6_6}, //D178-A13-13
    {0, C1_7,   C2_7,   C3_7}, //D183-A14-14
    {0, C4_7,   C5_7,   C6_7}, //D187-A15-15
    {0, C1_8,   C2_8,   C3_8}, //D190-A16-16


    {0, C2_9,   C3_9,   C4_9},  //D80-B0-17
    {0, C5_9,   C6_9,   C7_9},  //D84-B1-18
    {0, C1_9,   C3_10,  C4_10}, //D89-B2-19
    {0, C5_10,  C6_10,  C7_10}, //D94-B3-20
    {0, C1_10,  C2_10,  C4_11}, //D81-B4-21
    {0, C5_11,  C6_11,  C7_11}, //D85-B5-22
    {0, C1_11,  C2_11,  C3_11}, //D90-B6-23
    {0, C5_12,  C6_12,  C7_12}, //D95-B7-24
    {0, C1_12,  C2_12,  C3_12}, //D82-B8-25
    {0, C4_12,  C6_13,  C7_13}, //D86-B9-26
    {0, C1_13,  C2_13,  C3_13}, //D91-B10-27
    {0, C4_13,  C5_13,  C7_14}, //D96-B11-28
    {0, C1_14,  C2_14,  C3_14}, //D79-B12-29
    {0, C4_14,  C5_14,  C6_14}, //D83-B13-30
    {0, C1_15,  C2_15,  C3_15}, //D87-B14-31


    {1, C2_1,   C3_1,   C4_1}, //D102-C0-32
    {1, C5_1,   C6_1,   C7_1}, //D108-C1-33
    {1, C1_1,   C3_2,   C4_2}, //D115-C2-34
    {1, C5_2,   C6_2,   C7_2}, //D121-C3-35
    {1, C1_2,   C2_2,   C4_3}, //D126-C4-36
    {1, C5_3,   C6_3,   C7_3}, //D132-C5-37
    {1, C1_3,   C2_3,   C3_3}, //D138-C6-38
    {1, C5_4,   C6_4,   C7_4}, //D144-C7-39
    {1, C1_4,   C2_4,   C3_4}, //D149-C8-40
    {1, C4_4,   C6_5,   C7_5}, //D155-C9-41
    {1, C1_5,   C2_5,   C3_5}, //D160-C10-42
    {1, C4_5,   C5_5,   C7_6}, //D166-C11-43
    {1, C1_6,   C2_6,   C3_6}, //D173-C12-44
    {1, C4_6,   C5_6,   C6_6}, //D178-C13-45

    {1, C2_9,   C3_9,   C4_9},  //D80-D0-46
    {1, C1_9,   C3_10,  C4_10}, //D89-D2-47
    {1, C5_10,  C6_10,  C7_10}, //D94-D3-48
    {1, C5_11,  C6_11,  C7_11}, //D85-D5-49
    {1, C1_11,  C2_11,  C3_11}, //D90-D6-50
    {1, C1_12,  C2_12,  C3_12}, //D82-D8-51
    {1, C1_13,  C2_13,  C3_13}, //D91-D10-52
    {1, C4_13,  C5_13,  C7_14}, //D96-D11-53
    {1, C1_15,  C2_15,  C3_15}, //D87-D14-54
    {1, C4_15,  C5_15,  C6_15}, //D87-D14-55
    {1, C1_16,  C2_16,  C3_16}, //D87-D14-56
    {1, C4_16,  C5_16,  C6_16}, //D87-D14-57
    {1, C1_8,   C2_8,   C3_8},  //D84-D1-58
    {1, C4_8,   C5_8,   C6_8},  //D84-D1-59
    {1, C1_7,   C2_7,   C3_7},  //D84-D1-60
    {1, C1_10,  C2_10,  C4_11}, //D81-D4-61
    {1, C5_9,   C6_9,   C7_9},  //D95-D7-62
    {1, C5_12,  C6_12,  C7_12}, //D95-D7-63
    {1, C4_12,  C6_13,  C7_13}, //D86-D9-64
    {1, C1_14,  C2_14,  C3_14}, //D79-D12-65
    {1, C4_14,  C5_14,  C6_14}, //D83-D13-66
    {1, C4_7,   C5_7,   C6_7},  //D83-D13-67
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 1,           2,         3,          4,           5,           6,         7,          8,          9,          10,        11,           12,           13,          14,         16},
  {18,          19,        20,         21,          22,          23,        24,         25,         26,          27,        28,           29,           30,          31,          0},
  {33,          34,        35,         36,          37,          38,        39,         40,         41,          42,        43,           44,       NO_LED,          45,         17},
  {46,        NO_LED,      47,         48,          49,          50,        51,         52,         53,          54,        55,           56,           59,          60,         32},
  {61,        NO_LED,      62,     NO_LED,          63,      NO_LED,        64,     NO_LED,         65,      NO_LED,        66,       NO_LED,       NO_LED,          57,         67}
    },
    {
  //LED Index to Physical Positon
  {0,0},      { 17,  0},  { 34, 0 },  { 51, 0 },  { 69, 0},   { 86, 0},   {100, 0},   {103, 0},   { 120, 0},  { 138, 0},  { 155, 0},  { 172, 0},  { 189, 0},    {207,  0},   {215,  0},   {223, 0},   {224, 0},
  {0,16},     { 17, 16},  { 34,16 },  { 51,16 },  { 69,16},   { 86,16},   {103,16},               { 120,16},  { 138,16},  { 155,16},  { 172,16},  { 189,16},    {207, 16},   {215, 16},   {224,16},
  {0,32},     { 17, 32},  { 34,32 },  { 51,32 },  { 69,32},   { 86,32},   {103,32},   { 120,32},  { 138,32},  { 155,32},  { 172,32},  { 189,32},  {207, 32},    {224,32},
              { 17, 48},  { 34,48 },  { 51,48 },  { 69,48},   { 86,48},   {103,48},   { 120,48},  { 138,48},  { 155,48},  { 172,48},  { 189,48},  {207, 48},    {215, 48},   {224,48},    {224,48},
              { 17, 64},              { 51,64 },              { 86,64},   { 103,64},              { 138,64},              { 172,64},              {224, 64},
}, {
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,                         1,           1,
  1,                      1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,                      1,                      1,                      1,                      1,                      1,          1,            1,           1,           1,
} };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(33, 255, 255, 255);
    }
    return true;
}


#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

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
    #endif
        default:
        break;
    }
  }
  return true;
}
