// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

painter_device_t display;


uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {
    // each keymap creates its display handle
    qp_dprintf("Initialising display...\n");
    keyboard_post_init_user();
    qp_init(display, QP_ROTATION_0);

    // draw sample code, just a red line on black background
    qp_dprintf("Drawing sample code...\n");
    qp_rect(display, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, HSV_BLACK, true);
    qp_line(display, 0, 0, 20, 20, HSV_RED);

    return 0;
}


void keyboard_post_init_kb(void) {
    debug_enable = true;
    // actual code is deferred to ensure USB is init'ed and we can see output on console
    defer_exec(INIT_DELAY, deferred_init, NULL);
}
