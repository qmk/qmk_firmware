// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;
    keyboard_post_init_user();
}
