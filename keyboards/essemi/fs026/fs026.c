// Copyright 2024 Shanghai Eastsoft Microelectronics Co., Ltd
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "board.h"

void bootloader_jump(void) {
    /*Remap EFLASH,remap to boot*/
    md_fc_lock();
    md_syscfg_set_memory_mapping(SYSCFG, MD_SYSCFG_MEMMOD_MAIN);
    md_syscfg_set_flash_remap_base(SYSCFG, 0);
    md_syscfg_enable_memory_remap(SYSCFG);
    NVIC_SystemReset();
}

void mcu_reset(void) {
    NVIC_SystemReset();
}

void board_init(void) {
    /*Using USB_SOF to calibrate the internal clock*/
    md_rcu_enable_csu(RCU);
    CSU->CON |= CSU_CON_AUTOEN_MSK;
    CSU->CON |= CSU_CON_CNTEN_MSK;
}
