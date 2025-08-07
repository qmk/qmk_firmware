/* Copyright 2021 3araht
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

#include "chromatonemini.h"

#ifdef RGB_MATRIX_ENABLE
#    define NO_LED 255

// indicator
const uint8_t led_scale_indicator[12][12] = {
  {23, 29, 35, 41, 60, 66,  72,  78,  97, 103,    109,    115},     //  C
  { 5, 11, 17, 42, 48, 54,  79,  85,  91, NO_LED, NO_LED, NO_LED},  //  C#
  {28, 34, 40, 65, 71, 77, 102, 108, 114, NO_LED, NO_LED, NO_LED},  //  D
  { 6, 12, 18, 43, 49, 55,  80,  86,  92, NO_LED, NO_LED, NO_LED},  //  D#
  {27, 33, 39, 64, 70, 76, 101, 107, 113, NO_LED, NO_LED, NO_LED},  //  E
  { 7, 13, 19, 44, 50, 56,  81,  87,  93, NO_LED, NO_LED, NO_LED},  //  F
  {26, 32, 38, 63, 69, 75, 100, 106, 112, NO_LED, NO_LED, NO_LED},  //  F#
  { 8, 14, 20, 45, 51, 57,  82,  88,  94, NO_LED, NO_LED, NO_LED},  //  G
  {25, 31, 37, 62, 68, 74,  99, 105, 111, NO_LED, NO_LED, NO_LED},  //  G#
  { 9, 15, 21, 46, 52, 58,  83,  89,  95, NO_LED, NO_LED, NO_LED},  //  A
  {24, 30, 36, 61, 67, 73,  98, 104, 110, NO_LED, NO_LED, NO_LED},  //  A#
  {10, 16, 22, 47, 53, 59,  84,  90,  96, NO_LED, NO_LED, NO_LED}   //  B
};

const uint8_t led_single_col_indicator[37][3] = {
  {41, 78, 115},  //  K01  = C1
  { 5, 42,  79},  //  K02  = C#1
  {40, 77, 114},  //  K03  = D1
  { 6, 43,  80},  //  K04  = D#1
  {39, 76, 113},  //  K05  = E1
  { 7, 44,  81},  //  K06  = F1
  {38, 75, 112},  //  K07  = F#1
  { 8, 45,  82},  //  K08  = G1
  {37, 74, 111},  //  K09  = G#1
  { 9, 46,  83},  //  K10  = A1
  {36, 73, 110},  //  K11  = A#1
  {10, 47,  84},  //  K12  = B1
  {35, 72, 109},  //  K13  = C2
  {11, 48,  85},  //  K14  = C#2
  {34, 71, 108},  //  K15  = D2
  {12, 49,  86},  //  K16  = D#2
  {33, 70, 107},  //  K17  = E2
  {13, 50,  87},  //  K18  = F2
  {32, 69, 106},  //  K19  = F#2
  {14, 51,  88},  //  K20  = G2
  {31, 68, 105},  //  K21  = G#2
  {15, 52,  89},  //  K22  = A2
  {30, 67, 104},  //  K23  = A#2
  {16, 53,  90},  //  K24  = B2
  {29, 66, 103},  //  K25  = C3
  {17, 54,  91},  //  K26  = C#3
  {28, 65, 102},  //  K27  = D3
  {18, 55,  92},  //  K28  = D#3
  {27, 64, 101},  //  K29  = E3
  {19, 56,  93},  //  K30  = F3
  {26, 63, 100},  //  K31  = F#3
  {20, 57,  94},  //  K32  = G3
  {25, 62,  99},  //  K33  = G#3
  {21, 58,  95},  //  K34  = A3
  {24, 61,  98},  //  K35  = A#3
  {22, 59,  96},  //  K36  = B3
  {23, 60,  97}   //  K37  = C4
};

#endif  //  RGB_MATRIX_ENABLE

uint8_t shift_led_indicator_left(uint8_t scale_indicator_col){
    if (scale_indicator_col > 0) {
        scale_indicator_col--;
    } else {
        scale_indicator_col = 11;
    }
    return scale_indicator_col;
}

uint8_t shift_led_indicator_right(uint8_t scale_indicator_col){
    if (scale_indicator_col < 11) {
        scale_indicator_col++;
    } else {
        scale_indicator_col = 0;
    }
    return scale_indicator_col;
}
