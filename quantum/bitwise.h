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

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t bitpop(uint8_t bits);
uint8_t bitpop16(uint16_t bits);
uint8_t bitpop32(uint32_t bits);

uint8_t biton(uint8_t bits);
uint8_t biton16(uint16_t bits);
uint8_t biton32(uint32_t bits);

uint8_t  bitrev(uint8_t bits);
uint16_t bitrev16(uint16_t bits);
uint32_t bitrev32(uint32_t bits);

#ifdef __cplusplus
}
#endif
