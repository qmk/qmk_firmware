// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define DEBUG_MATRIX_SCAN_RATE

//#define QMK_WAITING_TEST_BUSY_PIN GP8
//#define QMK_WAITING_TEST_YIELD_PIN GP9

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// settings for the oled keyboard demo with Adafruit 0.91" OLED display on the Stemma QT port
#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1

#define OLED_BRIGHTNESS 255 // you can reduce the brightness, but not make it brighter!
#define OLED_TIMEOUT 3000000 // 5 minutes before oled turns off

#define ENCODER_A_PINS { GP27, GP26 }

#define ENCODER_RESOLUTION 4
