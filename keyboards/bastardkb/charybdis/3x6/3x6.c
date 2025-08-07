/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include "charybdis.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
/**
 * \brief LEDs index.
 *
 #  0,0  14  28  42  56  70  84  98    126 140 154 168 182 196 210 224,0
 #  0,0  15  30  45  60  75  90 105    119 134 149 164 179 194 209 224,0
 * ╭────────────────────────╮                 ╭────────────────────────╮
 *    0   5   6  11  12  15                     36  33  32  27  26  21
 * ├────────────────────────┤                 ├────────────────────────┤
 *    1   4   7  10  13  16                     37  34  31  28  25  22
 * ├────────────────────────┤                 ├────────────────────────┤
 *    2   3   8   9  14  17                     38  35  30  29  24  23
 * ╰────────────────────────╯                 ╰────────────────────────╯
 *                       18  19  20     39  40  XX
 *                     ╰────────────╯ ╰────────────╯
 *
 * Note: the LED config simulates 42 LEDs instead of the actual 41 to prevent
 * confusion when testing LEDs during assembly when handedness is not set
 * correctly.  Those fake LEDs are bound to the physical top-left corner.
 */
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {      0,      5,      6,     11,     12,     15 }, // Top row
    {      1,      4,      7,     10,     13,     16 }, // Middle row
    {      2,      3,      8,      9,     14,     17 }, // Bottom row
    { NO_LED,     20, NO_LED,     18,     19, NO_LED }, // Thumb cluster
    // Right split.
    {     21,     26,     27,     32,     33,     36 }, // Top row
    {     22,     25,     28,     31,     34,     37 }, // Middle row
    {     23,     24,     29,     30,     35,     38 }, // Bottom row
    { NO_LED,     41, NO_LED,     39,     40, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,   0 }, {   0,  21 }, {   0,  42 }, // col 1 (left most)
    /* index=3  */ {  15,  42 }, {  15,  21 }, {  15,   0 }, // col 2
    /* index=6  */ {  30,   0 }, {  30,  21 }, {  30,  42 },
    /* index=9  */ {  45,  42 }, {  45,  21 }, {  45,   0 },
    /* index=12 */ {  60,   0 }, {  60,  21 }, {  60,  42 },
    /* index=15 */ {  75,   0 }, {  75,  21 }, {  75,  42 },
    /* index=18 */ {  75,  64 }, {  90,  64 }, { 105,  64 }, // Thumb cluster
    // Right split.
    /* index=21 */ { 224,   0 }, { 224,  21 }, { 224,  42 }, // col 12 (right most)
    /* index=24 */ { 209,  42 }, { 209,  21 }, { 209,   0 }, // col 10
    /* index=27 */ { 194,   0 }, { 194,  21 }, { 194,  42 },
    /* index=30 */ { 179,  42 }, { 179,  21 }, { 179,   0 },
    /* index=33 */ { 164,   0 }, { 164,  21 }, { 164,  42 },
    /* index=36 */ { 149,   0 }, { 149,  21 }, { 149,  42 },
    /* index=39 */ { 119,  64 }, { 134,  64 }, {   0,   0 }, // Thumb cluster
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=3  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=6  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=9  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=15 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // Thumb cluster
    // Right split.
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=33 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=36 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=39 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // Thumb cluster
} };
#endif
// clang-format on
