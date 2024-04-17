/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

 void keyboard_post_init_user(void) {
     // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

     if (is_keyboard_left()) {
         dprintln("I'm left!");
     } else {
         dprintln("I'm right!");
     }
 }

/**
 * LEDs index.
 *
 * ╭────────────────────╮                 ╭────────────────────╮
 *    2   3   8   9  12                     30  27  26  21  20
 * ├────────────────────┤                 ├────────────────────┤
 *    1   4   7  10  13                     31  28  25  22  19
 * ├────────────────────┤                 ├────────────────────┤
 *    0   5   6  11  14                     32  29  24  23  18
 * ╰────────────────────╯                 ╰────────────────────╯
 *                   15  16  17     35  34  33
 *                 ╰────────────╯ ╰────────────╯
 */
// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {      2,      3,      8,      9,     12 }, // Top row
    {      1,      4,      7,     10,     13 }, // Middle row
    {      0,      5,      6,     11,     14 }, // Bottom row
    {     17, NO_LED,     15,     16, NO_LED }, // Thumb cluster
    // Right split.
    {     20,     21,     26,     27,     30 }, // Top row
    {     19,     22,     25,     28,     31 }, // Middle row
    {     18,     23,     24,     29,     32 }, // Bottom row
    {     35, NO_LED,     33,     34, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,  42 }, {   0,  21 }, {   0,   0 }, // col 1 (left most)
    /* index=3  */ {  18,   0 }, {  18,  21 }, {  18,  42 }, // col 2
    /* index=6  */ {  36,  42 }, {  36,  21 }, {  36,   0 },
    /* index=9  */ {  54,   0 }, {  54,  21 }, {  54,  42 },
    /* index=12 */ {  72,   0 }, {  72,  21 }, {  72,  42 },
    /* index=15 */ {  72,  64 }, {  90,  64 }, { 108,  64 }, // Thumb cluster
    // Right split.
    /* index=18 */ { 224,  42 }, { 224,  21 }, { 224,   0 }, // col 10 (right most)
    /* index=21 */ { 206,   0 }, { 206,  21 }, { 206,  42 }, // col 9
    /* index=24 */ { 188,  42 }, { 188,  21 }, { 188,   0 },
    /* index=27 */ { 170,   0 }, { 170,  21 }, { 170,  42 },
    /* index=30 */ { 152,   0 }, { 152,  21 }, { 152,  42 },
    /* index=33 */ { 152,  64 }, { 134,  64 }, { 116,  64 }, // Thumb cluster
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=3  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=6  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=9  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=15 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
    // Right split.
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=33 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
} };
#endif
// clang-format on
