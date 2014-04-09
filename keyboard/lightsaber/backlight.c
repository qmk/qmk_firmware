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
 * Alphas    PB1 (high)
 * Numeric   PB2 (high)
 * Mod+Num   PB3 (high)
 * Backside  PD6 (high)
 * TopRight  PD7 (low)
 * F-Row     PE6 (high)
 */

void backlight_set(uint8_t level)
{
    // Set as output.
    DDRB |= (1<<1) | (1<<2) | (1<<3);
    DDRD |= (1<<6) | (1<<7);
    DDRE |= (1<<6);

    if (level & BACKLIGHT_ALPHA)
    {
        PORTB |= (1<<1);
    }
    else
    {
        PORTB &= ~(1<<1);
    }
    if (level & BACKLIGHT_NUMERIC)
    {
        PORTB |= (1<<2);
    }
    else
    {
        PORTB &= ~(1<<2);
    }
    if (level & BACKLIGHT_MODNUM)
    {
        PORTB |= (1<<3);
    }
    else
    {
        PORTB &= ~(1<<3);
    }
    if (level & BACKLIGHT_BACKSIDE)
    {
        PORTD |= (1<<6);
    }
    else
    {
        PORTD &= ~(1<<6);
    }
    if (level & BACKLIGHT_TOPRIGHT)
    {
        PORTD &= ~(1<<7);
    }
    else
    {
        PORTD |= (1<<7);
    }
    if (level & BACKLIGHT_FROW)
    {
        PORTE |= (1<<6);
    }
    else
    {
        PORTE &= ~(1<<6);
    }
}
