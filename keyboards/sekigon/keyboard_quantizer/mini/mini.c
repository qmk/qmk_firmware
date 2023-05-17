// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard.h"
#include "pico/stdlib.h"
#include "bootloader.h"
#include "debug.h"

void keyboard_pre_init_kb(void) {
    set_sys_clock_khz(120000, true);
}

void virtser_recv(uint8_t c) {
    if (c == 'b') {
        bootloader_jump();
    } else if (c == 'd') {
        debug_enable = !debug_enable;
        uprintf("Debug %s\n", debug_enable ? "enabled" : "disabled");
    }
}
