// Copyright 2023 Noah Beidelman (@noahbei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
}
