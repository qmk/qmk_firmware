// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

/** \brief Storage for a hardware ID
 *
 * Ensure this is sized to cover all hardware scenarios
 */
typedef struct hardware_id_t {
    uint32_t data[4];
} hardware_id_t;

/** \brief Query the devices "unique" ID
 */
hardware_id_t get_hardware_id(void);
