/* Copyright 2020 Boardsource
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

#include "beiwagon.h"
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  {7,8,9},
    {10,11,12},
    {13,14,15},
    {16,17,18}
}, {
   {2, 0}, {1, 0}, {0, 0},
   {2, 1}, {1, 1}, {0, 1},
   {2, 2}, {1, 2}, {0, 2},
   {2, 3}, {1, 3}, {0, 3},
}, {
    2, 2, 2, 2, 2, 2, 
    1, 1, 1,
    1, 4, 1,
    1, 4, 1,
    1, 1, 1 

} };
#endif

