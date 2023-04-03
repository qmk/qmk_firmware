// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2022 Ulrich Spörlein (@uqs)
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2019 Sunjun Kim
// Copyright 2020 Ploopy Corporation
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "pointing_device.h"
#include <stdint.h>

#if !defined(PMW3360_CPI)
#    define PMW3360_CPI 1600U
#endif

#define PMW3360_CPI_STEP 100
#define PMW3360_CPI_MIN 100
#define PMW3360_CPI_MAX 12000

#define PMW3360_FIRMWARE_LENGTH 4094

// PMW3360 register addresses
// clang-format off
#define PMW3360_REG_Product_ID                   0x00
#define PMW3360_REG_Revision_ID                  0x01
#define PMW3360_REG_Motion                       0x02
#define PMW3360_REG_Delta_X_L                    0x03
#define PMW3360_REG_Delta_X_H                    0x04
#define PMW3360_REG_Delta_Y_L                    0x05
#define PMW3360_REG_Delta_Y_H                    0x06
#define PMW3360_REG_SQUAL                        0x07
#define PMW3360_REG_Raw_Data_Sum                 0x08
#define PMW3360_REG_Maximum_Raw_data             0x09
#define PMW3360_REG_Minimum_Raw_data             0x0a
#define PMW3360_REG_Shutter_Lower                0x0b
#define PMW3360_REG_Shutter_Upper                0x0c
#define PMW3360_REG_Control                      0x0d
#define PMW3360_REG_Config1                      0x0f
#define PMW3360_REG_Config2                      0x10
#define PMW3360_REG_Angle_Tune                   0x11
#define PMW3360_REG_Frame_Capture                0x12
#define PMW3360_REG_SROM_Enable                  0x13
#define PMW3360_REG_Run_Downshift                0x14
#define PMW3360_REG_Rest1_Rate_Lower             0x15
#define PMW3360_REG_Rest1_Rate_Upper             0x16
#define PMW3360_REG_Rest1_Downshift              0x17
#define PMW3360_REG_Rest2_Rate_Lower             0x18
#define PMW3360_REG_Rest2_Rate_Upper             0x19
#define PMW3360_REG_Rest2_Downshift              0x1a
#define PMW3360_REG_Rest3_Rate_Lower             0x1b
#define PMW3360_REG_Rest3_Rate_Upper             0x1c
#define PMW3360_REG_Observation                  0x24
#define PMW3360_REG_Data_Out_Lower               0x25
#define PMW3360_REG_Data_Out_Upper               0x26
#define PMW3360_REG_Raw_Data_Dump                0x29
#define PMW3360_REG_SROM_ID                      0x2a
#define PMW3360_REG_Min_SQ_Run                   0x2b
#define PMW3360_REG_Raw_Data_Threshold           0x2c
#define PMW3360_REG_Config5                      0x2f
#define PMW3360_REG_Power_Up_Reset               0x3a
#define PMW3360_REG_Shutdown                     0x3b
#define PMW3360_REG_Inverse_Product_ID           0x3f
#define PMW3360_REG_LiftCutoff_Tune3             0x41
#define PMW3360_REG_Angle_Snap                   0x42
#define PMW3360_REG_LiftCutoff_Tune1             0x4a
#define PMW3360_REG_Motion_Burst                 0x50
#define PMW3360_REG_LiftCutoff_Tune_Timeout      0x58
#define PMW3360_REG_LiftCutoff_Tune_Min_Length   0x5a
#define PMW3360_REG_SROM_Load_Burst              0x62
#define PMW3360_REG_Lift_Config                  0x63
#define PMW3360_REG_Raw_Data_Burst               0x64
#define PMW3360_REG_LiftCutoff_Tune2             0x65
// clang-format on

#if PMW3360_CPI > PMW3360_CPI_MAX || PMW3360_CPI < PMW3360_CPI_MIN || (PMW3360_CPI % PMW3360_CPI_STEP) != 0U
#    pragma message "PMW3360_CPI has to be in the range of " STR(PMW3360_CPI_MAX) "-" STR(PMW3360_CPI_MIN) " in increments of " STR(PMW3360_CPI_STEP) ". But it is " STR(PMW3360_CPI) "."
#    error Use correct PMW3360_CPI value.
#endif

const pointing_device_driver_t     pmw3360_driver_spi_default;
const pointing_device_spi_config_t pmw3360_config_spi_default;

void              pmw3360_init(const void* config);
uint16_t          pmw3360_get_cpi(const void* config);
void              pmw3360_set_cpi(const void* config, uint16_t cpi);
report_mouse_t    pmw3360_get_report(const void* config);