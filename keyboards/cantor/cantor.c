// Copyright 2023 Alessio Caiazza (@nolith)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// Workaround for https://github.com/qmk/qmk_firmware/issues/16406
__attribute__ ((weak))
void suspend_wakeup_init_kb(void) {
    NVIC_SystemReset();
    suspend_wakeup_init_user();
}
