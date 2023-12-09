/* Copyright 2021 @ Keychron(https://www.keychron.com)
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

/* RGB Matrix Driver Configuration */
#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_VCC

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {0,1} }

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* Encoder Configuration*/
#define ENCODER_DEFAULT_POS 0x3

/* Disable RGB lighting when PC is in suspend */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS