// Copyright 2024 zvecr <git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Workaround for reversible pcb/mcu
    palSetLineMode(C13, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(C15, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(B7, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A0, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A1, PAL_MODE_OUTPUT_OPENDRAIN);

    keyboard_pre_init_user();
}
