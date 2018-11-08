/* Copyright 2018
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
#define ________ KC_NO

#ifndef FLIP_HALF
#define LAYOUT_split( \
	L00, L01, L02, R00, R01, R02, \
	L10, L11, L12, R10, R11, R12  \
) { \
	{ L00, L01, L02 }, \
	{ L10, L11, L12 }, \
	{ R02, R01, R00 }, \
	{ R12, R11, R10 }, \
}
#else
#define LAYOUT_split( \
	L00, L01, L02, R00, R01, R02, \
	L10, L11, L12, R10, R11, R12  \
) { \
	{ L00, L01, L02 }, \
	{ L10, L11, L12 }, \
	{ R00, R01, R02 }, \
	{ R10, R11, R12 }, \
}
#endif

#define LAYOUT_macro( \
	L00, L01, L02, \
	L10, L11, L12  \
) { \
	{ L00, L01, L02 }, \
	{ L10, L11, L12 }, \
}

#define LAYOUT LAYOUT_macro

#ifdef USE_I2C
  #error "I2C not Supported"
#endif
