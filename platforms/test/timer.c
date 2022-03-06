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

static uint32_t current_time = 0;

void timer_init(void) {
    current_time = 0;
}

void timer_clear(void) {
    current_time = 0;
}

uint16_t timer_read(void) {
    return current_time & 0xFFFF;
}
uint32_t timer_read32(void) {
    return current_time;
}
uint16_t timer_elapsed(uint16_t last) {
    return TIMER_DIFF_16(timer_read(), last);
}
uint32_t timer_elapsed32(uint32_t last) {
    return TIMER_DIFF_32(timer_read32(), last);
}

void set_time(uint32_t t) {
    current_time = t;
}
void advance_time(uint32_t ms) {
    current_time += ms;
}

void wait_ms(uint32_t ms) {
    advance_time(ms);
}
