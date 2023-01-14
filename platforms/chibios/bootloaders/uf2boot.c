// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bootloader.h"

#define MAGIC_BOOT 0x544F4F42UL
#define MAGIC_REG *(volatile uint32_t*)0x20004000

void bootloader_jump(void) {
    MAGIC_REG = MAGIC_BOOT;
    NVIC_SystemReset();
}

void mcu_reset(void) {
    NVIC_SystemReset();
}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}
