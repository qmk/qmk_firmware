// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

void early_hardware_init_post(void) {
    // Disable RGB LEDs
    gpio_set_pin_output(RGB_ENABLE_PIN);
    gpio_write_pin(RGB_ENABLE_PIN, 1);
}

void housekeeping_task_kb() {
    // Enable RGB LEDs after 200 milliseconds
    static bool rgb_enabled = false;
    if (!rgb_enabled && timer_read32() > 200) {
        gpio_write_pin(RGB_ENABLE_PIN, 0);
        rgb_enabled = true;
    }
}
