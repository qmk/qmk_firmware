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

#ifndef TIMER_H
#define TIMER_H 1

#include <stdint.h>
#include <stdbool.h>

#if defined(__AVR__)
#    include "avr/timer_avr.h"
#endif

#define TIMER_DIFF(a, b, max) ((max == UINT8_MAX) ? ((uint8_t)((a)-(b))) : ( \
                               (max == UINT16_MAX) ? ((uint16_t)((a)-(b))) : ( \
                               (max == UINT32_MAX) ? ((uint32_t)((a)-(b))) : ( \
                               (a) >= (b) ? (a) - (b) : (max) + 1 - (b) + (a) ))))
#define TIMER_DIFF_8(a, b) TIMER_DIFF(a, b, UINT8_MAX)
#define TIMER_DIFF_16(a, b) TIMER_DIFF(a, b, UINT16_MAX)
#define TIMER_DIFF_32(a, b) TIMER_DIFF(a, b, UINT32_MAX)
#define TIMER_DIFF_RAW(a, b) TIMER_DIFF_8(a, b)

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t timer_count;

void     timer_init(void);
void     timer_clear(void);
uint16_t timer_read(void);
uint32_t timer_read32(void);
uint16_t timer_elapsed(uint16_t last);
uint32_t timer_elapsed32(uint32_t last);

// Utility functions to check if a future time has expired & autmatically handle time wrapping if checked / reset frequently (half of max value)
#define timer_expired(current, future) (((uint16_t)current - (uint16_t)future) < 0x8000)
#define timer_expired32(current, future) (((uint32_t)current - (uint32_t)future) < 0x80000000)

#ifdef __cplusplus
}
#endif

#endif
