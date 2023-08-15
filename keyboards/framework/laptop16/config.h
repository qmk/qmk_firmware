// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Allow (emulated) EEPROM reset using VIA
#define VIA_EEPROM_ALLOW_RESET

// Increase to 16K for more storage space
// With 64K backing size, this spread the wear level over 4 blocks
#define WEAR_LEVELING_LOGICAL_SIZE (4 * 4096)
// Increase to 64K backing size to allow more wear leveling
#define WEAR_LEVELING_BACKING_SIZE (16 * 4096)
// We use 1MB flash
#define PICO_FLASH_SIZE_BYTES (1 * 1024 * 1024)
#define WEAR_LEVELING_RP2040_FLASH_SIZE PICO_FLASH_SIZE_BYTES
// Keep the last 4K sector free for the serial number
#define WEAR_LEVELING_RP2040_FLASH_BASE ((PICO_FLASH_SIZE_BYTES) - (WEAR_LEVELING_BACKING_SIZE + 4096))

// Prints every second how many matrix scans were done (Frequency in Hz)
// Only during debugging, since it prevents the host from going to sleep
// #define DEBUG_MATRIX_SCAN_RATE

// PWM single one backlight configuration
// GPIO25 maps to PWM channel 4B of the RP2040
// On the Raspberry Pi Pico this is the green LED on the board, good for prototyping
#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define BACKLIGHT_BREATHING
// Change PWM frequency to 24kHz, the default of 2048Hz causes loud noise
// TODO: Waiting for PR #21717
// #define BACKLIGHT_PWM_PERIOD BACKLIGHT_PWM_COUNTER_FREQUENCY / 24000
