// Copyright 2023 Laneware Peripherals
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* ┌───┐
 * │000│ ┌───┐
 * ├───┤ │001│
 * │100│ └───┘
 * ├───┼───┬───┐
 * │200│201│202│
 * └───┴───┴───┘
 */

#define LAYOUT_default( 
	K000, K001, \
	K100, \
	K200, K201, K202 \
) { \
	{ K000,  K001}, \
	{ K100}, \
	{ K200,  K201,  K202} \
}
