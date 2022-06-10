// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <ch.h>
#include "hardware_id.h"

hardware_id_t get_hardware_id(void) {
    hardware_id_t id = {0};
#ifdef UID_BASE
    id.data[0] = (uint32_t)(*((uint32_t *)UID_BASE));
    id.data[1] = (uint32_t)(*((uint32_t *)(UID_BASE + 4)));
    id.data[1] = (uint32_t)(*((uint32_t *)(UID_BASE + 8)));
#endif
    return id;
}
