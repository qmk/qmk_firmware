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

#define TIMER_DIFF(a, b) ((a) >= (b) ?  (a) - (b) : UINT16_MAX - (b) + (a))


extern volatile uint16_t timer_count;


void timer_init(void);
void timer_clear(void);
uint16_t timer_read(void);
uint16_t timer_elapsed(uint16_t last);

#endif
