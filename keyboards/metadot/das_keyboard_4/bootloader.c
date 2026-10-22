// Copyright 2026 Giuseppe Iannello
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bootloader.h"

#include <NUC123.h>
#include <ch.h>
        
__attribute__((weak)) void bootloader_jump(void) {
    // Unlock the registries
    UNLOCKREG();

    // Set boot from LDROM
    FMC->ISPCON |= FMC_ISPCON_BS_Msk;

    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    // Unlock the registries
    UNLOCKREG();

    // Set boot from APROM
    FMC->ISPCON &= ~FMC_ISPCON_BS_Msk;

    NVIC_SystemReset();
}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}
