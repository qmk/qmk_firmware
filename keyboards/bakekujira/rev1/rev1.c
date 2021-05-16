/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE

  // Physical and logical Layout
  // 18 cols, 5 rows
  // x = 13 * col position
  // y = 16 * row position

  // Columns
  //  0  1  2  3  4  5  6    7  8  9 10 11 12 13 14  15 16 17   Rows
  //
  // 13 19 20 29 30 37 38   58 57 50 49 40 39    32  27 26 20    0
  // 12   11  10   9        13  14   15   16  17   18    19      1 backlight
  // 14    21 28 31 36 39   59 56 51 48 41 38 33 31  28 25 21    1
  // 1               8      12                              1    2 backlight
  // 15    22 27 32 35 40   60 55 52 47 42 37 34                 2
  // 2               7      11                              2    3 backlight
  //    18 23 26 33 34 41   61 54 53 46 43    35        24       3
  //  3  4     5     6        10   9    8   7  6    5    4  3    4 backlight
  // 16 17 24 25       42   62       45 44    36 30  29 23 22    4


  // backlight L physical and logical layout
  // 0  1  2  3  4  5  6    Rows
  //                        0
  // 12   11  10   9        1
  // 1             8        2
  // 2               7      3
  //  3  4     5     6      4

  // backlight R physical and logical layout
  // 7  8  9  10  11  12  13  14   15  16  17
  //                                        0
  // 13  14   15   16  17   18    19        1
  // 12                              1      2
  // 11                              2      3
  //   10   9    8   7  6    5    4  3      4


led_config_t g_led_config = { {
    {  12,             18,       19,     28,        29,      36,       37,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  13,         NO_LED,       20,     27,        30,      35,       38,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  14,         NO_LED,       21,     26,        31,      34,       39,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  NO_LED,         17,       22,     25,        32,      33,       40,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  15,             16,       23,     24,    NO_LED,  NO_LED,       41,  NO_LED,  NO_LED,  NO_LED,    NO_LED },

    // { 61, 67, 68, 73, NO_LED, 80, 81, 90, 91, 98, 99 },
    // { 62, 66, 69, 72, 74, 79, 82, 89, 92, 97, 100 },
    // { NO_LED, NO_LED, NO_LED, NO_LED, 75, 78, 83, 88, 93, 96, 101 },
    // { NO_LED, 65, NO_LED, NO_LED, 76, NO_LED, 84, 87, 94, 95, 102 },
    // { 63, 64, 70, 71, 77, NO_LED, 85, 86, NO_LED, NO_LED, 103 },

    {   99,            98,       91,     90,        81,      80,   NO_LED,      73,      68,      67,        61 },
    {  100,            97,       92,     89,        82,      79,       74,      72,      69,      66,        62 },
    {  101,            96,       93,     88,        83,      78,       75,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  102,            95,       94,     87,        84,  NO_LED,       76,  NO_LED,  NO_LED,      65,    NO_LED },
    {  103,        NO_LED,   NO_LED,     86,        85,  NO_LED,       77,      71,      70,      64,        63 },
}, {
    // physical underglow placement
    // {   0,   8 }, {  13,  8 }, {  39,   8 }, {  58,   8 },    {   98,   8 }, { 111,   8 }, { 130,   8 }, { 150,   8 }, { 163,   8 },  { 176,   8 }, { 195,    8 },
    // {   0,  24 },                            {  58,  24 },    {   91,  24 },                                                                                        { 201,   24 },
    // {   0,  40 },                            {  72,  40 },    {   91,  40 },                                                                                        { 201,   40 },
    // {   0,  56 }, {  13,  56 },{  39,  56 }, {  72,   56 },   {  104,  56 }, { 117,  56 }, { 137,  56 }, { 156,  56 },  { 163,  56 }, { 176,  56 },  { 195, 56},    { 201,   56 },


    // following is the phyiscal placement for reference for the left side
    // {   0,   0 }, {  13,   0 }, {  26,   0 }, {  39,   0 }, {  52,   0 }, {  65,  0  }, {  78,  0  },
    // {   0,  16 },               {  26,  16 }, {  39,  16 }, {  52,  16 }, {  65,  16 }, {  78,  16 },
    // {   0,  32 },               {  26,  32 }, {  39,  32 }, {  52,  32 }, {  65,  32 }, {  78,  32 },
    //               {  13,  48 }, {  26,  48 }, {  39,  48 }, {  52,  48 }, {  65,  48 }, {  78,  48 },
    // {   0,  64 }, {  13,  64 }, {  26,  64 }, {  39,  64 },                             {  78,  64 },

    // underglow indexes from 0 to 11
    {   0,  24 }, {   0,  40 }, {   0,  56 }, {  13,  56 },{  39,  56 }, {  72,   56 },  {  72,  40 }, {  58,  24 }, {  58,   8 }, {  39,   8 }, {  13,  8 }, {   0,   8 },
    // left side starts at index 12
    {   0,   0 }, {   0,  16 }, {   0,  32 }, {   0,  64 },
    {  13,  64 }, {  13,  48 }, {  13,   0 },
    {  26,   0 }, {  26,  16 }, {  26,  32 }, {  26,  48 }, {  26,  64 },
    {  39,  64 }, {  39,  48 }, {  39,  32 }, {  39,  16 }, {  39,   0 },
    {  52,   0 }, {  52,  16 }, {  52,  32 }, {  52,  48 },
    {  65,  48 }, {  65,  32 }, {  65,  16 }, {  65,  0  },
    {  78,  0  }, {  78,  16 }, {  78,  32 }, {  78,  48 },  {  78,  64 },

// {  91,   0 }, { 104,   0 }, { 117,   0 }, { 130,   0 }, { 143,   0 }, { 156,   0 },                { 182,  0 },           {  208,  0 }, { 221,   0 }, { 234,   0 },
// {  91,  16 }, { 104,  16 }, { 117,  16 }, { 130,  16 }, { 143,  16 }, { 156,  16 }, { 169,  16 },  { 182,  16 },          {  208, 16 }, { 221,  16 }, { 234,  16 },
// {  91,  32 }, { 104,  32 }, { 117,  32 }, { 130,  32 }, { 143,  32 }, { 156,  32 }, { 169,  32 },
// {  91,  48 }, { 104,  48 }, { 117,  48 }, { 130,  48 }, { 143,  48 },               { 169,  48 },                                       { 221,  48 },
// {  33,  64 },                             { 130,  64 }, { 143,  64 },               { 169,  64 },  { 182,  64 },          {  208, 64 }, { 221,  64 }, { 234,  64 },

    // underglow indexes for right side
    { 201,   24 }, { 201,   40 }, { 201,   56 }, { 195, 56}, { 176,  56 }, { 163,  56 }, { 156,  56 }, { 137,  56 },  { 117,  56 }, {  104,  56 }, {   91,  40 },  {   91,  24 },  {   98,   8 }, { 111,   8 }, { 130,   8 }, { 150,   8 },  { 163,   8 },  { 176,   8 }, { 195,    8 },
    // right side
    { 234,   0 }, { 234,  16 }, { 234,  64 },
    { 221,  64 }, { 221,  48 }, { 221,  16 }, { 221,   0 },
    { 208,   0 }, {  208, 16 }, { 208,  64 },
    { 182,  64 }, { 182,  16 }, { 182,   0 },
    { 169,  16 }, { 169,  32 }, { 169,  48 }, { 169,  64 },
    { 156,  32 }, { 156,  16 }, { 156,   0 },
    { 143,   0 }, { 143,  16 }, { 143,  32 }, { 143,  48 }, { 143,  64 },
    { 130,  64 }, { 130,  48 }, { 130,  32 }, { 130,  16 }, { 130,   0 },
    { 117,   0 }, { 117,  16 }, { 117,  32 }, { 117,  48 },
    { 104,  48 }, { 104,  32 }, { 104,  16 }, { 104,   0 },
    {  91,   0 }, {  91,  16 }, {  91,  32 }, {  91,  48 }, {  33,  64 }

}, {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 12 underglow
    4, 1, 1, 1,
    1, 1, 4,
    4, 4, 4, 4, 1,
    1, 4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4, 4,

    // physical placement reference for left side
    // 4, 4, 4, 4, 4, 4, 4,
    // 1,    4, 4, 4, 4, 4,
    // 1,    4, 4, 4, 4, 4,
    //    1, 4, 4, 4, 4, 4,
    // 1, 1, 1, 1,       4,

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 19 underglow lights
    4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4,
    1, 4, 4,
    4, 4, 1, 1,
    4, 4, 4,
    4, 4, 4, 4, 1,
    1, 4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4, 4

    // physical placemnet for reference for right side
    // 4, 4, 4, 4, 4, 4,    4,    4, 4, 4,
    // 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4,
    // 4, 4, 4, 4, 4, 4, 4,
    // 4, 4, 4, 4, 4,    1,          4,
    // 4,       1, 1,    1, 1,    4, 4, 4,
}};
#endif


#ifdef SSD1306OLED
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_gfx(keycode,record) && process_record_user(keycode, record);
}
#endif
