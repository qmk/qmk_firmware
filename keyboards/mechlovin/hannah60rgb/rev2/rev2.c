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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
// left CA
    {0, C1_1,   C3_2,   C4_2}, //D9-0-0
    {0, C5_2,   C6_2,   C7_2}, //D59-1-1
    {0, C2_1,   C3_1,   C4_1}, //D68-2-2
    {0, C5_1,   C6_1,   C7_1}, //D76-3-3
    {0, C1_2,   C2_2,   C4_3}, //D10-15-4
    {0, C5_3,   C6_3,   C7_3}, //D60-16-5
    {0, C1_3,   C2_3,   C3_3}, //D72-17-6
    {0, C5_4,   C6_4,   C7_4}, //D77-18-7
    {0, C1_4,   C2_4,   C3_4}, //D46-30-8
    {0, C4_4,   C6_5,   C7_5}, //D61-31-9
    {0, C1_5,   C2_5,   C3_5}, //D73-32-10
    {0, C4_5,   C5_5,   C7_6}, //D78-33-11
    {0, C1_6,   C2_6,   C3_6}, //D126-44-12
    {0, C4_6,   C5_6,   C6_6}, //D51-45-13
    {0, C1_7,   C2_7,   C3_7}, //D63-46-14
    {0, C4_7,   C5_7,   C6_7}, //D74-47-15
    {0, C1_8,   C2_8,   C3_8}, //D56-60-16
    {0, C4_8,   C5_8,   C6_8}, //D67-61-17

// left CB
    {0, C2_9,   C3_9,   C4_9},  //D80-4-18
    {0, C5_9,   C6_9,   C7_9},  //D84-5-19
    {0, C1_9,   C3_10,  C4_10}, //D89-6-20
    {0, C5_10,  C6_10,  C7_10}, //D94-7-21
    {0, C1_10,  C2_10,  C4_11}, //D81-19-22
    {0, C5_11,  C6_11,  C7_11}, //D85-20-23
    {0, C1_11,  C2_11,  C3_11}, //D90-21-24
    {0, C5_12,  C6_12,  C7_12}, //D95-22-25
    {0, C1_12,  C2_12,  C3_12}, //D82-34-26
    {0, C4_12,  C6_13,  C7_13}, //D86-35-27
    {0, C1_13,  C2_13,  C3_13}, //D91-36-28
    {0, C4_13,  C5_13,  C7_14}, //D96-37-29
    {0, C1_14,  C2_14,  C3_14}, //D79-48-30
    {0, C4_14,  C5_14,  C6_14}, //D83-49-31
    {0, C1_15,  C2_15,  C3_15}, //D87-50-32
    {0, C4_15,  C5_15,  C6_15}, //D92-51-33
    {0, C1_16,  C2_16,  C3_16}, //D75-62-34
    {0, C4_16,  C5_16,  C6_16}, //D93-63-35

// right CA
    {1, C2_1,   C3_1,   C4_1},  //D98-8-36
    {1, C5_1,   C6_1,   C7_1},  //D102-9-37
    {1, C1_1,   C3_2,   C4_2},  //D106-10-38
    {1, C5_2,   C6_2,   C7_2},  //D111-11-39
    {1, C2_9,   C3_9,   C4_9},  //D116-12-40
    {1, C5_9,   C6_9,   C7_9},  //D130-13-41
    {1, C1_13,  C2_13,  C3_13}, //D121-14-42
    {1, C1_2,   C2_2,   C4_3},  //D99-23-43
    {1, C5_3,   C6_3,   C7_3},  //D103-24-44
    {1, C1_3,   C2_3,   C3_3},  //D107-25-45
    {1, C5_4,   C6_4,   C7_4},  //D112-26-46
    {1, C1_9,   C3_10,  C4_10}, //D117-27-47
    {1, C5_10,  C6_10,  C7_10}, //D129-28-48
    {1, C4_13,  C5_13,  C7_14}, //D122-29-49
    {1, C1_4,   C2_4,   C3_4},  //D100-38-50
    {1, C4_4,   C6_5,   C7_5},  //D104-39-51
    {1, C1_5,   C2_5,   C3_5},  //D108-40-52
    {1, C4_5,   C5_5,   C7_6},  //D113-41-53
// right CB
    {1, C1_10,  C2_10,  C4_11}, //D118-42-54
    {1, C5_11,  C6_11,  C7_11}, //D123-43-55
    {1, C1_6,   C2_6,   C3_6},  //D97-52-56
    {1, C4_6,   C5_6,   C6_6},  //D101-53-57
    {1, C1_7,   C2_7,   C3_7},  //D105-54-58
    {1, C4_7,   C5_7,   C6_7},  //D109-55-59
    {1, C1_11,  C2_11,  C3_11}, //D114-56-60
    {1, C5_12,  C6_12,  C7_12}, //D128-57-61
    {1, C1_14,  C2_14,  C3_14}, //D119-58-62
    {1, C4_14,  C5_14,  C6_14}, //D124-59-63
    {1, C1_8,   C2_8,   C3_8}, //D127-64-64
    {1, C4_8,   C5_8,   C6_8}, //D110-65-65
    {1, C1_12,  C2_12,  C3_12}, //D115-66-66
    {1, C4_12,  C6_13,  C7_13}, //D120-67-67
    {1, C1_15,  C2_15,  C3_15}, //D125-68-68
    {1, C4_15,  C5_15,  C6_15}, //D140-69-69
    {0, C8_7,   C7_7,   C7_8}, //INDICATOR LED-70
    {0, C8_8,   C8_1,   C8_2}, //INDICATOR LED-71
    {0, C9_7,   C8_6,   C9_6}, //INDICATOR LED-72
    {0, C9_8,   C8_4,   C8_5},//INDICATOR LED-73
    {0, C8_15,  C9_1,   C9_2},//INDICATOR LED-74
    {0, C8_16,  C8_3,   C9_3},//INDICATOR LED-75
    {0, C9_15,  C9_9,   C9_10},//INDICATOR LED-76
    {0, C9_16,  C9_11,  C7_12},//INDICATOR LED-77
};

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,   1,  2,      3,     18,     19, 20,     21,     36,     37, 38, 39, 40, 41 },
        { 4,   5,  6,      7,     22,     23, 24,     25,     43,     44, 45, 46, 47, 69 },
        { 8,   9, 10,     11,     26,     27, 28,     29,     50,     51, 52, 53, 54, 55 },
        { 13, 14, 15,     30,     31,     32, 33,     56,     57,     58, 59, 60, 62, 63 },
        { 16, 17, 34, NO_LED, NO_LED, NO_LED, 35, NO_LED, NO_LED, NO_LED, 65, 66, 67, 68 }
    }, {
        //LED Index to Physical Positon
        {   0,  0 }, {  16,  0 }, {  32,  0 }, { 48,  0 }, //9-59-68-76
        {   0, 16 }, {  16, 16 }, {  32, 16 }, { 48, 16 }, //10-60-72-77
        {   0, 32 }, {  16, 32 }, {  32, 32 }, { 48, 32 }, //46-61-73-78
        {   0, 48 }, {   0, 48 }, {  12, 48 }, { 16, 48 }, //126-51-63-74
        {   0, 64 }, {  16, 64 }, //56-67
        {  64,  0 }, {  80,  0 }, {  96,  0 }, { 112,  0 }, //80-84-89-94
        {  64, 16 }, {  80, 16 }, {  96, 16 }, { 112, 16 }, //81-85-90-95
        {  64, 32 }, {  80, 32 }, {  96, 32 }, { 112, 32 }, //82-86-91-96
        {  32, 48 }, {  48, 48 }, {  64, 48 }, {  80, 48 }, //79-83-87-92
        {  32, 64 }, {  80, 64 }, //75-93
        { 128,  0 }, { 144,  0 }, { 160,  0 }, { 176,  0 }, { 192,  0 }, { 220,  0 }, { 210,  0 }, //98-102-106-111-116-121-130
        { 128, 16 }, { 144, 16 }, { 160, 16 }, { 176, 16 }, { 192, 16 }, { 220, 16 }, { 220, 16 }, //99-103-107-112-117-129-122
        { 128, 32 }, { 144, 32 }, { 160, 32 }, { 176, 32 }, { 192, 32 }, { 220, 32 }, //100-104-108-113-118-123
        {  96, 48 }, { 112, 48 }, { 128, 48 }, { 144, 48 }, { 160, 48 }, { 200, 48 }, { 220, 48 }, { 220, 48 }, //97-101-105-109-114-119-128-124
        {  96, 64 }, { 144, 64 }, { 160, 64 }, { 176, 64 }, { 220, 64 }, //127-110-115-120-125
        { 220,  0 }, //140
        {   0,  0 }, {   0,  0 }, {   0,  0 }, {   0,  0 }, {   0,  0 }, {   0,  0 }, {   0,  0 }, {   0,  0 }
    }, {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1,
        9, 9, 9, 9, 9, 9, 9, 9
    }
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(8, 255, 255, 255);
        rgb_matrix_set_color(70, 255, 0, 0);
    } else {
        rgb_matrix_set_color(70, 0, 0, 0);
    }
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(71, 255, 0, 0);
    } else {
        rgb_matrix_set_color(71, 0, 0, 0);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(72, 255, 0, 0);
    } else {
        rgb_matrix_set_color(72, 0, 0, 0);
    }
    return true;
}

__attribute__((weak))
layer_state_t layer_state_set_user(layer_state_t state) {
  // if on layer 1, turn on L1 LED, otherwise off.
    if (get_highest_layer(state) == 0) {
        rgb_matrix_set_color(73, 255, 0, 0);
    } else {
        rgb_matrix_set_color(73, 0, 0, 0);
    }
  // if on layer 2, turn on L2 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        rgb_matrix_set_color(74, 255, 0, 0);
    } else {
        rgb_matrix_set_color(74, 0, 0, 0);
    }

  // if on layer 3, turn on L3 LED, otherwise off.
    if (get_highest_layer(state) == 2) {
        rgb_matrix_set_color(75, 255, 0, 0);
    } else {
        rgb_matrix_set_color(75, 0, 0, 0);
    }

  // if on layer 4, turn on L4 LED, otherwise off.
    if (get_highest_layer(state) == 3) {
        rgb_matrix_set_color(76, 255, 0, 0);
    } else {
        rgb_matrix_set_color(76, 0, 0, 0);
    }

  // if on layer 5, turn on L5 LED, otherwise off.
    if (get_highest_layer(state) == 4) {
        rgb_matrix_set_color(77, 255, 0, 0);
    } else {
        rgb_matrix_set_color(77, 0, 0, 0);
    }

    return state;
}

#endif
