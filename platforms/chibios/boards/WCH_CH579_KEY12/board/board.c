// Copyright 2026 Ryan McLean
// SPDX-License-Identifier: GPL-2.0-or-later

#include "hal.h"

void __early_init(void) {
    /* Nothing needed here — usb_lld_start() handles D+ pull-up at 48 MHz. */
}

/**
 * @brief   Board-specific initialisation.
 */
void boardInit(void) {}

/**
 * @brief   PAL setup.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
const PALConfig pal_default_config = {0};
#endif
