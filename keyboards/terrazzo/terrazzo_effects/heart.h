/* Copyright 2020 ademey "MsMustard"
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

#ifndef DISABLE_TERRAZZO_EFFECT_HEART
TERRAZZO_EFFECT(HEART)
#   ifdef TERRAZZO_EFFECT_IMPLS

static uint8_t heart_frames[4][105] = {
{
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 5, 5, 0, 5, 5, 0,
    5, 0, 0, 5, 0, 0, 5,
    5, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 0, 0, 5, 0,
    0, 0, 5, 0, 5, 0, 0,
    0, 0, 0, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
},
{
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 5, 5, 0, 5, 5, 0,
    5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5,
    0, 5, 5, 5, 5, 5, 0,
    0, 0, 5, 5, 5, 0, 0,
    0, 0, 0, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
},
{
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 0,
    1, 0, 0, 5, 0, 0, 1,
    0, 5, 5, 0, 5, 5, 0,
    5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5,
    0, 5, 5, 5, 5, 5, 0,
    0, 0, 5, 5, 5, 0, 0,
    1, 0, 0, 5, 0, 0, 1,
    0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
},
{
    0, 1, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 0, 1,
    0, 5, 5, 0, 5, 5, 0,
    5, 0, 0, 5, 0, 0, 5,
    0, 5, 5, 0, 5, 5, 0,
    5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5,
    0, 5, 5, 5, 5, 5, 0,
    0, 0, 5, 5, 5, 0, 0,
    5, 0, 0, 5, 0, 0, 5,
    0, 5, 0, 0, 0, 5, 0,
    1, 0, 5, 0, 5, 0, 1,
    0, 1, 0, 5, 0, 1, 0,
    0, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0
}
};


void HEART(uint8_t i, bool dir) {
    led_matrix_set_value_all(0);
    terrazzo_draw_at(0, 0, 7, 15, heart_frames[i % 4]);
}

#   endif
#endif