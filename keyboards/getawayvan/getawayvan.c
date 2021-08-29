/* Copyright 2020 QMK
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

#include "getawayvan.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0,  1,  2,      3,  4,      5,  6,      7,  8,  9, 10, 11 },
  { 12, 13, 14,     15, 16,     17, 18,     19, 20, 21, 22, 23 },
  { 24, 25, 26,     27, 28,     29, 30,     31, 32, 33, 34, 36 },
  { 37, 39, 41, NO_LED, 42,     43, 44, NO_LED, 45, 46, 48, 50 }
}, {
  // LED Index to Physical Position
  {  0,  0}, { 19,  0}, { 38,  0}, { 57,  0}, { 76,  0}, { 95,  0}, {114,  0}, {133,  0}, {152,  0}, {172,  0}, {191,  0}, {217,  0},
  {  2, 21}, { 22, 21}, { 41, 21}, { 60, 21}, { 79, 21}, { 98, 21}, {117, 21}, {136, 21}, {155, 21}, {175, 21}, {194, 21}, {220, 21},
  {  7, 43}, { 33, 43}, { 52, 43}, { 71, 43}, { 91, 43}, {110, 43}, {129, 43}, {148, 43}, {167, 43}, {186, 43}, {205, 43}, {214, 43}, {224, 43},
  {  0, 64}, {  7, 64}, { 21, 64}, { 31, 64}, { 41, 64},            { 76, 64}, {112, 64}, {127, 64},            {159, 64}, {187, 64}, {189, 64}, {205, 64}, {219, 64}, {224, 64}
}, {
  // LED Index to Flag
  5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
  5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
  5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
  5, 5, 5,    5,    5,    5, 5, 5, 5, 5, 5, 5, 5, 5
} };

#endif
