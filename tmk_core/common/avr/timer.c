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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include "timer_avr.h"
#include "timer.h"


// counter resolution 1ms
// NOTE: union { uint32_t timer32; struct { uint16_t dummy; uint16_t timer16; }}
volatile uint32_t timer_count;

void timer_init(void)
{
#if TIMER_PRESCALER == 1
    uint8_t prescaler = 0x01;
#elif TIMER_PRESCALER == 8
    uint8_t prescaler = 0x02;
#elif TIMER_PRESCALER == 64
    uint8_t prescaler = 0x03;
#elif TIMER_PRESCALER == 256
    uint8_t prescaler = 0x04;
#elif TIMER_PRESCALER == 1024
    uint8_t prescaler = 0x05;
#else
#   error "Timer prescaler value is NOT vaild."
#endif

#ifndef __AVR_ATmega32A__
    // Timer0 CTC mode
    TCCR0A = 0x02;

    TCCR0B = prescaler;

    OCR0A = TIMER_RAW_TOP;
    TIMSK0 = (1<<OCIE0A);
#else
    // Timer0 CTC mode
    TCCR0 = (1 << WGM01) | prescaler;

    OCR0 = TIMER_RAW_TOP;
    TIMSK = (1 << OCIE0);
#endif
}

inline
void timer_clear(void)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    timer_count = 0;
  }
}

inline
uint16_t timer_read(void)
{
    uint32_t t;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      t = timer_count;
    }

    return (t & 0xFFFF);
}

inline
uint32_t timer_read32(void)
{
    uint32_t t;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      t = timer_count;
    }

    return t;
}

inline
uint16_t timer_elapsed(uint16_t last)
{
    uint32_t t;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      t = timer_count;
    }

    return TIMER_DIFF_16((t & 0xFFFF), last);
}

inline
uint32_t timer_elapsed32(uint32_t last)
{
    uint32_t t;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      t = timer_count;
    }

    return TIMER_DIFF_32(t, last);
}

// excecuted once per 1ms.(excess for just timer count?)
#ifndef __AVR_ATmega32A__
#define TIMER_INTERRUPT_VECTOR TIMER0_COMPA_vect
#else
#define TIMER_INTERRUPT_VECTOR TIMER0_COMP_vect
#endif
ISR(TIMER_INTERRUPT_VECTOR, ISR_NOBLOCK)
{
    timer_count++;
}
