/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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
#include "backlight.h"

/* Backlight pin configuration
 *
 * FN1       PB0 (low)
 * FN2       PB5 (low)
 * FN3       PB4 (low)
 * FN4       PD7 (low)
 * REAR      PD6 (high)
 * NUMPAD    PB2 (high)
 * NUMLOCK   PB1 (low)
 */
void backlight_init_ports() {
    DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<4) | (1<<5);
    DDRD |= (1<<6) | (1<<7);

    backlight_disable_numlock();
}

void backlight_set(uint8_t level) {
    (level & BACKLIGHT_FN1) ? backlight_enable_fn1() : backlight_disable_fn1();
    (level & BACKLIGHT_FN2) ? backlight_enable_fn2() : backlight_disable_fn2();
    (level & BACKLIGHT_FN3) ? backlight_enable_fn3() : backlight_disable_fn3();
    (level & BACKLIGHT_FN4) ? backlight_enable_fn4() : backlight_disable_fn4();
    (level & BACKLIGHT_NUMPAD) ? backlight_enable_numpad() : backlight_disable_numpad();
    (level & BACKLIGHT_REAR) ? backlight_enable_rear() : backlight_disable_rear();
}

void backlight_enable_fn1() {
    PORTB &= ~(1<<0);
}

void backlight_disable_fn1() {
    PORTB |= (1<<0);
}

void backlight_invert_fn1() {
    PORTB ^= (1<<0);
}

void backlight_enable_fn2() {
    PORTB &= ~(1<<5);
}

void backlight_disable_fn2() {
    PORTB |= (1<<5);
}

void backlight_invert_fn2() {
    PORTB ^= (1<<5);
}

void backlight_enable_fn3() {
    PORTB &= ~(1<<4);
}

void backlight_disable_fn3() {
    PORTB |= (1<<4);
}

void backlight_invert_fn3() {
    PORTB ^= (1<<4);
}

void backlight_enable_fn4() {
    PORTD &= ~(1<<7);
}

void backlight_disable_fn4() {
    PORTD |= (1<<7);
}

void backlight_invert_fn4() {
    PORTD ^= (1<<7);
}

void backlight_enable_numpad() {
    PORTB |= (1<<2);
}

void backlight_disable_numpad() {
    PORTB &= ~(1<<2);
}

void backlight_invert_numpad() {
    PORTB ^= (1<<2);
}

void backlight_enable_numlock() {
    PORTB &= ~(1<<1);
}

void backlight_disable_numlock() {
    PORTB |= (1<<1);
}

void backlight_invert_numlock() {
    PORTB ^= (1<<1);
}

void backlight_enable_rear() {
    PORTD |= (1<<6);
}

void backlight_disable_rear() {
    PORTD &= ~(1<<6);
}

void backlight_invert_rear() {
    PORTD ^= (1<<6);
}
