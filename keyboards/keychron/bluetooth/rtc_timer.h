/* Copyright 2023 @ lokher (https://www.keychron.com)
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

#pragma once

#include "timer.h"
#include <stdint.h>

#define RTC_MAX_TIME (24 * 3600 * 1000) // Set to 1 day

#if 0
#    define TIMER_DIFF(a, b, max) ((max == UINT8_MAX) ? ((uint8_t)((a) - (b))) : ((max == UINT16_MAX) ? ((uint16_t)((a) - (b))) : ((max == UINT32_MAX) ? ((uint32_t)((a) - (b))) : ((a) >= (b) ? (a) - (b) : (max) + 1 - (b) + (a)))))
#    define TIMER_DIFF_8(a, b) TIMER_DIFF(a, b, UINT8_MAX)
#    define TIMER_DIFF_16(a, b) TIMER_DIFF(a, b, UINT16_MAX)
#    define TIMER_DIFF_32(a, b) TIMER_DIFF(a, b, UINT32_MAX)
#    define TIMER_DIFF_RAW(a, b) TIMER_DIFF_8(a, b)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void     rtc_timer_init(void);
void     rtc_timer_clear(void);
uint32_t rtc_timer_read_ms(void);
uint32_t rtc_timer_elapsed_ms(uint32_t last);

#ifdef __cplusplus
}
#endif
