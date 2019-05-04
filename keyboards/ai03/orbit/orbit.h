/* Copyright 2018 Ryota Goto
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
#ifndef ORBIT_H
#define ORBIT_H

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
 
#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif


#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, \
	L10, L11, L12, L13, L14, L15, L16, R10, R11, R12, R13, R14, R15, R16, \
	L20, L21, L22, L23, L24, L25, L26, R20, R21, R22, R23, R24, R25, R26, \
	L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, \
         L41, L42, L43, L44, L45, L46, R40, R41, R42, R43, R44, R45 \
) \
{ \
	{ L00,   L01,   L02,   L03,   L04,   L05,   L06 }, \
	{ L10,   L11,   L12,   L13,   L14,   L15,   L16 }, \
	{ L20,   L21,   L22,   L23,   L24,   L25,   L26 }, \
	{ L30,   L31,   L32,   L33,   L34,   L35,   L36 }, \
	{ KC_NO, L41,   L42,   L43,   L44,   L45,   L46 }, \
	{ R00,   R01,   R02,   R03,   R04,   R05,   R06 }, \
	{ R10,   R11,   R12,   R13,   R14,   R15,   R16 }, \
	{ R20,   R21,   R22,   R23,   R24,   R25,   R26 }, \
	{ R30,   R31,   R32,   R33,   R34,   R35,   R36 }, \
	{ R40,   R41,   R42,   R43,   R44,   R45, KC_NO }  \
}

uint8_t current_layer;

extern void led_toggle(int id, bool on);
void set_all_leds(bool leds[6]);
extern void set_layer_indicators(uint8_t layer);

#endif
