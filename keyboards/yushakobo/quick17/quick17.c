/* Copyright 2021 yushakobo
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

#include "quick17.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {12, 13, 14, 15, 16, 17},
        {0, 1, 11, 10, 9, 8},
        {2, 3, 4, 5, 6, 7}
    },
    {
        {0,32},  {44,32}, {0,64},  {44,64}, {89,64}, {134,64},
        {179,64},{224,64},{224,32},{179,32},{134,32},{89,32},
        {0,0},   {44,0},  {89,0},  {134,0}, {179,0}, {224,0}
    },
    {
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4
    }
};
#endif
