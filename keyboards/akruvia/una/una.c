// Copyright 2023 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    setPinInputHigh(GP3);
    setPinInputHigh(GP2);
    keyboard_pre_init_user();
}