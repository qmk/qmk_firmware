/* Copyright (C) 2024 koosikus
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

#ifdef WIRELESS_ENABLE
#    define LPWR_TIMEOUT RGB_MATRIX_TIMEOUT
#    define WLS_KEYBOARD_REPORT_KEYS 5
#    undef LPWR_TIMEOUT
#    define LPWR_TIMEOUT 600000 // 10min

#endif

#define USB_POWER_EN_PIN A14
#define LED_POWER_EN_PIN A15

#  define BT_CABLE_PIN B8 // 
#  define BT_CHARGE_PIN B9 // 

#  define BT_MODE_SW_PIN C10 // 
#  define RF_MODE_SW_PIN D2 // 

/* UART */
#define UART_TX_PIN A9
#define UART_RX_PIN A10
#define UART_RX_PAL_MODE 7

/* SPI Config for spi flash*/
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4
#define SPI_MOSI_PAL_MODE 5

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE (WEAR_LEVELING_BACKING_SIZE / 2)

/* I2C Config for LED Driver */
#define SNLED27351_I2C_ADDRESS_1 0b1110100
#define SNLED27351_I2C_ADDRESS_2 0b1110111
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 400000 /* 400000 */

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
