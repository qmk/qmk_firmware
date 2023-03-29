// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ergodone.h"

#include "ergodox_compat.h"
void keyboard_post_init_kb(void) {
    ergodox_blink_all_leds();

    keyboard_post_init_user();
}
