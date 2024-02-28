// Copyright 2022 ShandonCodes (@ShandonCodes)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
  SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_SPI2_DMA_RMP);
}