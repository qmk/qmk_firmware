/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include "quantum.h"

#define LED_ON()    do { DDRC |= (1<<5); PORTC |= (1<<5); } while (0)
#define LED_OFF()   do { DDRC &= ~(1<<5); PORTC &= ~(1<<5); } while (0)
#define LED_TGL()   do { DDRC |= (1<<5); PINC |= (1<<5); } while (0)


void matrix_init_kb(void) {
    LED_ON();
    _delay_ms(500);
    LED_OFF();
    
    matrix_init_user();
}