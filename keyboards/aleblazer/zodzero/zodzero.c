/*
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "zodzero.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
// Key Matrix to LED Index
  // Left Hand
  { 8, 6, 5, 3, 2, 0, 15, NO_LED },
  { 9, 10, 11, 12, 13, 14, 17, NO_LED},
  { 23, 22, 21, 20, 19, 18, 16, NO_LED},
  { 24, 26, 27, 29, 30, 32, 34, NO_LED },
  // Right Hand
  { 43, 41, 40, 38, 37, 35, 50, NO_LED },
  { 44, 45, 46, 47, 48, 49, 52, NO_LED},
  { 58, 57, 56, 55, 54, 53, 51, NO_LED},
  { 59, 61, 62, 64, 65, 67, 69, NO_LED },
}, {
  // LED Index to Physical Position
  // Left Hand
  { 77, 4 },
{ 69, 2 },
{ 62, 3 },
{ 47, 1 },
{ 39, 1 },
{ 33, 3 },
{ 18, 10 },
{ 10, 9 },
{ 3, 11 },
{ 3, 25 },
{ 18, 24 },
{ 33, 17 },
{ 47, 15 },
{ 62, 17 },
{ 77, 18 },
{ 92, 25 },
{ 107, 50 },
{ 94, 43 },
{ 77, 32 },
{ 62, 31 },
{ 47, 29 },
{ 33, 31 },
{ 18, 38 },
{ 3, 39 },
{ 3, 52 },
{ 10, 62 },
{ 18, 51 },
{ 33, 45 },
{ 41, 54 },
{ 47, 43 },
{ 62, 45 },
{ 70, 56 },
{ 84, 53 },
{ 88, 64 },
{ 100, 62 },
{ 147, 4 },
{ 155, 2 },
{ 162, 3 },
{ 177, 1 },
{ 185, 1 },
{ 192, 3 },
{ 206, 10 },
{ 214, 9 },
{ 221, 11 },
{ 221, 25 },
{ 206, 24 },
{ 192, 17 },
{ 177, 15 },
{ 162, 17 },
{ 147, 18 },
{ 133, 25 },
{ 117, 50 },
{ 130, 43 },
{ 147, 32 },
{ 162, 31 },
{ 177, 29 },
{ 192, 31 },
{ 206, 38 },
{ 221, 39 },
{ 221, 52 },
{ 214, 62 },
{ 206, 51 },
{ 192, 45 },
{ 183, 54 },
{ 177, 43 },
{ 162, 45 },
{ 155, 56 },
{ 140, 53 },
{ 136, 64 },
{ 124, 62 },
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
