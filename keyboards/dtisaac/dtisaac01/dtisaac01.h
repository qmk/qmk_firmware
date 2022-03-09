/* Copyright 2021 DTIsaac
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

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K058, K061, K062, K063, K064, K065, K066, \
	K010, K011, K012, K013, K014, K015, K016, K017, K018, K068, K060, K071, K072, K073, K074, K075, K076, \
	K020, K021, K022, K023, K024, K025, K026, K027, K028, K078, K070, K081, K082, K083, K084, K085, K086, \
	K030, K031, K032, K033, K034, K035, K036, K037, K038, K088, K080, K091,       K093, \
	K040,       K042, K043, K044, K045, K046, K047, K048, K098, K090, K101,       K103,       K105, \
	K050, K051, K052,                   K056,       			K100, K111, K112, K113, K114, K115, K116 \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008 }, \
	{ K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018 }, \
	{ K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028 }, \
	{ K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038 }, \
	{ K040,  KC_NO, K042,  K043,  K044,  K045,  K046,  K047,  K048 }, \
	{ K050,  K051,  K052,  KC_NO, KC_NO, KC_NO, K056,  KC_NO, K058 }, \
	{ K060,  K061,  K062,  K063,  K064,  K065,  K066,  KC_NO, K068 }, \
	{ K070,  K071,  K072,  K073,  K074,  K075,  K076,  KC_NO, K078 }, \
	{ K080,  K081,  K082,  K083,  K084,  K085,  K086,  KC_NO, K088 }, \
	{ K090,  K091,  KC_NO, K093,  KC_NO, KC_NO, KC_NO, KC_NO, K098 }, \
	{ K100,  K101,  KC_NO, K103,  KC_NO, K105,  KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, K111,  K112,  K113,  K114,  K115,  K116,  KC_NO, KC_NO }  \
}
