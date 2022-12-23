// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef __ASSEMBLER__
#    include <stdlib.h>
#    include <stdint.h>
#    include "flash_spi.h"
#endif

// Use 1 block -- check the config for the SPI flash to determine how big it is
#ifndef WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT
#    define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT 1
#endif // WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT

// Start at the first block of the external flash
#ifndef WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET
#    define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET 0
#endif // WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET

// 8-byte writes by default
#ifndef BACKING_STORE_WRITE_SIZE
#    define BACKING_STORE_WRITE_SIZE 8
#endif

// The space allocated by the block
#ifndef WEAR_LEVELING_BACKING_SIZE
#    define WEAR_LEVELING_BACKING_SIZE ((EXTERNAL_FLASH_BLOCK_SIZE) * (WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT))
#endif // WEAR_LEVELING_BACKING_SIZE

// Use half of the backing size for logical EEPROM
#ifndef WEAR_LEVELING_LOGICAL_SIZE
#    define WEAR_LEVELING_LOGICAL_SIZE ((WEAR_LEVELING_BACKING_SIZE) / 2)
#endif // WEAR_LEVELING_LOGICAL_SIZE
