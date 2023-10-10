/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#define MATRIX_UNSELECT_DRIVE_HIGH

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {4, 4} }

/* RGB Matrix Driver Configuration */
#define SNLED27351_DRIVER_COUNT 2
#define DRIVER_ADDR_1 SNLED27351_I2C_ADDRESS_VDDIO
#define DRIVER_ADDR_2 SNLED27351_I2C_ADDRESS_GND

#define SNLED27351_PHASE_CHANNEL SNLED27351_MSKPHASE_9CHANNEL

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Encoder Configuration*/
#define ENCODER_DEFAULT_POS 0x3

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
