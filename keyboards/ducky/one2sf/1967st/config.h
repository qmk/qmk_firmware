// Copyright 2019 /u/KeepItUnder
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define GPIO_INPUT_PIN_DELAY (NUC123_HCLK / 6 / 1000000L)

// Wear-leveling EEPROM backed by on-chip APROM flash (64 KB with default 4 KB data-flash).
// 2 KB backing store → 1 KB logical EEPROM, uses the last 4 sectors of APROM.
#define WEAR_LEVELING_EFL_FLASH_SIZE 0x10000
// NUC123 flash write granularity is 4 bytes (from hal_efl_lld.c NUC123_PAGE_SIZE).
// QMK's auto-detection checks QMK_MCU_FAMILY_NUC123 but the build system generates
// QMK_MCU_FAMILY_NUMICRO, so we set it explicitly.
#define BACKING_STORE_WRITE_SIZE 4
