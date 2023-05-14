// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void matrix_init_custom(void) {
    // TODO: initialize hardware here
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here

    return matrix_has_changed;
}

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance,
                      uint8_t const* desc_report, uint16_t desc_len) {
}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance,
                                uint8_t const* report, uint16_t len) {
}