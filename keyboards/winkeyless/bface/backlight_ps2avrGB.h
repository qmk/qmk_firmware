/* Copyright 2017 Sebastian Kaim
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


#if defined(__AVR__)
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#include <stddef.h>
#include <stdlib.h>
#include "backlight.h"

#ifndef PS2AVRGB_BACKLIGHT_H
#define PS2AVRGB_BACKLIGHT_H

uint8_t get_pwm_for_brightness(uint8_t level);
void set_backlight_pwm(uint8_t level);
void backlight_on(void);
void backlight_off(void);

#endif
