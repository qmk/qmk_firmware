/*
Copyright 2021 Bryan Ong

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

#pragma once

#include "quantum.h"

#define LAYOUT_all LAYOUT_ava_split_bs

#define LAYOUT_ava_split_bs( \
	K020,   K000, K001, K002, K003, K004, K005, K006,       K010, K011, K012, K013, K014, K015, K016, K017, \
	K040,   K021,       K022, K023, K024, K025, K026,       K030, K031, K032, K033, K034, K035, K036, K037, \
	K060,   K041,       K042, K043, K044, K045, K046,       K050, K051, K052, K053, K054, K055,       K056, \
	K007,   K061,       K062, K063, K064, K065, K066,       K070, K071, K072, K073, K074, K075, K076, K077, \
	        K027, K047,             K057, K067,                   K081, K083,             K085, K086, K087  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007 }, \
	{ K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017 }, \
	{ K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027 }, \
	{ K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037 }, \
	{ K040,  K041,  K042,  K043,  K044,  K045,  K046,  K047 }, \
	{ K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057 }, \
	{ K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067	}, \
	{ K070,  K071,  K072,  K073,  K074,  K075,  K076,  K077 }, \
	{ KC_NO, K081,  KC_NO, K083,  KC_NO, K085,  K086,  K087 }  \
}

#define LAYOUT_ava( \
	K020,   K000, K001, K002, K003, K004, K005, K006,       K010, K011, K012, K013, K014, K015,       K017, \
	K040,   K021,       K022, K023, K024, K025, K026,       K030, K031, K032, K033, K034, K035, K036, K037, \
	K060,   K041,       K042, K043, K044, K045, K046,       K050, K051, K052, K053, K054, K055,       K056, \
	K007,   K061,       K062, K063, K064, K065, K066,       K070, K071, K072, K073, K074, K075, K076, K077, \
	        K027, K047,             K057, K067,                   K081, K083,             K085, K086, K087  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007 }, \
	{ K010,  K011,  K012,  K013,  K014,  K015,  KC_NO, K017 }, \
	{ K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027 }, \
	{ K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037 }, \
	{ K040,  K041,  K042,  K043,  K044,  K045,  K046,  K047 }, \
	{ K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057 }, \
	{ K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067	}, \
	{ K070,  K071,  K072,  K073,  K074,  K075,  K076,  K077 }, \
	{ KC_NO, K081,  KC_NO, K083,  KC_NO, K085,  K086,  K087 }  \
}

