/* Copyright 2023 splitkb.com <support@splitkb.com>
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

// Make it easier to enter the bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

// I2C0, onboard SSD1306 socket and I2C to Myriad module
#define I2C_DRIVER   I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1
// We need to slow down the I2C clock because the default of 400.000
// fails to communicate with Zetta ZD24C02A EEPROM on a Myriad card.
#define I2C1_CLOCK_SPEED 100000

// SPI1, both for onboard matrix data and SPI to Myriad module
#define SPI_DRIVER   SPID1
#define SPI_SCK_PIN  GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

// UART1, communication between the two halves
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_DRIVER SIOD1
#define SERIAL_USART_TX_PIN GP20
#define SERIAL_USART_RX_PIN GP21

// Potential onboard speaker, not populated by default
#define AUDIO_PIN GP23

// Handedness
#define SPLIT_HAND_PIN GP14

// Matrix size
// Note that the rows are doubled,
// because this is a split
// 5 rows for the keeb, 1 row for Myriad
#define MATRIX_COLS  8
#define MATRIX_ROWS  12

// Encoders
// 3 onboard, 1 for Myriad
#define NUM_ENCODERS_LEFT 4
#define NUM_ENCODERS_RIGHT 4

// OLED display
#define OLED_DISPLAY_128X64
#define SPLIT_OLED_ENABLE
