/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "4x6.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
/**
 * \brief LEDs index.
 *
 * ╭────────────────────────╮                 ╭────────────────────────╮
 *    0   7   8  15  16  20                     49  45  44  37  36  29
 * ├────────────────────────┤                 ├────────────────────────┤
 *    1   6   9  14  17  21                     50  46  43  38  35  30
 * ├────────────────────────┤                 ├────────────────────────┤
 *    2   5  10  13  18  22                     51  47  42  39  34  31
 * ├────────────────────────┤                 ├────────────────────────┤
 *    3   4  11  12  19  23                     52  48  41  40  33  32
 * ╰────────────────────────╯                 ╰────────────────────────╯
 *                       26  27  28     53  54  XX
 *                           25  24     55  XX
 *                     ╰────────────╯ ╰────────────╯
 */
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {      0,      7,      8,     15,     16,     20 }, // Num row
    {      1,      6,      9,     14,     17,     21 }, // Top row
    {      2,      5,     10,     13,     18,     22 }, // Middle row
    {      3,      4,     11,     12,     19,     23 }, // Bottom row
    { NO_LED,     28,     24,     26,     27,     25 }, // Thumb cluster
    // Right split.
    {     29,     36,     37,     44,     45,     49 }, // Num row
    {     30,     35,     38,     43,     46,     50 }, // Top row
    {     31,     34,     39,     42,     47,     51 }, // Middle row
    {     32,     33,     40,     41,     48,     52 }, // Bottom row
    { NO_LED,     53,     55,     54, NO_LED, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,   0 }, {   0,  12 }, {   0,  24 }, {   0,  36 }, // col 1 (left most)
    /* index=4  */ {  16,  36 }, {  16,  24 }, {  16,  12 }, {  16,   0 }, // col 2
    /* index=8  */ {  32,   0 }, {  32,  12 }, {  32,  24 }, {  32,  36 },
    /* index=12 */ {  48,  36 }, {  48,  24 }, {  48,  12 }, {  48,   0 },
    /* index=16 */ {  64,   0 }, {  64,  12 }, {  64,  24 }, {  64,  36 },
    /* index=20 */ {  80,   0 }, {  80,  12 }, {  80,  24 }, {  80,  36 },
    /* index=24 */ { 112,  64 }, {  96,  64 }, {  80,  52 },
    /* index=27 */ {  96,  52 }, { 112,  52 },
    // Right split.
    /* index=29 */ { 224,   0 }, { 224,  12 }, { 224,  24 }, { 224,  36 }, // col 12 (right most)
    /* index=33 */ { 208,  36 }, { 208,  24 }, { 208,  12 }, { 208,   0 }, // col 11
    /* index=37 */ { 192,   0 }, { 192,  12 }, { 192,  24 }, { 192,  36 },
    /* index=41 */ { 176,  36 }, { 176,  24 }, { 176,  12 }, { 176,   0 },
    /* index=45 */ { 160,   0 }, { 160,  12 }, { 160,  24 }, { 160,  36 },
    /* index=49 */ { 144,   0 }, { 144,  12 }, { 144,  24 }, { 144,  36 },
    /* index=53 */ { 112,  52 }, { 128,  64 }, { 112,  64 },
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=4  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=8  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=16 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=20 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=24 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster top
    /* index=27 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER,                    // Thumb cluster bottom
    // Right split.
    /* index=29 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 12
    /* index=33 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 11
    /* index=37 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=41 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=45 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=49 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=53 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // Thumb cluster
} };
#endif
// clang-format on
