/* Copyright 2023 Jack Humbert <jack.humb@gmail.com>
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

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
    {{5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}},
    {{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
    {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},

    {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
    {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7}},
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {0};
#    endif
#endif

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = {
    {36, 37, 38, 39, 40, 41},
    {24, 25, 26, 27, 28, 29},
    {12, 13, 14, 15, 16, 17},
    { 0,  1,  2,  9, 10, 11},
    {42, 43, 44, 45, 46, 47},
    {30, 31, 32, 33, 34, 35},
    {18, 19, 20, 21, 22, 23},
    { 6,  7,  8,  3,  4,  5}
};
