/* Copyright 2023 @ Keychron(https://www.keychron.com)
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
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_GND

/* Increase I2C speed to 1000 KHz */
#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 15U
#define I2C1_TIMINGR_SCLL 51U

#define SNLED27351_CURRENT_TUNE \
    { 0x80, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0x80, 0xFF, 0xFF } // 300mA

/* Split Keyboard specific options. */
#define SERIAL_USART_TX_PIN A9 // USART TX pin

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

// Needed as the master side could enter slave state during poweron
// of host, due to missing VUSB detection.
#define SPLIT_WATCHDOG_ENABLE
