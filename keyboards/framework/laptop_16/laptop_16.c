// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

/**
 * Hook into early keyboard initialization
 */
void keyboard_pre_init_kb(void) {
    // Mark boot as done.
    // Before this, when holding down both alt keys QSPI_SS is pulled low to put
    // the RP2040 in bootloader mode during reset.
    gpio_set_pin_output(BOOT_DONE_GPIO);
    gpio_write_pin_low(BOOT_DONE_GPIO);

    // TODO: Do we ever need to disable it to save power?
    gpio_set_pin_output(MUX_ENABLE_GPIO);
    gpio_write_pin_high(MUX_ENABLE_GPIO);

    gpio_set_pin_input(SLEEP_GPIO);

    keyboard_pre_init_user();
}
