// Copyright 2023 Allan Seidel (@Allan Seidel)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

/* OLED SPI Defines */
#define OLED_DISPLAY_128X64
#define OLED_IC OLED_IC_SH1106

/* OLED SPI Pins */
#define OLED_DC_PIN GP11
#define OLED_CS_PIN GP12
#define OLED_RST_PIN GP13

/* Shift OLED columns by 2 pixels */
#define OLED_COLUMN_OFFSET 2

/* Divisor for OLED */
#define OLED_SPI_DIVISOR 4

/* ChibiOS SPI definitions */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP26
#define SPI_MOSI_PIN GP27

/* Double tap the pico reset button to enter bootloader. */
/* Pico reset button is the RUN pin (side hole #30). */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
