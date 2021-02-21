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
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__) || (__has_builtin(__builtin_popcount) && __has_builtin(__builtin_popcountl))

Q_ALWAYS_INLINE uint8_t bitpop(uint8_t bits) { return (uint8_t)__builtin_popcount(bits); }
Q_ALWAYS_INLINE uint8_t bitpop16(uint16_t bits) { return (uint8_t)__builtin_popcount(bits); }
Q_ALWAYS_INLINE uint8_t bitpop32(uint32_t bits) { return (uint8_t)__builtin_popcountl(bits); }

#else /* __GNUC__ || (__builtin_popcount && __builtin_popcountl) */

uint8_t bitpop(uint8_t bits);
uint8_t bitpop16(uint16_t bits);
uint8_t bitpop32(uint32_t bits);

#endif /* __GNUC__ || (__builtin_popcount && __builtin_popcountl) */

#if defined(__GNUC__) || (__has_builtin(__builtin_clz) && __has_builtin(__builtin_clzl))

Q_ALWAYS_INLINE uint8_t biton(uint8_t bits) { return (uint8_t)(bits ? 7 - __builtin_clz(bits) : 0); }
Q_ALWAYS_INLINE uint8_t biton16(uint16_t bits) { return (uint8_t)(bits ? 15 - __builtin_clz(bits) : 0); }
Q_ALWAYS_INLINE uint8_t biton32(uint32_t bits) { return (uint8_t)(bits ? 31 - __builtin_clzl(bits) : 0); }

#else /* __GNUC__ || (__builtin_clz && __builtin_clzl) */

uint8_t biton(uint8_t bits);
uint8_t biton16(uint16_t bits);
uint8_t biton32(uint32_t bits);

#endif /* __GNUC__ || (__builtin_clz && __builtin_clzl) */

uint8_t  bitrev(uint8_t bits);
uint16_t bitrev16(uint16_t bits);
uint32_t bitrev32(uint32_t bits);

#ifdef __cplusplus
}
#endif
