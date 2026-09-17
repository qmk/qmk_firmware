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
