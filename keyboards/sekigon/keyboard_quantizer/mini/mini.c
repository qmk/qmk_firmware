// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard.h"
#include "pico/stdlib.h"

extern void start_core1(void);

void keyboard_pre_init_kb(void) {
    set_sys_clock_khz(120000, true);
}

void keyboard_post_init_kb(void) {
    start_core1();
    keyboard_post_init_user();
}