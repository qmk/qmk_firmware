/*
 * (C) 2020 Sadao Ikebe @bonyarou
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
#include QMK_KEYBOARD_H
#include "key_duration.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

static keypress_timer_expired_func_t callback;

void keypress_timer_init(keypress_timer_expired_func_t _clbk) {
    cli();
    callback = _clbk;
  TCCR1A = 0; // 0b00000000  - TOP is 0xFFFF
    TCCR1B = (1<< CS12) | (1<< CS10); // clock /1024
  TCCR1C = 0; // not forcing output compare
    TCNT1 = 0; // set timer counter initial value (16 bit value)
    OCR1A = 0xffff;
  sei(); // enable interrupts
}

void keypress_timer_start(uint16_t count) {
    cli();
  TCNT1 = 0; // set timer counter initial value (16 bit value)
    OCR1A = count;
  TIMSK1 = 2; // enable timer compare match 1A interrupt
  sei(); // enable interrupts
}

ISR(TIMER1_COMPA_vect) // 16 bit timer 1 compare 1A match
{
    callback();
}
