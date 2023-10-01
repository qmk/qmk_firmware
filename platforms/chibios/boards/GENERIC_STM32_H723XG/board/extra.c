// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <hal.h>
#define BOOTLOADER_MAGIC 0xDEADBEEF

////////////////////////////////////////////////////////////////////////////////
// Different signalling for bootloader entry
// - RAM is cleared on reset, so we can't use the usual __ram0_end__ symbol.
// - Use backup registers in the RTC peripheral to store the magic value instead.

static inline void enable_backup_register_access(void) {
    PWR->CR1 |= PWR_CR1_DBP;
}

static inline void disable_backup_register_access(void) {
    PWR->CR1 &= ~PWR_CR1_DBP;
}

void bootloader_marker_enable(void) {
    enable_backup_register_access();
    RTC->BKP0R = BOOTLOADER_MAGIC;
    disable_backup_register_access();
}

bool bootloader_marker_active(void) {
    enable_backup_register_access();
    bool ret = RTC->BKP0R == BOOTLOADER_MAGIC;
    disable_backup_register_access();
    return ret;
}

void bootloader_marker_disable(void) {
    enable_backup_register_access();
    RTC->BKP0R = 0;
    disable_backup_register_access();
}
