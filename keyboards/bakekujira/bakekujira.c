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

#include "bakekujira.h"

#ifdef RGB_MATRIX_ENABLE

  // Physical and logical Layout
  // 18 cols, 5 rows
  // x = 13 * col position
  // y = 16 * row position
  // Columns
  //  0  1  2  3  4  5  6    7  8  9 10 11 12 13 14  15 16 17   Rows
  // 13 19 20 29 30 37 38   58 57 50 49 40 39    32  27 26 20    0
  // 14    21 28 31 36 39   59 56 51 48 41 38 33 31  28 25 21    1
  // 15    22 27 32 35 40   60 55 52 47 42 37 34                 2
  //    18 23 26 33 34 41   61 54 53 46 43    35        24       3
  // 16 17 24 25       42   62       45 44    36 30  29 23 22    4

  // backlight L physical and logical layout
  // 0  1  2  3  4  5  6
  //                        Rows
  // 12   11  10   9        0
  // 1             8        1
  // 2               7      2
  //  3  4     5     6      3

  // backlight R physical and logical layout
  // 7  8  9  10  11  12  13  14   15  16  17
  //                                     Rows
  // 13  14   15   16  17   18    19        0
  // 12                              1      1
  // 11                              2      2
  //                                 3      3
  //   10   9    8   7  6    5    4         4

led_config_t g_led_config = { {
    {  12,           18,      19,     28,        29,      36,       37,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  13,       NO_LED,      20,     27,        30,      35,       38,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  14,       NO_LED,      21,     26,        31,      34,       39,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  NO_LED,       17,      22,     25,        32,      33,       40,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  15,           16,      23,     24,    NO_LED,  NO_LED,       41,  NO_LED,  NO_LED,  NO_LED,    NO_LED },

    {  57,           56,      49,     48,        39,      38,   NO_LED,      31,      26,      25,        19 },
    {  58,           55,      50,     47,        40,      37,       32,      30,      27,      24,        20 },
    {  59,           54,      51,     46,        41,      36,       33,  NO_LED,  NO_LED,  NO_LED,    NO_LED },
    {  60,           53,      52,     45,        42,  NO_LED,       34,  NO_LED,  NO_LED,      23,    NO_LED },
    {  61,       NO_LED,  NO_LED,     44,        43,  NO_LED,       35,      29,      28,      22,        21 },
}, {
    {   0,   0 }, {  13,   0 }, {  26,   0 }, {  39,   0 }, {  52,   0 }, {  65,  0  }, {  78,  0  },   {  91,   0 }, { 104,   0 }, { 117,   0 }, { 130,   0 }, { 143,   0 }, { 156,   0 },                { 182,  0 },           {  208,  0 }, { 221,   0 }, { 234,   0 },
    {   0,  16 },               {  26,  16 }, {  39,  16 }, {  52,  16 }, {  65,  16 }, {  78,  16 },   {  91,  16 }, { 104,  16 }, { 117,  16 }, { 130,  16 }, { 143,  16 }, { 156,  16 }, { 169,  16 },  { 182,  16 },          {  208, 16 }, { 221,  16 }, { 234,  16 },
    {   0,  32 },               {  26,  32 }, {  39,  32 }, {  52,  32 }, {  65,  32 }, {  78,  32 },   {  91,  32 }, { 104,  32 }, { 117,  32 }, { 130,  32 }, { 143,  32 }, { 156,  32 }, { 169,  32 },
                  {  13,  48 }, {  26,  48 }, {  39,  48 }, {  52,  48 }, {  65,  48 }, {  78,  48 },   {  91,  48 }, { 104,  48 }, { 117,  48 }, { 130,  48 }, { 143,  48 },               { 169,  48 },                                       { 221,  48 },
    {   0,  64 }, {  13,  64 }, {  26,  64 }, {  39,  64 },                             {  78,  64 },   {  33,  64 },                             { 130,  64 }, { 143,  64 },               { 169,  64 },  { 182,  64 },          {  208, 64 }, { 221,  64 }, { 234,  64 },

    {   0,   8 }, {  13,  8 }, {  39,   8 }, {  58,   8 },    {   98,   8 }, { 111,   8 }, { 130,   8 }, { 150,   8 }, { 163,   8 },  { 176,   8 }, { 195,    8 },
    {   0,  24 },                            {  58,  24 },    {   91,  24 },                                                                                        { 201,   24 },
    {   0,  40 },                            {  72,  40 },    {   91,  40 },                                                                                        { 201,   40 },
                                                                                                                                                                    { 201,   56 },
    {   0,  56 }, {  13,  56 },{  39,  56 }, {  72,   56 },   {  104,  56 }, { 117,  56 }, { 137,  56 }, { 156,  56 },  { 163,  56 }, { 176,  56 },  { 195, 56}
}, {
    4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4,    4,    4, 4, 4,
    1,    4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4,
    1,    4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,
       1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4,    1,          4,
    1, 1, 1, 1,       4,  4,       1, 1,    1, 1,    4, 4, 4,

    2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

}};
#endif

void matrix_init_kb(void) {
    matrix_init_user();
}

#ifdef SSD1306OLED
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_gfx(keycode,record) && process_record_user(keycode, record);
}
#endif
