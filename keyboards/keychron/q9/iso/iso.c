/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

// clang-format off

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB12_CA16, CB10_CA16, CB11_CA16}, // Tab
    {0, CB12_CA15, CB10_CA15, CB11_CA15}, // Q
    {0, CB12_CA14, CB10_CA14, CB11_CA14}, // W
    {0, CB12_CA13, CB10_CA13, CB11_CA13}, // E
    {0, CB12_CA12, CB10_CA12, CB11_CA12}, // R
    {0, CB12_CA11, CB10_CA11, CB11_CA11}, // T
    {0, CB12_CA10, CB10_CA10, CB11_CA10}, // Y
    {0, CB12_CA9,  CB10_CA9,  CB11_CA9},  // U
    {0, CB12_CA8,  CB10_CA8,  CB11_CA8},  // I
    {0, CB12_CA7,  CB10_CA7,  CB11_CA7},  // O
    {0, CB12_CA6,  CB10_CA6,  CB11_CA6},  // P
    {0, CB12_CA5,  CB10_CA5,  CB11_CA5},  // [
    {0, CB12_CA4,  CB10_CA4,  CB11_CA4},  // ]
    {0, CB12_CA2,  CB10_CA2,  CB11_CA2},  // Del

    {0, CB3_CA16, CB1_CA16, CB2_CA16}, // CapsLock
    {0, CB3_CA15, CB1_CA15, CB2_CA15}, // A
    {0, CB3_CA14, CB1_CA14, CB2_CA14}, // S
    {0, CB3_CA13, CB1_CA13, CB2_CA13}, // D
    {0, CB3_CA12, CB1_CA12, CB2_CA12}, // F
    {0, CB3_CA11, CB1_CA11, CB2_CA11}, // G
    {0, CB3_CA10, CB1_CA10, CB2_CA10}, // H
    {0, CB3_CA9,  CB1_CA9,  CB2_CA9},  // J
    {0, CB3_CA8,  CB1_CA8,  CB2_CA8},  // K
    {0, CB3_CA7,  CB1_CA7,  CB2_CA7},  // L
    {0, CB3_CA6,  CB1_CA6,  CB2_CA6},  // ;
    {0, CB3_CA5,  CB1_CA5,  CB2_CA5},  // '
    {0, CB3_CA3,  CB1_CA3,  CB2_CA3},  // #
    {0, CB12_CA3,  CB10_CA3,  CB11_CA3},  // Enter
    {0, CB3_CA2,  CB1_CA2,  CB2_CA2},  // Home

    {0, CB9_CA16, CB7_CA16, CB8_CA16}, // LeftShift
    {0, CB9_CA15, CB7_CA15, CB8_CA15}, // |
    {0, CB9_CA14, CB7_CA14, CB8_CA14}, // Z
    {0, CB9_CA13, CB7_CA13, CB8_CA13}, // X
    {0, CB9_CA12, CB7_CA12, CB8_CA12}, // C
    {0, CB9_CA11, CB7_CA11, CB8_CA11}, // V
    {0, CB9_CA10, CB7_CA10, CB8_CA10}, // B
    {0, CB9_CA9,  CB7_CA9,  CB8_CA9},  // N
    {0, CB9_CA8,  CB7_CA8,  CB8_CA8},  // M
    {0, CB9_CA7,  CB7_CA7,  CB8_CA7},  // ,
    {0, CB9_CA6,  CB7_CA6,  CB8_CA6},  // .
    {0, CB9_CA5,  CB7_CA5,  CB8_CA5},  // ?
    {0, CB9_CA3,  CB7_CA3,  CB8_CA3},  // RightShift
    {0, CB9_CA2,  CB7_CA2,  CB8_CA2},  // Up

    {0, CB6_CA16, CB4_CA16, CB5_CA16}, // LeftCtrl
    {0, CB6_CA15, CB4_CA15, CB5_CA15}, // LeftWin
    {0, CB6_CA14, CB4_CA14, CB5_CA14}, // LeftAlt
    {0, CB6_CA10, CB4_CA10, CB5_CA10}, // Space
    {0, CB6_CA6,  CB4_CA6,  CB5_CA6},  // RightAlt
    {0, CB6_CA5,  CB4_CA5,  CB5_CA5},  // Fn1
    {0, CB6_CA4,  CB4_CA4,  CB5_CA4},  // Fn2
    {0, CB6_CA3,  CB4_CA3,  CB5_CA3},  // Left
    {0, CB6_CA2,  CB4_CA2,  CB5_CA2},  // Down
    {0, CB3_CA4,  CB1_CA4,  CB2_CA4}   // Right
};

#endif // RGB_MATRIX_ENABLE
