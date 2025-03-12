/* Copyright 2024 GSKY <gskyGit@gsky.com.tw>
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
#endif

#define USB_POWER_EN_PIN C13
#define LED_POWER_EN_PIN B13

#define RGB_MATRIX_BAT_INDEX_MAP {17, 18, 19, 20, 21, 22, 23, 24, 25, 26}

#define MM_BT_DEF_PIN   C15
#define MM_24G_DEF_PIN  C14

/* UART */
#define UART_TX_PIN C10
#define UART_RX_PIN C11

/* Encoder */
#define ENCODER_MAP_KEY_DELAY 1

/* SPI */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B14
#define WEAR_LEVELING_LOGICAL_SIZE (WEAR_LEVELING_BACKING_SIZE / 2)

/* RGB Matrix */
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

/* WS2812 */
#define WS2812_SPI_DRIVER SPIDM2
#define RGBLED_NUM  81
#define WS2812_SPI_DIVISOR 32

/* It is not mandatory to configure; adjust according to the datasheet of WS2812 LEDs. */
#define WS2812_TIMING 1500
#define WS2812_T1H 1200
#define WS2812_T0H 400
