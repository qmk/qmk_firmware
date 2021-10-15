/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

// For the COMBO keys function.
#define COMBO_TERM  40  /* time limit in milliseconds combos need to be completed */	
#define COMBO_COUNT 6

#define TAPPING_TOGGLE 2  /* How many times TT(__layer__) needs to be tapped to stick */
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 150
//#define TAPPING_FORCE_HOLD
//#define PERMISSIVE_HOLD