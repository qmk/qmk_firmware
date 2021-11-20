/* Copyright 2021 Christoph Rehmann (crehmann)
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

#pragma once

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

// Using the right side as master
#define MASTER_RIGHT

#ifdef HAPTIC_ENABLE
//#define NO_HAPTIC_MOD
#define NO_HAPTIC_FN
#define NO_HAPTIC_ALPHA
#define NO_HAPTIC_PUNCTUATION
#define NO_HAPTIC_NAV 
#define NO_HAPTIC_NUMERIC
#define DRV_GREETING       alert_750ms
#define DRV_MODE_DEFAULT   sharp_tick1
#endif

#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTE
#define PS2_CLOCK_PIN   PINE
#define PS2_CLOCK_DDR   DDRE
#define PS2_CLOCK_BIT   6
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    7
#define PS2_INT_INIT()  do { EICRB |= ((1<<ISC61) | (0<<ISC60)); } while (0)
#define PS2_INT_ON()  do { EIMSK |= (1<<INT6); } while (0)
#define PS2_INT_OFF() do { EIMSK &= ~(1<<INT6);} while (0)
#define PS2_INT_VECT   INT6_vect
#endif
