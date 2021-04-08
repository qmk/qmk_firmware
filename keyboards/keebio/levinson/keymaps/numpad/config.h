/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 Danny Nguyen <danny@keeb.io>

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

// #define USE_I2C
// Need to flip the rows
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6 }

/* Select hand configuration */
// #define MASTER_RIGHT
// #define EE_HANDS

/* Time in ms until oneshot layer times out */
#define ONESHOT_TIMEOUT 3000
