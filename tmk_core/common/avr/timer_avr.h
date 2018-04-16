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

#ifndef TIMER_AVR_H
#define TIMER_AVR_H 1

#include <stdint.h>

#ifndef TIMER_PRESCALER
#   if F_CPU > 16000000
#       define TIMER_PRESCALER      256
#   elif F_CPU > 2000000
#       define TIMER_PRESCALER      64
#   elif F_CPU > 250000
#       define TIMER_PRESCALER      8
#   else
#       define TIMER_PRESCALER      1
#   endif
#endif
#define TIMER_RAW_FREQ      (F_CPU/TIMER_PRESCALER)
#define TIMER_RAW           TCNT0
#define TIMER_RAW_TOP       (TIMER_RAW_FREQ/1000)

#if (TIMER_RAW_TOP > 255)
#   error "Timer0 can't count 1ms at this clock freq. Use larger prescaler."
#endif

#endif
