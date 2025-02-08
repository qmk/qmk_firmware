/* Copyright 2021 Takeshi Nishio
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
    { 0, 37, 33,  0, 27, 31, 30, 35, 25,  0},
    {17,  0, 21,  0, 15, 19, 18, 23, 13,  0},
    {17,  0,  0, 21, 15, 19, 18, 23, 13,  0},
    { 4, 12,  8,  0,  2,  6,  5, 10,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {28, 36, 32, 34, 26,  0, 29,  0,  0, 24},
    {16, 24, 20, 22, 14,  0,  0,  0,  0, 12},
    {16, 24, 20, 22, 14,  0,  0,  0,  0, 12},
    { 3, 11,  7,  9,  1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};
#endif
