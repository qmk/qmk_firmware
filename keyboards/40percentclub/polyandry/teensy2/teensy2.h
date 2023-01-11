/* Copyright 2021
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

//NOTE TO FUTURE FROM RYJELSUM (original contributor):
//This has been unchanged from the promicro.h file. 
//I DO NOT HAVE A TEENSY 2.0 TO TEST WITH.
//I believe this should still work - but it's not a sure thing.

#include "polyandry.h"

#define LAYOUT_ortho_4x3( \
	K000, K001, K002, \
 	K003, K004, K005, \
	K006, K007, K008, \
	K009, K010, K011  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011 }  \
}
