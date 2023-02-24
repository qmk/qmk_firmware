/* Copyright 2022 Leo Deng (@myst729)
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
#include "djam.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
  {
    /* Key Matrix to LED Index */
    { 17, 16, 15, NO_LED, NO_LED, 7, 6, 5 },
    { 21, 17, 16, 15, 7, 6, 5, 1 },
    { 19, 18, 13, 11, 9, 4, 3, NO_LED }
  },
  {
    /* LED Index to Physical Position */
    // Switch LEDs
    {224,14}, {224,24}, {224,33}, {212,57}, {192,57}, {192,38}, {172,38}, {152,38},
    {152,57}, {142,57}, {132,57}, {112,57}, {92,57},  {82,57},  {72,57},
    {72,38},  {52,38},  {32,38},  {32,57},  {12,57},  {0,33},   {0,24},   {0,14},
    // Underglow LEDs
    {0,0},    {92,0},   {132,0},  {224,0},  {222,64}, {172,64}, {72,64},  {2,64},
  },
  {
    /* LED Index to Flag */
    2, 4, 2, 4, 4, 4, 4, 4,
    2, 4, 2, 4, 2, 4, 2,
    4, 4, 4, 4, 4, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 2, 2
  }
};
#endif
