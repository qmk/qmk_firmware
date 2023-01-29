// Copyright 2023 a_marmot
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
//
// SPDX-License-Identifier: GPL-2.0-or-later

// This firmware is for a Razer Orbweaver Chroma keypad, modded to replace the stock MCU
// with an Elite Pi RP2040 microcontroller. Mod instructions can be found on geekhack
// https://geekhack.org/index.php?topic=119396.0

// The firmware controls a 6x5 key matrix (4x5 keypad + 6 additional keys
// on the thumb pad and up to 4 additional keys added by user). It also controls a
// IS31FL3731 RGB Matrix controller (on the Chroma model) via I2C interface. This requires
// a single I2C Driver with 20 common anode RGB LEDs. Note the I2C clock speed must be
// slowed down to 100 kHz for the IS31 chip to keep up.  

// Updated firmware includes a single multi-layer keymap ("orby") with fixed color maps
// for each layer.  The default (base) layer is a menu for other layers, or to put the
// RP2040 in bootloader mode.  

// Other keymaps include a utility ("RGBtest") for sequentially toggling all the LEDs
// one by one to insure the correct RGB matrix assignments, and "RGB144" for testing all 
// 144 matrix elements and reporting the active LED. The keymap "NoRGB" does not include 
// any writes to the IS31, so can be used to test the key matrix by itself (or on a non-
// RGB Orbweaver).

#pragma once

#define DRIVER_COUNT 1
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_LED_TOTAL 60
#define RGB_MATRIX_LED_COUNT 20
#define ISSI_TIMEOUT 100
#define ISSI_PERSISTENCE 0
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE  STD_DUTY_CYCLE

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
