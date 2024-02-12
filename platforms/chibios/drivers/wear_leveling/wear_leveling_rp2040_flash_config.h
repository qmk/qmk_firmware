// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef __ASSEMBLER__
#    include "hardware/flash.h"
#endif

// 2-byte writes
#ifndef BACKING_STORE_WRITE_SIZE
#    define BACKING_STORE_WRITE_SIZE 2
#endif

// 64kB backing space allocated
#ifndef WEAR_LEVELING_BACKING_SIZE
#    define WEAR_LEVELING_BACKING_SIZE 8192
#endif // WEAR_LEVELING_BACKING_SIZE

// 32kB logical EEPROM
#ifndef WEAR_LEVELING_LOGICAL_SIZE
#    define WEAR_LEVELING_LOGICAL_SIZE ((WEAR_LEVELING_BACKING_SIZE) / 2)
#endif // WEAR_LEVELING_LOGICAL_SIZE

// Define how much flash space we have (defaults to lib/pico-sdk/src/boards/include/boards/***)
#ifndef WEAR_LEVELING_RP2040_FLASH_SIZE
#    define WEAR_LEVELING_RP2040_FLASH_SIZE (PICO_FLASH_SIZE_BYTES)
#endif

// Define the location of emulated EEPROM
#ifndef WEAR_LEVELING_RP2040_FLASH_BASE
#    define WEAR_LEVELING_RP2040_FLASH_BASE ((WEAR_LEVELING_RP2040_FLASH_SIZE) - (WEAR_LEVELING_BACKING_SIZE))
#endif
