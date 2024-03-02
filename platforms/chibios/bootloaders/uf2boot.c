// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bootloader.h"

// From mmoskal/uf2-stm32f103's backup.c
#define MAGIC_BOOT 0x544F4F42UL

// defined by linker script
extern uint32_t _board_magic_reg[];
#define MAGIC_REG _board_magic_reg[0]

void bootloader_jump(void) {
    MAGIC_REG = MAGIC_BOOT;
    NVIC_SystemReset();
}

void mcu_reset(void) {
    NVIC_SystemReset();
}

/* not needed, no two-stage reset */
void enter_bootloader_mode_if_requested(void) {}
