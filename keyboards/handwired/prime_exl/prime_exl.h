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
#ifndef PRIME_EXL_H
#define PRIME_EXL_H

#include "quantum.h"

#define LAYOUT( \
	K040, K050, K041, K051, K042, K052, 		K043, K053, K044, K054, K045, K055, 		K046, K056, K047, K057, K048, K058, \
	K030, K060, K031, K061, K032, K062,		K033, K063, K034, K064, K035, K065, 		K036, K066, K037, K067, K038, K068, \
	K020, K070, K021, K071, K022, K072,		K023, K073, K024, K074, K025, K075, 		K085, K026, K076, K027, K077, K028, K078, \
	K010, K080, K011, K081, K012, K082,		K013, K083, K014, K084,    	K015,					K016,		  K086, K017, K087, K018, \
	K000, K090, K001, K091, K002, K092 \
) { \
	{ K000,  K001,  K002,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018 }, \
	{ K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028 }, \
	{ K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038 }, \
	{ K040,  K041,  K042,  K043,  K044,  K045,  K046,  K047,  K048 }, \
	{ K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057,  K058 }, \
	{ K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  K068 }, \
	{ K070,  K071,  K072,  K073,  K074,  K075,  K076,  K077,  K078 }, \
	{ K080,  K081,  K082,  K083,  K084,  K085,  K086,  K087,  KC_NO }, \
	{ K090,  K091,  K092,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}

#endif