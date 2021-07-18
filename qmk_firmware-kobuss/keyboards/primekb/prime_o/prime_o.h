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
	K001, K008, K013, K018, K023, K029, K035, K041, K046, K052, K058, K064, K071, K076, K081, K086, \
	K002, K009, K014, K019, K024, K030, K036, K042, K047, K053, K059, K065, K072, K077, K082, K087, \
	K004, K010, K015, K020, K025, K031, K037, K043, K048, K054, K060, K066, K073, K078, K083, K089, \
	K005, K011, K016, K021, K026, K032, K038, K044, K049, K055, K061, K067, K074, K079, K084, K090, \
	K007, K012, K017, K022, K028, K034, K040, K045, K051, K057, K063, K069, K075, K080, K085, K092  \
) { \
	{ K007,  K017,  K028,  K040,  K051,  K063,  K075,  K085 }, \
	{ K005,  K016,  K026,  K038,  K049,  K061,  K074,  K084 }, \
	{ K004,  K015,  K025,  K037,  K048,  K060,  K073,  K083 }, \
	{ K002,  K014,  K024,  K036,  K047,  K059,  K072,  K082 }, \
	{ K001,  K013,  K023,  K035,  K046,  K058,  K071,  K081 }, \
	{ K008,  K018,  K029,  K041,  K052,  K064,  K076,  K086 }, \
	{ K009,  K019,  K030,  K042,  K053,  K065,  K077,  K087 }, \
	{ K010,  K020,  K031,  K043,  K054,  K066,  K078,  K089 }, \
	{ K011,  K021,  K032,  K044,  K055,  K067,  K079,  K090 }, \
	{ K012,  K022,  K034,  K045,  K057,  K069,  K080,  K092 }  \
}

#endif
