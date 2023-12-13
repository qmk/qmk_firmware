// Copyright 2023 BlindAssassin111 (@blindassassin111)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // enable built in pullups to avoid timeouts when right hand not connected
    setPinInputHigh(D0);
    setPinInputHigh(D1);

    keyboard_pre_init_user();
}
