/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_VREG_H
#define _HARDWARE_VREG_H

#include "pico.h"
#include "hardware/structs/vreg_and_chip_reset.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file vreg.h
 *  \defgroup hardware_vreg hardware_vreg
 *
 * Voltage Regulation API
 *
 */

/** Possible voltage values that can be applied to the regulator
 */
enum vreg_voltage {
    VREG_VOLTAGE_0_85 = 0b0110,    ///< 0.85v
    VREG_VOLTAGE_0_90 = 0b0111,    ///< 0.90v
    VREG_VOLTAGE_0_95 = 0b1000,    ///< 0.95v
    VREG_VOLTAGE_1_00 = 0b1001,    ///< 1.00v
    VREG_VOLTAGE_1_05 = 0b1010,    ///< 1.05v
    VREG_VOLTAGE_1_10 = 0b1011,    ///< 1.10v
    VREG_VOLTAGE_1_15 = 0b1100,    ///< 1.15v
    VREG_VOLTAGE_1_20 = 0b1101,    ///< 1.20v
    VREG_VOLTAGE_1_25 = 0b1110,    ///< 1.25v
    VREG_VOLTAGE_1_30 = 0b1111,    ///< 1.30v

    VREG_VOLTAGE_MIN = VREG_VOLTAGE_0_85,      ///< Always the minimum possible voltage
    VREG_VOLTAGE_DEFAULT = VREG_VOLTAGE_1_10,  ///< Default voltage on power up.
    VREG_VOLTAGE_MAX = VREG_VOLTAGE_1_30,      ///< Always the maximum possible voltage
};


/*! \brief  Set voltage
 *  \ingroup hardware_vreg
 *
 * \param voltage  The voltage (from enumeration \ref vreg_voltage) to apply to the voltage regulator
 **/
void vreg_set_voltage(enum vreg_voltage voltage);

#ifdef __cplusplus
}
#endif

#endif