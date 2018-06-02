/*
Copyright 2016 Daniel Svensson <dsvensson@gmail.com>

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

#ifndef PEGASUSHOOF_H
#define PEGASUSHOOF_H

#include "matrix.h"
#include "quantum.h"

#define  ___ KC_NO

#define KEYMAP( \
	KG6,      KH4, KI4, KI2, KI6, KP5, KL6, KM2, KM4, KO4, KO5, KO6, KO0,   KN5, KN7, KP7, \
	KG4, KG5, KH5, KI5, KJ5, KJ4, KK4, KK5, KL5, KM5, KF5, KF4, KL4, KO2,   KR4, KC4, KE4, \
	KG2, KG7, KH7, KI7, KJ7, KJ2, KK2, KK7, KL7, KM7, KF7, KF2, KL2, KO3,   KQ4, KC5, KE5, \
	KH2, KG3, KH3, KI3, KJ3, KJ6, KK6, KK3, KL3, KM3, KF3, KF6,      KO1,                  \
	KB2, KH6, KG1, KH1, KI1, KJ1, KJ0, KK0, KK1, KL1, KM1, KF0,      KB3,        KC6,      \
	KP4, KD2, KN6,                KQ6,                KN0, KA3, KM0, KP1,   KC0, KQ0, KR0  \
	) { /*        00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
		/* 0 */  { ___ , ___ , KC0 , ___ , ___ , KF0 , ___ , ___ , ___ , KJ0 , KK0 , ___ , KM0 , KN0 , KO0 , ___ , KQ0 , KR0 }, \
		/* 1 */  { ___ , ___ , ___ , ___ , ___ , ___ , KG1 , KH1 , KI1 , KJ1 , KK1 , KL1 , KM1 , ___ , KO1 , KP1 , ___ , ___ }, \
		/* 2 */  { ___ , KB2 , ___ , KD2 , ___ , KF2 , KG2 , KH2 , KI2 , KJ2 , KK2 , KL2 , KM2 , ___ , KO2 , ___ , ___ , ___ }, \
		/* 3 */  { KA3 , KB3 , ___ , ___ , ___ , KF3 , KG3 , KH3 , KI3 , KJ3 , KK3 , KL3 , KM3 , ___ , KO3 , ___ , ___ , ___ }, \
		/* 4 */  { ___ , ___ , KC4 , ___ , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , KM4 , ___ , KO4 , KP4 , KQ4 , KR4 }, \
		/* 5 */  { ___ , ___ , KC5 , ___ , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , KK5 , KL5 , KM5 , KN5 , KO5 , KP5 , ___ , ___ }, \
		/* 6 */  { ___ , ___ , KC6 , ___ , ___ , KF6 , KG6 , KH6 , KI6 , KJ6 , KK6 , KL6 , ___ , KN6 , KO6 , ___ , KQ6 , ___ }, \
		/* 7 */  { ___ , ___ , ___ , ___ , ___ , KF7 , KG7 , KH7 , KI7 , KJ7 , KK7 , KL7 , KM7 , KN7 , ___ , KP7 , ___ , ___ }, \
	}

inline void ph_caps_led_on(void)  { DDRC |=  (1<<6); PORTC &= ~(1<<6); }
inline void ph_caps_led_off(void) { DDRC &= ~(1<<6); PORTC &= ~(1<<6); }

inline void ph_sclk_led_on(void)  { DDRC |=  (1<<5); PORTC &= ~(1<<5); }
inline void ph_sclk_led_off(void) { DDRC &= ~(1<<5); PORTC &= ~(1<<5); }


#endif
