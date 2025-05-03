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

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB9_CA1,    CB7_CA1,    CB8_CA1},  // ESC
    {0, CB9_CA2,    CB7_CA2,    CB8_CA2},  // F1
    {0, CB9_CA3,    CB7_CA3,    CB8_CA3},  // F2
    {0, CB9_CA4,    CB7_CA4,    CB8_CA4},  // F3
    {0, CB9_CA5,    CB7_CA5,    CB8_CA5},  // F4
    {0, CB9_CA6,    CB7_CA6,    CB8_CA6},  // F5
    {0, CB9_CA7,    CB7_CA7,    CB8_CA7},  // F6
    {0, CB9_CA8,    CB7_CA8,    CB8_CA8},  // F7
    {0, CB9_CA9,    CB7_CA9,    CB8_CA9},  // F8
    {0, CB9_CA10,   CB7_CA10,   CB8_CA10}, // F9
    {0, CB9_CA11,   CB7_CA11,   CB8_CA11}, // F10
    {0, CB9_CA12,   CB7_CA12,   CB8_CA12}, // F11
    {0, CB9_CA13,   CB7_CA13,   CB8_CA13}, // F12
    {0, CB9_CA14,   CB7_CA14,   CB8_CA14}, // Mute
    {0, CB9_CA15,   CB7_CA15,   CB8_CA15}, // Print
    {0, CB9_CA16,   CB7_CA16,   CB8_CA16}, // Cortana
    {1, CB9_CA15,   CB7_CA15,   CB8_CA15}, // Light

    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},  // `~
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},  // 1!
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},  // 2@
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},  // 3#
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},  // 4$
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},  // 5%
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},  // 6^
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},  // 7&
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},  // 8*
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10}, // 9()
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11}, // 0)
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12}, // -_
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13}, // =+
    {0, CB3_CA14,   CB1_CA14,   CB2_CA14}, // |
    {1, CB6_CA6,    CB4_CA6,    CB5_CA6},  // Backspace
    {0, CB3_CA15,   CB1_CA15,   CB2_CA15}, // Ins
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16}, // Home
    {1, CB9_CA16,   CB7_CA16,   CB8_CA16}, // Page Up

    {0, CB6_CA1,    CB4_CA1,    CB5_CA1},  // tab
    {0, CB6_CA2,    CB4_CA2,    CB5_CA2},  // Q
    {0, CB6_CA3,    CB4_CA3,    CB5_CA3},  // W
    {0, CB6_CA4,    CB4_CA4,    CB5_CA4},  // E
    {0, CB6_CA5,    CB4_CA5,    CB5_CA5},  // R
    {0, CB6_CA6,    CB4_CA6,    CB5_CA6},  // T
    {0, CB6_CA7,    CB4_CA7,    CB5_CA7},  // Y
    {0, CB6_CA8,    CB4_CA8,    CB5_CA8},  // U
    {0, CB6_CA9,    CB4_CA9,    CB5_CA9},  // I
    {0, CB6_CA10,   CB4_CA10,   CB5_CA10}, // O
    {0, CB6_CA11,   CB4_CA11,   CB5_CA11}, // P
    {0, CB6_CA12,   CB4_CA12,   CB5_CA12}, // [{
    {0, CB6_CA13,   CB4_CA13,   CB5_CA13}, // }}
    {0, CB6_CA15,   CB4_CA15,   CB5_CA15}, // Del
    {0, CB6_CA16,   CB4_CA16,   CB5_CA16}, // End
    {1, CB9_CA13,   CB7_CA13,   CB8_CA13}, // Page Down

    {1, CB9_CA1,    CB7_CA1,    CB8_CA1},  // Cpas
    {1, CB9_CA2,    CB7_CA2,    CB8_CA2},  // A
    {1, CB9_CA3,    CB7_CA3,    CB8_CA3},  // S
    {1, CB9_CA4,    CB7_CA4,    CB8_CA4},  // D
    {1, CB9_CA5,    CB7_CA5,    CB8_CA5},  // F
    {1, CB9_CA6,    CB7_CA6,    CB8_CA6},  // G
    {1, CB9_CA7,    CB7_CA7,    CB8_CA7},  // H
    {1, CB9_CA8,    CB7_CA8,    CB8_CA8},  // J
    {1, CB9_CA9,    CB7_CA9,    CB8_CA9},  // K
    {1, CB9_CA10,   CB7_CA10,   CB8_CA10}, // L
    {1, CB9_CA11,   CB7_CA11,   CB8_CA11}, // ;
    {1, CB9_CA12,   CB7_CA12,   CB8_CA12}, // :
    {1, CB9_CA14,   CB7_CA14,   CB8_CA14}, // #~
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14}, // Enter

    {1, CB3_CA1,    CB1_CA1,    CB2_CA1},  // LShift
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},  // Z
    {1, CB3_CA4,    CB1_CA4,    CB2_CA4},  // X
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},  // C
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},  // V
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},  // B
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},  // N
    {1, CB3_CA9,    CB1_CA9,    CB2_CA9},  // M
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10}, // ,<
    {1, CB3_CA11,   CB1_CA11,   CB2_CA11}, // .>
    {1, CB3_CA12,   CB1_CA12,   CB2_CA12}, // /?
    {1, CB3_CA13,   CB1_CA13,   CB2_CA13}, // |
    {1, CB3_CA14,   CB1_CA14,   CB2_CA14}, // RShift
    {1, CB3_CA16,   CB1_CA16,   CB2_CA16}, // Up

    {1, CB6_CA1,    CB4_CA1,    CB5_CA1},  // LCtrl
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2},  // LWin
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},  // LAlt
    {1, CB6_CA4,    CB4_CA4,    CB5_CA4},  // NUm
    {1, CB6_CA7,    CB4_CA7,    CB5_CA7},  // Space
    {1, CB6_CA10,   CB4_CA10,   CB5_CA10}, // Jap
    {1, CB6_CA11,   CB4_CA11,   CB5_CA11}, // RAlt
    {1, CB6_CA12,   CB4_CA12,   CB5_CA12}, // RWin
    {1, CB6_CA13,   CB4_CA13,   CB5_CA13}, // Fn
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14}, // RCtrl
    {1, CB6_CA15,   CB4_CA15,   CB5_CA15}, // Left
    {1, CB6_CA16,   CB4_CA16,   CB5_CA16}, // Down
    {1, CB3_CA15,   CB1_CA15,   CB2_CA15}, // Right
};

#endif // RGB_MATRIX_ENABLE
