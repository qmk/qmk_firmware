// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// We use 1MB flash
#define PICO_FLASH_SIZE_BYTES (1 * 1024 * 1024)
#define WEAR_LEVELING_RP2040_FLASH_SIZE PICO_FLASH_SIZE_BYTES
// Keep the last 4K sector free for the serial number
#define WEAR_LEVELING_RP2040_FLASH_BASE ((PICO_FLASH_SIZE_BYTES) - (WEAR_LEVELING_BACKING_SIZE + 4096))

#define SLEEP_GPIO GP0
#define MUX_ENABLE_GPIO GP4
#define BOOT_DONE_GPIO GP5

// PWM single one backlight configuration
// GPIO25 maps to PWM channel 4B of the RP2040
// On the Raspberry Pi Pico this is the green LED on the board, good for prototyping
#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B
// Change PWM frequency to 24kHz, the default of 2048Hz causes loud noise
#define BACKLIGHT_PWM_PERIOD BACKLIGHT_PWM_COUNTER_FREQUENCY / 24000
