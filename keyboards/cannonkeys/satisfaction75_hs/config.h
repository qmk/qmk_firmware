// Copyright 2023 Andrew Kannan (@awkannan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* LSE clock */
#define STM32_LSECLK 32768

#define ENCODER_RESOLUTION 2

// I2C config
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
#define I2C1_TIMINGR_PRESC 0x00U
#define I2C1_TIMINGR_SCLDEL 0x03U
#define I2C1_TIMINGR_SDADEL 0x01U
#define I2C1_TIMINGR_SCLH 0x03U
#define I2C1_TIMINGR_SCLL 0x09U

// configure oled driver for the 128x32 oled
#define OLED_UPDATE_INTERVAL 66 // ~15fps

// OLED_TIMEOUT is incompatible with the OLED_OFF mode
#define OLED_TIMEOUT 0

// OLED timeout reimplemented in the keyboard-specific code
#define CUSTOM_OLED_TIMEOUT 60000

// Custom config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
// Custom config Usage:
// 1 for enabled encoder modes (1 byte)
// 1 for OLED default mode (1 byte)
// 6 for 3x custom encoder settings, left, right, and press (18 bytes)
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 20

// And if VIA isn't enabled, fall back to using standard QMK for configuration
#ifndef VIA_ENABLE
#define EECONFIG_KB_DATA_SIZE VIA_EEPROM_CUSTOM_CONFIG_SIZE
#endif

// VIA lighting is handled by the keyboard-level code
#define VIA_CUSTOM_LIGHTING_ENABLE
