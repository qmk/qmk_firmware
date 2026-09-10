// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "wireless_2p4ghz.h"

__attribute__((weak)) void wireless_2p4ghz_init(void) {}

__attribute__((weak)) void wireless_2p4ghz_task(void) {}

__attribute__((weak)) bool wireless_2p4ghz_is_connected(void) {
    return false;
}

__attribute__((weak)) bool wireless_2p4ghz_can_send_nkro(void) {
    return false;
}

__attribute__((weak)) uint8_t wireless_2p4ghz_keyboard_leds(void) {
    return 0;
}

__attribute__((weak)) void wireless_2p4ghz_send_keyboard(report_keyboard_t *report) {}

__attribute__((weak)) void wireless_2p4ghz_send_nkro(report_nkro_t *report) {}

__attribute__((weak)) void wireless_2p4ghz_send_mouse(report_mouse_t *report) {}

__attribute__((weak)) void wireless_2p4ghz_send_consumer(uint16_t usage) {}

__attribute__((weak)) void wireless_2p4ghz_send_system(uint16_t usage) {}

__attribute__((weak)) void wireless_2p4ghz_send_raw_hid(uint8_t *data, uint8_t length) {}

__attribute__((weak)) void wireless_2p4ghz_unpair(void) {}
