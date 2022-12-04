/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
<<<<<<<< HEAD:keyboards/bastardkb/scylla/v2/splinky_2/config.h
    { GP29, GP26, GP5, GP4, GP9 }
#define MATRIX_COL_PINS \
    { GP27, GP28, GP15, GP6, GP7, GP8 }
========
    { D4, C6, F5, F7 }
#define MATRIX_COL_PINS \
    { B4, B5, E6, D7, F6 }
>>>>>>>> f271c985ce (Revert "Merge branch 'hex6c-rev2' of https://github.com/mechlovin/qmk_firmware into hex6c-rev2"):keyboards/bastardkb/dilemma/elitec/config.h

/* Handedness. */
#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
<<<<<<<< HEAD:keyboards/bastardkb/scylla/v2/splinky_2/config.h
// #define SPLIT_HAND_PIN GP13
// #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.

/* RGB settings. */
#define RGB_DI_PIN GP0

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
========
//#define SPLIT_HAND_PIN F4
// If you've soldered the handedness pull-up on the upper side instead of the
// left one, uncomment the following line.
//#define SPLIT_HAND_PIN_LOW_IS_LEFT // High -> right, Low -> left.

/* serial.c configuration (for split keyboard). */
#define SOFT_SERIAL_PIN D2
>>>>>>>> f271c985ce (Revert "Merge branch 'hex6c-rev2' of https://github.com/mechlovin/qmk_firmware into hex6c-rev2"):keyboards/bastardkb/dilemma/elitec/config.h
