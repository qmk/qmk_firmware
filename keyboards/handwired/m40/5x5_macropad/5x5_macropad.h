// Copyright 2022 Tomek (@m40-dev)
// SPDX-License-Identifier: GPL-2.0-or-later

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
#define LAYOUT_ortho_5x5( \
	K000, K001, K002, K003, K004, \
	K100, K101, K102, K103, K104, \
	K200, K201, K202, K203, K204, \
	K300, K301, K302, K303, K304, \
	K400, K401, K402, K403, K404 ) { \
	{ K000,  K001,  K002,  K003, K004 }, \
	{ K100,  K101,  K102,  K103, K104 }, \
	{ K200,  K201,  K202,  K203, K204 }, \
	{ K300,  K301,  K302,  K303, K304 }, \
	{ K400,  K401,  K402,  K403, K404 } \
}
