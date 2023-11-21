/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

/* LED Matrix Driver Configuration */
#define SNLED27351_DRIVER_COUNT 1
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_GND
#define LED_MATRIX_LED_COUNT 84

#define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_6_CHANNEL
#define SNLED27351_CURRENT_TUNE \
    { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 } // 250mA
    // { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 } // 127mA

/* Disable LED lighting when PC is in suspend */
#define LED_DISABLE_WHEN_USB_SUSPENDED

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 46