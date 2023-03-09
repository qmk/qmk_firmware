/*
Copyright 2020 Nidzo Tomic <tomicn8@hotmail.com>
Copyright 2022 an_achronism <87213873+an-achronism@users.noreply.github.com>

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

/* define if matrix has ghost */
#define MATRIX_HAS_GHOST

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* redefine available (emulated) EEPROM as 4 kB rather than the default 2 kB to let VIA use more of the on-chip Flash of the STM32F303 to store 4 layers (since 4 layers * 8 rows * 16 columns * 2 = 1024 bytes but the default max available is 1023 bytes due to ATMEGA32U4 etc. only having 1 kB of EEPROM) */
#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048
