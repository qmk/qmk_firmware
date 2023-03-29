/* 
/ Copyright 2022 quarkeys
/ This program is free software: you can redistribute it and/or modify
/ it under the terms of the GNU General Public License as published by
/ the Free Software Foundation, either version 2 of the License, or
/ (at your option) any later version.
/ This program is distributed in the hope that it will be useful,
/ but WITHOUT ANY WARRANTY; without even the implied warranty of
/ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/ GNU General Public License for more details.
/ You should have received a copy of the GNU General Public License
/ along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "z40.h"
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    /*
        { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B }, \
        { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B }, \
        { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B }, \
        { k30, k31, k32, k33, k34, k35, XXX, k36, k37, k38, k39, k3A }\
    */
        { 46,     45,     44,     43,     42,     41,     40,     39,     38,     37,     36,     35      },
        { 34,     33,     32,     31,     30,     29,     28,     27,     26,     25,     24,     23      },
        { 22,     21,     20,     29,     18,     17,     16,     15,     14,     13,     12,     11      },
        { 10,      9,      8,      7,      6,          5,          4,      3,      2,      1,      0      }
  }, 
  {  // Index to Physical Position
      {225, 64}, {200, 64}, {180, 64}, {160, 64}, {140, 64},            {110, 64}, { 80, 64}, { 60, 64}, { 40, 64}, { 20, 64}, {  0, 64},
      {225, 42}, {200, 42}, {180, 42}, {160, 42}, {140, 42}, {120, 42}, {100, 42}, { 80, 42}, { 60, 42}, { 40, 42}, { 20, 42}, {  0, 42},
      {225, 21}, {200, 21}, {180, 21}, {160, 21}, {140, 21}, {120, 21}, {100, 21}, { 80, 21}, { 60, 21}, { 40, 21}, { 20, 21}, {  0, 21},
      {225,  0}, {200,  0}, {180,  0}, {160,  0}, {140,  0}, {120,  0}, {100,  0}, { 80,  0}, { 60,  0}, { 40,  0}, { 20,  0}, {  0,  0}
  }, 
  {
      1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1,
      1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
      1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
      1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1
  } 
};
#endif
