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

#ifndef DISABLE_TERRAZZO_EFFECT_PAC_DUDE
TERRAZZO_EFFECT(PAC_DUDE)
#   ifdef TERRAZZO_EFFECT_IMPLS

static uint8_t pac_frames[3][25] = {
{ // up
    0, 0, 0, 0, 0,
    9, 0, 0, 0, 9,
    9, 9, 0, 9, 9,
    9, 9, 9, 9, 9,
    0, 9, 9, 9, 0
},
{ // closed
    0, 9, 9, 9, 0,
    9, 9, 9, 9, 9,
    9, 9, 9, 9, 9,
    9, 9, 9, 9, 9,
    0, 9, 9, 9, 0
},
{ // down
    0, 9, 9, 9, 0,
    9, 9, 9, 9, 9,
    9, 9, 0, 9, 9,
    9, 0, 0, 0, 9,
    0, 0, 0, 0, 0
}
};

static uint8_t pac_ghost[20] = {
    0, 4, 4, 4, 0,
    4, 0, 4, 0, 4,
    4, 4, 4, 4, 4,
    4, 0, 4, 0, 4
};


void PAC_DUDE(uint8_t i, bool dir) {
    led_matrix_set_index_value_all(0);
    if (dir) {
        terrazzo_draw_at(1, 4, 5, 5, pac_frames[i % 2]);
        terrazzo_set_pixel(3, 0 + i % 3, 5);
        terrazzo_set_pixel(3, 3 + i % 3, 5);
    } else {
        terrazzo_draw_at(1, 4, 5, 5, pac_frames[1 + i % 2]);
        terrazzo_draw_at(1, 8 + i % 8, 5, 4, pac_ghost);
    }
    
}

#   endif
#endif