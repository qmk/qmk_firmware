// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bluetooth.h"

__attribute__((weak)) void bluetooth_init(void) {}

__attribute__((weak)) void bluetooth_task(void) {}

__attribute__((weak)) bool bluetooth_is_connected(void) {
    return true;
}

__attribute__((weak)) bool bluetooth_can_send_nkro(void) {
    return false;
}

__attribute__((weak)) uint8_t bluetooth_keyboard_leds(void) {
    return 0;
}

__attribute__((weak)) void bluetooth_send_keyboard(report_keyboard_t *report) {}

__attribute__((weak)) void bluetooth_send_nkro(report_nkro_t *report) {}

__attribute__((weak)) void bluetooth_send_mouse(report_mouse_t *report) {}

__attribute__((weak)) void bluetooth_send_consumer(uint16_t usage) {}

__attribute__((weak)) void bluetooth_send_system(uint16_t usage) {}

__attribute__((weak)) void bluetooth_send_raw_hid(uint8_t *data, uint8_t length) {}
