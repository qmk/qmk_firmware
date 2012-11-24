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

// bit population - return number of on-bit
uint8_t bitpop(uint8_t bits)
{
    uint8_t c;
    for (c = 0; bits; c++)
        bits &= bits - 1;
    return c;
/*
    const uint8_t bit_count[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
    return bit_count[bits>>4] + bit_count[bits&0x0F]
*/
}

uint8_t bitpop16(uint16_t bits)
{
    uint8_t c;
    for (c = 0; bits; c++)
        bits &= bits - 1;
    return c;
}

// most significant on-bit - return highest location of on-bit
uint8_t biton(uint8_t bits)
{
    uint8_t n = 0;
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    return n;
}
