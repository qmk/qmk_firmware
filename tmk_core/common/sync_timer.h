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

#ifndef SYNC_TIMER_H
#define SYNC_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"


#ifdef __cplusplus
extern "C" {
#endif

void sync_timer_init(void);
void sync_timer_clear(void);
void sync_timer_update(uint32_t time);
uint16_t sync_timer_read(void);
uint32_t sync_timer_read32(void);
uint16_t sync_timer_elapsed(uint16_t last);
uint32_t sync_timer_elapsed32(uint32_t last);
bool sync_timer_expired(uint16_t future);
bool sync_timer_expired32(uint32_t future);

#ifdef __cplusplus
}
#endif

#endif
