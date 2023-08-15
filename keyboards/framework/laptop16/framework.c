// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "framework.h"

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();

    // Enable debug output
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
}

/**
 * Hook into early keyboard initialization
 */
void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();

    // Mark boot as done.
    // Before this, when holding down both alt keys QSPI_SS is pulled low to put
    // the RP2040 in bootloader mode during reset.
    setPinOutput(BOOT_DONE_GPIO);
    writePinLow(BOOT_DONE_GPIO);

    // TODO: Do we ever need to disable it to save power?
    setPinOutput(MUX_ENABLE_GPIO);
    writePinHigh(MUX_ENABLE_GPIO);

    setPinInput(SLEEP_GPIO);
}
