/* Copyright 2026 Karl Strålman
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

// #define SERIAL_USART_SPEED 921600
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN B10
#define SERIAL_USART_RX_PIN B11
#define SERIAL_USART_PIN_SWAP
#define USART3_REMAP
#define SERIAL_USART_TX_PAL_MODE 4
#define SERIAL_USART_RX_PAL_MODE 4
#define SERIAL_USART_DRIVER SD3

#define MASTER_LEFT
#define OLED_DISPLAY_ADDRESS 0x3C //0x78
#define OLED_DISPLAY_128X64
#define OLED_BRIGHTNESS 128

#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B13
#define I2C1_SCL_PAL_MODE 5
#define I2C1_SDA_PIN B14
#define I2C1_SDA_PAL_MODE 5
