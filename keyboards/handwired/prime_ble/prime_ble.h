/* Copyright 2018 Holten Campbell
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
//#ifndef PRIME_EXL_H
//#define PRIME_EXL_H


#include "quantum.h"

#define LAYOUT( \
	K030, K040, K031, K041, 	K032, K042, K033, K043, K034, K044, 		K035, K045, K036, K046, K037, K047, K038,\
	K020, K050, K021, K051,		K022, K052, K023, K053, K024, K054, 		K025, K055, K026, K056, K027, 		K058, \
	K010, K060, K011, K061,		K012, K062, K013, K063, K014, K064, 		K015, K065, K016, K066, K017, K067, K018, \
	K000, K070, K001, K071,		K002, K072, K003, 			  K074,			K005,		  			K076, K007, K078 \
) { \
	{ K000,  K001,  K002,  K003,  KC_NO, K005,  KC_NO, K007,  KC_NO }, \
	{ K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018  }, \
	{ K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  KC_NO }, \
	{ K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038 }, \
	{ K040,  K041,  K042,  K043,  K044,  K045,  K046,  K047,  KC_NO }, \
	{ K050,  K051,  K052,  K053,  K054,  K055,  K056,  KC_NO, K058 }, \
	{ K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  KC_NO }, \
	{ K070,  K071,  K072,  KC_NO, K074,  KC_NO, K076,  KC_NO, K078 } \
}

//#endif