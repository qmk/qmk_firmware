// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define FW_VERSION "20250419-1.2.0"

// see `wear_leveling_rp2040_flash_config.h`
// currently, using 16MB SPI flash
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8192

// using W25Q128JVS as an EEPROM
#define EXTERNAL_EEPROM_PAGE_SIZE 256
#define EXTERNAL_EEPROM_BYTE_COUNT (65536 * EXTERNAL_EEPROM_PAGE_SIZE)
#define EXTERNAL_EEPROM_ADDRESS_SIZE 4

#define EECONFIG_KB_DATA_SIZE 1024 // 1KB for kb_config_t
#define EECONFIG_KB_DATA_VERSION (0x01)

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET               // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25      // Specify a optional status led by GPIO number which blinks when entering the bootloader

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#define ENCODER_A_PINS {NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN}
#define ENCODER_B_PINS {NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN}

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3
