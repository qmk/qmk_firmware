// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2021 Alabastard (@Alabastard-64)
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2019 Sunjun Kim
// Copyright 2020 Ploopy Corporation
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "pointing_device.h"
#include <stdint.h>

#if !defined(PMW3389_CPI)
#    define PMW3389_CPI 2000
#endif

#define PMW3389_CPI_STEP 50
#define PMW3389_CPI_MIN 50
#define PMW3389_CPI_MAX 16000

#define PMW3389_FIRMWARE_LENGTH 4094

// PMW3389 register addresses
// clang-format off
#define PMW3389_REG_Product_ID                 0x00
#define PMW3389_REG_Revision_ID                0x01
#define PMW3389_REG_Motion                     0x02
#define PMW3389_REG_Delta_X_L                  0x03
#define PMW3389_REG_Delta_X_H                  0x04
#define PMW3389_REG_Delta_Y_L                  0x05
#define PMW3389_REG_Delta_Y_H                  0x06
#define PMW3389_REG_SQUAL                      0x07
#define PMW3389_REG_RawData_Sum                0x08
#define PMW3389_REG_Maximum_RawData            0x09
#define PMW3389_REG_Minimum_RawData            0x0a
#define PMW3389_REG_Shutter_Lower              0x0b
#define PMW3389_REG_Shutter_Upper              0x0c
#define PMW3389_REG_Ripple_Control             0x0d
#define PMW3389_REG_Resolution_L               0x0e
#define PMW3389_REG_Resolution_H               0x0f
#define PMW3389_REG_Config2                    0x10
#define PMW3389_REG_Angle_Tune                 0x11
#define PMW3389_REG_Frame_Capture              0x12
#define PMW3389_REG_SROM_Enable                0x13
#define PMW3389_REG_Run_Downshift              0x14
#define PMW3389_REG_Rest1_Rate_Lower           0x15
#define PMW3389_REG_Rest1_Rate_Upper           0x16
#define PMW3389_REG_Rest1_Downshift            0x17
#define PMW3389_REG_Rest2_Rate_Lower           0x18
#define PMW3389_REG_Rest2_Rate_Upper           0x19
#define PMW3389_REG_Rest2_Downshift            0x1a
#define PMW3389_REG_Rest3_Rate_Lower           0x1b
#define PMW3389_REG_Rest3_Rate_Upper           0x1c
#define PMW3389_REG_Observation                0x24
#define PMW3389_REG_Data_Out_Lower             0x25
#define PMW3389_REG_Data_Out_Upper             0x26
#define PMW3389_REG_SROM_ID                    0x2a
#define PMW3389_REG_Min_SQ_Run                 0x2b
#define PMW3389_REG_RawData_Threshold          0x2c
#define PMW3389_REG_Control2                   0x2d
#define PMW3389_REG_Config5_L                  0x2e
#define PMW3389_REG_Config5_H                  0x2f
#define PMW3389_REG_Power_Up_Reset             0X3a
#define PMW3389_REG_Shutdown                   0x3b
#define PMW3389_REG_Inverse_Product_ID         0x3f
#define PMW3389_REG_LiftCutoff_Cal3            0x41
#define PMW3389_REG_Angle_Snap                 0x42
#define PMW3389_REG_LiftCutoff_Cal1            0x4a
#define PMW3389_REG_Motion_Burst               0x50
#define PMW3389_REG_SROM_Load_Burst            0x62
#define PMW3389_REG_Lift_Config                0x63
#define PMW3389_REG_RawData_Burst              0x64
#define PMW3389_REG_LiftCutoff_Cal2            0x65
#define PMW3389_REG_LiftCutoff_Cal_Timeout     0x71
#define PMW3389_REG_LiftCutoff_Cal_Min_Length  0x72
#define PMW3389_REG_PWM_Period_Cnt             0x73
#define PMW3389_REG_PWM_Width_Cnt              0x74
// clang-format on

#if PMW3389_CPI > PMW3389_CPI_MAX || PMW3389_CPI < PMW3389_CPI_MIN || (PMW3389_CPI % PMW3389_CPI_STEP) != 0U
#    pragma message "PMW3389_CPI has to be in the range of " STR(PMW3389_CPI_MAX) "-" STR(PMW3389_CPI_MIN) " in increments of " STR(PMW3389_CPI_STEP) ". But it is " STR(PMW3389_CPI) "."
#    error Use correct PMW3389_CPI value.
#endif

const pointing_device_driver_t     pmw3389_driver_spi_default;
const pointing_device_spi_config_t pmw3389_config_spi_default;

void              pmw3389_init(const void* config);
uint16_t          pmw3389_get_cpi(const void* config);
void              pmw3389_set_cpi(const void* config, uint16_t cpi);
report_mouse_t    pmw3389_get_report(const void* config);