/* Copyright 2020 Takeshi Nishio
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

#if defined(AUDIO_ENABLE) && defined(MUSIC_MAP)
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = {
    { 0,  0,  0,  0,  0,  0,  0, 64, 65, 66, 67},
    { 0,  0,  0,  0,  0,  0,  0, 49, 50, 51, 52},
    { 0,  0,  0,  0,  0,  0,  0, 35, 36, 37, 38},
    { 0,  0,  0,  0,  0,  0,  0, 21, 22, 23, 24},
    { 0,  0,  0,  0,  0,  0,  0,  8,  9, 10, 11},
    { 0,  0,  0,  0,  0,  0, 59, 60, 61, 62, 63},
    {53, 54, 55, 56, 57, 58,  0, 45, 46, 47, 48},
    {39,  0, 40, 41, 42, 43, 44,  0, 32, 33, 34},
    {25,  0, 26, 27, 28, 29, 30, 31,  0, 19, 20},
    {11,  0, 12, 13, 14, 15, 16, 17, 18,  0,  0},
    { 0,  1,  2,  3,  0,  4,  0,  5,  6,  7,  0}
};
#endif
