// Copyright 2020-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_RSE_PIN B13
#define LED_LWR_PIN B12

#define EEPROM_PAGE_SIZE
#define FEE_PAGE_SIZE 0x800
#define FEE_PAGE_COUNT 4

#define FEE_MCU_FLASH_SIZE_IGNORE_CHECK
#define FEE_MCU_FLASH_SIZE                                \
    ({                                                    \
        uint16_t flash_size = *(uint16_t*)FLASHSIZE_BASE; \
        (flash_size <= 512) ? flash_size : 512;           \
    })
