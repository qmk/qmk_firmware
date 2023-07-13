// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define ENCODER_DEFAULT_POS 0x3  // enable 1:1 resolution

/*
 * Wear-leveling RP2040 Driver Configuration
 */

// #define WEAR_LEVELING_RP2040_FLASH_SIZE (32 * 1024 * 1024)  // Number of bytes of flash on the board.
// #define WEAR_LEVELING_RP2040_FLASH_BASE (flash_size-sector_size)  // The byte-wise location that the backing storage should be located.
#define WEAR_LEVELING_LOGICAL_SIZE (2 * 1024)  // Number of bytes “exposed” to the rest of QMK and denotes the size of the usable EEPROM.
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)  // Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size as well as the sector size.
// #define BACKING_STORE_WRITE_SIZE 2  // The write width used whenever a write is performed on the external flash peripheral.

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
