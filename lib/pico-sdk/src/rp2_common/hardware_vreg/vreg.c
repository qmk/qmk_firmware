/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"
#include "hardware/vreg.h"

void vreg_set_voltage(enum vreg_voltage voltage) {
    hw_write_masked(&vreg_and_chip_reset_hw->vreg, ((uint)voltage) << VREG_AND_CHIP_RESET_VREG_VSEL_LSB, VREG_AND_CHIP_RESET_VREG_VSEL_BITS);
}
