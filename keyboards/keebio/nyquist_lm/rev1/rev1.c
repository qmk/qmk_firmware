// Copyright 2025 Keebio (@keebio)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Disable the PD peripheral in pre-init because its pins (B4, B6) are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_pre_init_user();
}
