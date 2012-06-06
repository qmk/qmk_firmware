/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "util.h"

// bit population
int bitpop(uint8_t bits)
{
    int c;
    for (c = 0; bits; c++)
        bits &= bits -1;
    return c;
}

// most significant on-bit
int biton(uint8_t bits)
{
    int n = 0;
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    return n;
}
