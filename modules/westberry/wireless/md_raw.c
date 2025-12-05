// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#if RAW_ENABLE

#    include "quantum.h"
#    include "wireless.h"

void md_receive_raw_cb(uint8_t *data, uint8_t length) {
    void raw_hid_receive(uint8_t *data, uint8_t length);

    raw_hid_receive(data, length);
}

#endif
