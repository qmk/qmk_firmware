// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define QMK_WAITING_TEST_BUSY_PIN GP8
#define QMK_WAITING_TEST_YIELD_PIN GP9

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// settings for the oled keyboard demo with Adafruit 0.91" OLED display on the Stemma QT port
#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13

/* LCD configs */
#define LCD_RST_PIN GP0
#define LCD_DC_PIN GP1
#define LCD_CS_PIN GP2

/* SPI pins */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20
