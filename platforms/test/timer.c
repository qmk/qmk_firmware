/* Copyright 2017 Fred Sundvik
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

#include "timer.h"
#include <stdatomic.h>

static atomic_uint_least32_t current_time      = 0;
static atomic_uint_least32_t async_tick_amount = 0;
static atomic_uint_least32_t access_counter    = 0;

void simulate_async_tick(uint32_t t) {
    async_tick_amount = t;
}

uint32_t timer_read_internal(void) {
    return current_time;
}

uint32_t current_access_counter(void) {
    return access_counter;
}

void reset_access_counter(void) {
    access_counter = 0;
}

void timer_init(void) {
    current_time      = 0;
    async_tick_amount = 0;
    access_counter    = 0;
}

void timer_clear(void) {
    current_time      = 0;
    async_tick_amount = 0;
    access_counter    = 0;
}

uint16_t timer_read(void) {
    return (uint16_t)timer_read32();
}

uint32_t timer_read32(void) {
    if (access_counter++ > 0) {
        current_time += async_tick_amount;
    }
    return current_time;
}

void set_time(uint32_t t) {
    current_time   = t;
    access_counter = 0;
}

void advance_time(uint32_t ms) {
    current_time += ms;
    access_counter = 0;
}

void wait_ms(uint32_t ms) {
    advance_time(ms);
}
