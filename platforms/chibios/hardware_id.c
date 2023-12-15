// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <ch.h>
#include "hardware_id.h"

hardware_id_t get_hardware_id(void) {
    hardware_id_t id = {0};
#if defined(RP2040)
    // Forward declare as including "hardware/flash.h" here causes more issues...
    void flash_get_unique_id(uint8_t *);

    flash_get_unique_id((uint8_t *)&id);
#elif defined(UID_BASE)
    id.data[0] = (uint32_t)(*((uint32_t *)UID_BASE));
    id.data[1] = (uint32_t)(*((uint32_t *)(UID_BASE + 4)));
    id.data[2] = (uint32_t)(*((uint32_t *)(UID_BASE + 8)));
#endif
    return id;
}
