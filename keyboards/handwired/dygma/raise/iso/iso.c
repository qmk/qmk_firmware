/* Copyright 2018-2021 James Laird-Wah, Islam Sharabash
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// "led_map" is taken from kaleidoscope
// LHK = Left Hand Keys
// LPH = "Leds per hand", which isn't _actually_ the number of leds, but instead
// is just used for indexing
#define LHK 33
#define LPH 72

const uint8_t led_map[DRIVER_LED_TOTAL] = {
  // left side - 33 keys
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 68, 69,

  // right side - 36 keys
  0 + LPH, 1 + LPH, 2 + LPH, 3 + LPH, 4 + LPH, 5 + LPH, 6 + LPH, 15 + LPH, 8 + LPH, 9 + LPH, 10 + LPH, 11 + LPH, 12 + LPH, 13 + LPH, 14 + LPH, 7 + LPH, 16 + LPH, 17 + LPH, 18 + LPH, 19 + LPH,
  20 + LPH, 21 + LPH, 22 + LPH, 23 + LPH, 24 + LPH, 25 + LPH, 26 + LPH, 27 + LPH, 28 + LPH, 29 + LPH, 30 + LPH, 31 + LPH, 32 + LPH, 33 + LPH, 68 + LPH, 69 + LPH,

  // left under glow - 30 keys
  34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,

  // right underglow - 32 keys
  34 + LPH, 35 + LPH, 36 + LPH, 37 + LPH, 38 + LPH, 39 + LPH, 40 + LPH, 41 + LPH, 42 + LPH, 43 + LPH, 44 + LPH, 45 + LPH, 46 + LPH, 47 + LPH, 48 + LPH, 49 + LPH, 50 + LPH, 51 + LPH,
  52 + LPH, 53 + LPH, 54 + LPH, 55 + LPH, 56 + LPH, 57 + LPH, 58 + LPH, 59 + LPH, 60 + LPH, 61 + LPH, 62 + LPH, 63 + LPH, 64 + LPH, 65 + LPH, 0xff
};

// taken from "key_led_map" and reformatted
// ISO & ANSI (ANSI has no LED at 20, but this key can never be pressed so we can have just one map).
led_config_t g_led_config = { {
    // left hand
    { 0  , 1  , 2  , 3  , 4  , 5      , 6      , NO_LED } ,
    { 7  , 8  , 9  , 10 , 11 , 12     , NO_LED , NO_LED } ,
    { 13 , 14 , 15 , 16 , 17 , 18     , NO_LED , NO_LED } ,
    { 19 , 20 , 21 , 22 , 23 , 24     , 25     , NO_LED } ,
    { 26 , 27 , 28 , 29 , 30 , NO_LED , 31     , 32     } ,

    // right hand
    { 33  , 34  , 35  , 36  , 37 , 38  , 39     , NO_LED } ,
    { 40 ,  41 ,  42 ,  43 ,  44 , 45  , 46     , 47     } ,
    { 48 ,  49 ,  50 ,  51 ,  52 , 53  , 54     , NO_LED } ,
    { 55 ,  56 ,  57 ,  58 ,  59 , 60 ,  NO_LED ,  NO_LED    } ,
    { 61 ,  62 ,  63 ,  64 ,  65 , 66 ,  67 ,  68 }
  }, {
    // generated from the svg image of the keyboard, see create-led-config.js
    {82, 3}, {88, 3}, {94, 3}, {100, 3}, {106, 3}, {112, 3}, {118, 3}, {84, 10}, {91, 10}, {97, 10}, {103, 10}, {109, 10},
    {115, 10}, {84, 16}, {92, 16}, {98, 16}, {104, 16}, {110, 16}, {116, 16}, {82, 22}, {88, 22}, {94, 22}, {100, 22},
    {106, 22}, {112, 22}, {118, 22}, {83, 28}, {90, 28}, {98, 28}, {106, 28}, {116, 28}, {111, 34}, {118, 34}, {168, 3},
    {159, 3}, {153, 3}, {147, 3}, {141, 3}, {135, 3}, {129, 3}, {170, 13}, {162, 10}, {156, 10}, {150, 10}, {144, 10},
    {139, 10}, {133, 10}, {127, 10}, {164, 16}, {158, 16}, {152, 16}, {146, 16}, {140, 16}, {134, 16}, {128, 16}, {166, 22},
    {154, 22}, {148, 22}, {142, 22}, {136, 22}, {130, 22}, {170, 28}, {163, 28}, {156, 28}, {149, 28}, {140, 28}, {131, 28},
    {136, 34}, {128, 34}, {78, 13}, {78, 6}, {80, 0}, {87, 0}, {95, 0}, {103, 0}, {111, 0}, {119, 0}, {122, 3}, {121, 9},
    {120, 15}, {122, 21}, {123, 27}, {123, 33}, {120, 38}, {116, 42}, {114, 48}, {112, 55}, {109, 61}, {103, 64}, {96, 64},
    {88, 64}, {81, 63}, {76, 60}, {75, 52}, {75, 46}, {74, 38}, {74, 32}, {75, 27}, {77, 21}, {175, 10}, {175, 4}, {172, 0},
    {164, 0}, {157, 0}, {149, 0}, {142, 0}, {134, 0}, {127, 0}, {123, 3}, {122, 8}, {122, 15}, {124, 21}, {124, 27}, {124, 33},
    {126, 38}, {131, 42}, {134, 48}, {135, 55}, {137, 61}, {143, 63}, {150, 63}, {158, 63}, {166, 63}, {173, 63}, {177, 59},
    {178, 49}, {179, 40}, {179, 31}, {177, 25}, {175, 20}, {175, 15}, {123, 54}

  }, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4
  }
};
