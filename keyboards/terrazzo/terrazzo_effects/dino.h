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

#ifndef DISABLE_TERRAZZO_EFFECT_DINO
TERRAZZO_EFFECT(DINO)
#   ifdef TERRAZZO_EFFECT_IMPLS

static uint8_t dino_frames[2][56] = {
{
    0, 0, 0, 9, 9, 9, 9,
    0, 0, 0, 9, 0, 9, 9,
    9, 0, 0, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 0, 0,
    9, 9, 9, 9, 9, 0, 0,
    0, 9, 9, 9, 0, 0, 0,
    0, 9, 0, 9, 9, 0, 0,
    0, 9, 9, 0, 0, 0, 0
},
{
    0, 0, 0, 9, 9, 9, 9,
    0, 0, 0, 9, 0, 9, 9,
    9, 0, 0, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 0, 0,
    9, 9, 9, 9, 9, 0, 0,
    0, 9, 9, 9, 0, 0, 0,
    0, 9, 0, 9, 0, 0, 0,
    0, 0, 0, 9, 9, 0, 0
}
};

static uint8_t dino_reverse[2][56] = {
{
    9, 9, 9, 9, 0, 0, 0,
    9, 9, 0, 9, 0, 0, 0,
    9, 9, 9, 9, 0, 0, 9,
    0, 0, 9, 9, 9, 9, 9,
    0, 0, 9, 9, 9, 9, 9,
    0, 0, 0, 9, 9, 9, 0,
    0, 0, 9, 9, 0, 9, 0,
    0, 0, 0, 0, 9, 9, 0
},
{
    9, 9, 9, 9, 0, 0, 0,
    9, 9, 0, 9, 0, 0, 0,
    9, 9, 9, 9, 0, 0, 9,
    0, 0, 9, 9, 9, 9, 9,
    0, 0, 9, 9, 9, 9, 9,
    0, 0, 0, 9, 9, 9, 0,
    0, 0, 0, 9, 0, 9, 0,
    0, 0, 9, 9, 0, 0, 0
}
};

static uint8_t dino_bg[10][42] = {
{
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 0,
    0, 0, 0, 0, 0, 4, 0,
    0, 1, 1, 0, 0, 0, 4,
    1, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0
},
{
    0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 4, 0, 4,
    0, 0, 0, 0, 4, 0, 4,
    1, 1, 0, 0, 0, 4, 4,
    0, 0, 1, 1, 1, 1, 4,
    0, 0, 0, 0, 0, 0, 4
},
{
    0, 0, 0, 0, 0, 4, 0,
    0, 0, 0, 4, 0, 4, 0,
    0, 0, 0, 4, 0, 4, 4,
    1, 0, 0, 0, 4, 4, 0,
    0, 1, 1, 1, 1, 4, 0,
    0, 0, 0, 0, 0, 4, 0
},
{
    0, 0, 0, 0, 4, 0, 0,
    0, 0, 4, 0, 4, 0, 4,
    0, 0, 4, 0, 4, 4, 4,
    0, 0, 0, 4, 4, 0, 0,
    1, 1, 1, 1, 4, 1, 1,
    0, 0, 0, 0, 4, 0, 0
},
{
    0, 0, 0, 4, 0, 0, 0,
    0, 4, 0, 4, 0, 4, 0,
    0, 4, 0, 4, 4, 4, 0,
    0, 0, 4, 4, 0, 0, 0,
    1, 1, 1, 4, 1, 1, 1,
    0, 0, 0, 4, 0, 0, 0
},
{
    0, 0, 4, 0, 0, 0, 0,
    4, 0, 4, 0, 4, 0, 0,
    4, 0, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 0, 1,
    1, 1, 4, 1, 1, 1, 0,
    0, 0, 4, 0, 0, 0, 0
},
{
    0, 4, 0, 0, 0, 0, 0,
    0, 4, 0, 4, 0, 0, 0,
    0, 4, 4, 4, 0, 0, 0,
    4, 4, 0, 0, 0, 1, 1,
    1, 4, 1, 1, 1, 0, 0,
    0, 4, 0, 0, 0, 0, 0
},
{
    4, 0, 0, 0, 0, 0, 0,
    4, 0, 4, 0, 0, 0, 0,
    4, 4, 4, 0, 0, 0, 0,
    4, 0, 0, 0, 1, 1, 0,
    4, 1, 1, 1, 0, 0, 1,
    4, 0, 0, 0, 0, 0, 0
},
{
    0, 0, 0, 0, 0, 0, 0,
    0, 4, 0, 0, 0, 0, 0,
    4, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0,
    1, 1, 1, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0
},
{
    0, 0, 0, 0, 0, 0, 0, 
    4, 0, 0, 0, 0, 0, 4, 
    4, 0, 0, 0, 0, 0, 4, 
    0, 0, 1, 1, 0, 0, 0, 
    1, 1, 0, 0, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0
}
};

void DINO(uint8_t i, bool dir) {
    led_matrix_set_value_all(0);
    if (dir) {
        terrazzo_draw_at(0, 7, 7, 8, dino_frames[i % 2]);
    } else {
        terrazzo_draw_at(0, 7, 7, 8, dino_reverse[i % 2]);

    }
    terrazzo_draw_at(0, 0, 7, 6, dino_bg[i % 10]);
}

#   endif
#endif