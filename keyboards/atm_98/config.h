// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN C11
#define LED_POWER_EN_PIN C13

#define ATM_FIRMWARE_VERSION_MAJOR 1
#define ATM_FIRMWARE_VERSION_MINOR 3
#define ATM_FIRMWARE_VERSION_PATCH 3

#define RGB_MATRIX_BAT_INDEX_MAP {17, 18, 19, 20, 21, 22, 23, 24, 25, 26}

/* User */
#define MATRIX_IO_DELAY 2
#define MATRIX_MASKED

/* UART */
#define UART_TX_PAL_MODE 7
#define UART_RX_PAL_MODE 7
#define UART_TX_PIN A9
#define UART_RX_PIN A10

/* Encoder */
#define ENCODER_RESOLUTION 2
#define ENCODER_MAP_KEY_DELAY 1

/* SPI */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4


#define EECONFIG_KB_DATA_SIZE 600
#define EECONFIG_KB_DATA_VERSION 3
/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE (WEAR_LEVELING_BACKING_SIZE / 2)

/* RGB Matrix */
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_SLEEP


/* WS2812 */
#define WS2812_SPI_DRIVER SPIDM2
#define WS2812_SPI_DIVISOR 32

/* It is not mandatory to configure; adjust according to the datasheet of WS2812 LEDs. */
#define WS2812_TIMING 1500
#define WS2812_T1H 1200
#define WS2812_T0H 400

#define RGBLIGHT_HUE_STEP 28
#define DIP_SWITCH_MATRIX_GRID { {0,14}, {0,15}, {0,16} }
