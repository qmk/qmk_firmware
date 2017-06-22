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

// TODO: the timer should work, but at a much faster rate than realtime
// It should also have some kind of integration with the testing system

void timer_init(void) {}

void timer_clear(void) {}

uint16_t timer_read(void) { return 0; }
uint32_t timer_read32(void) { return 0; }
uint16_t timer_elapsed(uint16_t last) { return 0; }
uint32_t timer_elapsed32(uint32_t last) { return 0; }

