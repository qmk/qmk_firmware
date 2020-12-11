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
__attribute__((noinline)) uint8_t bitpop(uint8_t bits) {
    uint8_t c;
    for (c = 0; bits; c++) bits &= bits - 1;
    return c;
    /*
        const uint8_t bit_count[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
        return bit_count[bits>>4] + bit_count[bits&0x0F]
    */
}

uint8_t bitpop16(uint16_t bits) {
    uint8_t c;
    for (c = 0; bits; c++) bits &= bits - 1;
    return c;
}

uint8_t bitpop32(uint32_t bits) {
    uint8_t c;
    for (c = 0; bits; c++) bits &= bits - 1;
    return c;
}

// most significant on-bit - return highest location of on-bit
// NOTE: return 0 when bit0 is on or all bits are off
__attribute__((noinline)) uint8_t biton(uint8_t bits) {
    uint8_t n = 0;
    if (bits >> 4) {
        bits >>= 4;
        n += 4;
    }
    if (bits >> 2) {
        bits >>= 2;
        n += 2;
    }
    if (bits >> 1) {
        bits >>= 1;
        n += 1;
    }
    return n;
}

uint8_t biton16(uint16_t bits) {
    uint8_t n = 0;
    if (bits >> 8) {
        bits >>= 8;
        n += 8;
    }
    if (bits >> 4) {
        bits >>= 4;
        n += 4;
    }
    if (bits >> 2) {
        bits >>= 2;
        n += 2;
    }
    if (bits >> 1) {
        bits >>= 1;
        n += 1;
    }
    return n;
}

uint8_t biton32(uint32_t bits) {
    uint8_t n = 0;
    if (bits >> 16) {
        bits >>= 16;
        n += 16;
    }
    if (bits >> 8) {
        bits >>= 8;
        n += 8;
    }
    if (bits >> 4) {
        bits >>= 4;
        n += 4;
    }
    if (bits >> 2) {
        bits >>= 2;
        n += 2;
    }
    if (bits >> 1) {
        bits >>= 1;
        n += 1;
    }
    return n;
}

__attribute__((noinline)) uint8_t bitrev(uint8_t bits) {
    bits = (bits & 0x0f) << 4 | (bits & 0xf0) >> 4;
    bits = (bits & 0b00110011) << 2 | (bits & 0b11001100) >> 2;
    bits = (bits & 0b01010101) << 1 | (bits & 0b10101010) >> 1;
    return bits;
}

uint16_t bitrev16(uint16_t bits) {
    bits = bitrev(bits & 0x00ff) << 8 | bitrev((bits & 0xff00) >> 8);
    return bits;
}

uint32_t bitrev32(uint32_t bits) {
    bits = (uint32_t)bitrev16(bits & 0x0000ffff) << 16 | bitrev16((bits & 0xffff0000) >> 16);
    return bits;
}
