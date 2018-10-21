/* Copyright 2018 Jumail Mundekkat
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
#ifndef PRIME_O_H
#define PRIME_O_H

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K010, K011, K012, K013, K014, K015, K016, K017, \
	K020, K021, K022, K023, K024, K025, K026, K027, K030, K031, K032, K033, K034, K035, K036, K037, \
	K040, K041, K042, K043, K044, K045, K046, K047, K050, K051, K052, K053, K054, K055, K056, K057, \
	K060, K061, K062, K063, K064, K065, K066, K067, K070, K071, K072, K073, K074, K075, K076, K077, \
	K080, K081, K082, K083, K084, K085, K086, K087, K090, K091, K092, K093, K094, K095, K096, K097  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007 }, \
	{ K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017 }, \
	{ K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027 }, \
	{ K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037 }, \
	{ K040,  K041,  K042,  K043,  K044,  K045,  K046,  K047 }, \
	{ K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057 }, \
	{ K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067 }, \
	{ K070,  K071,  K072,  K073,  K074,  K075,  K076,  K077 }, \
	{ K080,  K081,  K082,  K083,  K084,  K085,  K086,  K087 }, \
	{ K090,  K091,  K092,  K093,  K094,  K095,  K096,  K097 }  \
}

#endif
