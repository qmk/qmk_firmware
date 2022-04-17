// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <avr/boot.h>
#include "hardware_id.h"

hardware_id_t get_hardware_id(void) {
    hardware_id_t id = {0};
    for (uint8_t i = 0; i < 10; i += 1) {
        ((uint8_t*)&id)[i] = boot_signature_byte_get(i + 0x0E);
    }
    return id;
}
