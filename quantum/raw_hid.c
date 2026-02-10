// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "raw_hid.h"
#include "host.h"

void raw_hid_send(uint8_t *data, uint8_t length) {
    host_raw_hid_send(data, length);
}

__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}
