/* Copyright 2021 Neo keys
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
led_config_t g_led_config = { {
    // Key Matrix to LED Index
      { 86,     85,     84,     83,     82,     81,     80,     79,     78,     77,     76,     75,     74,     73,     72,     71      },    // 16
      { 70,     69,     68,     67,     66,     65,     64,     63,     62,     61,     60,     59,     58,     NO_LED, 57,     56      },    // 15
      { 55,     54,     53,     52,     51,     50,     49,     48,     47,     46,     45,     44,     43,     42,     41,     40      },    // 16
      { 39,     38,     37,     36,     35,     34,     33,     32,     31,     30,     29,     28,     NO_LED, 27,     26,     25      },    // 15 
      { 24,     NO_LED, 23,     22,     21,     20,     19,     18,     17,     16,     15,     14,     13,     NO_LED, 12,     11      },    // 14
      { 10,     9,      8,      NO_LED, NO_LED, NO_LED, NO_LED, 7,      6,      5,      NO_LED, 4,      3,      2,      1,      0       }     // 11
  }, 
  {  // Index to Physical Position
      {252,108}, {238,108}, {196,108}, {178,108}, {160,108},            {150, 21}, {226,  0}, {100,108},                                             { 40,108}, { 22,108}, {  4,108},    // 11
      {233, 42}, {219, 86},            {184, 86}, {158, 86}, {144, 86}, {130, 86}, {116, 86}, {102, 86}, { 88, 86}, { 74, 86}, { 60, 86}, { 46, 86}, { 32, 86},            {  9, 86},    // 14
      {224, 21}, {238,108}, {197, 64},            {174, 64}, {160, 64}, {146, 64}, {132, 64}, {108, 64}, { 94, 64}, { 80, 64}, { 66, 64}, { 52, 64}, { 38, 64}, { 24, 64}, {  5, 64},    // 15
      {252, 42}, {238, 42}, {214, 42}, {196, 42}, {182, 42}, {168, 42}, {134, 42}, {120, 42}, {106, 42}, { 92, 42}, { 78, 42}, { 64, 42}, { 50, 42}, { 36, 42}, { 22, 42}, {  4, 42},    // 16
      {252, 21}, {238, 21},            {201, 21}, {180, 21}, {164, 21}, {136, 21}, {122, 21}, {108, 21}, { 94, 21}, { 80, 21}, { 66, 21}, { 42, 21}, { 28, 21}, { 14, 21}, {  0, 21},    // 15
      {252,  0}, {238,  0}, {208,  0}, {190,  0}, {176,  0}, {162,  0}, {148,  0}, {130,  0}, {106,  0}, { 92,  0}, { 78,  0}, { 60,  0}, { 46,  0}, { 32,  0}, { 18,  0}, {  0,  0}     // 16
  },
  {
      1, 1, 1, 1, 1,    1, 1, 2,             1, 1, 1,      // 11
      1, 1,    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,    1,      // 14
      1, 1, 1,    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,      // 15
      1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,      // 16
      1, 1,    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,      // 15
      1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1       // 16
  } 
};
#endif