/*
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include "spi_master.h"

//////////////////////////////////////////////////////////////////////////////
// Configurations

#ifndef PMW3360_NCS_PIN
#    define PMW3360_NCS_PIN B6
#endif

/// DEBUG_PMW3360_SCAN_RATE enables scan performance counter.
/// It records scan count in a last second and enables pmw3360_scan_rate_get().
/// Additionally, it will be logged automatically when defined CONSOLE_ENABLE
/// and `debug_enable = true`.
//#define DEBUG_PMW3360_SCAN_RATE

//////////////////////////////////////////////////////////////////////////////
// Top level API

/// pmw3360_init initializes PMW3360DM-T2QU module.
/// It will return true when succeeded, otherwise false.
bool pmw3360_init(void);

typedef struct {
    int16_t x;
    int16_t y;
} pmw3360_motion_t;

/// pmw3360_motion_read gets a motion data by Motion register.
/// This requires to write a dummy data to pmw3360_Motion register
/// just before.
bool pmw3360_motion_read(pmw3360_motion_t *d);

/// pmw3360_motion_burst gets a motion data by Motion_Burst command.
/// This requires to write a dummy data to pmw3360_Motion_Burst register
/// just before.
bool pmw3360_motion_burst(pmw3360_motion_t *d);

/// pmw3360_scan_rate_get gets count of scan in a last second.
/// This works only when DEBUG_PMW3360_SCAN_RATE is defined.
uint32_t pmw3360_scan_rate_get(void);

// TODO: document
uint8_t pmw3360_cpi_get(void);

// TODO: document
void pmw3360_cpi_set(uint8_t cpi);

//////////////////////////////////////////////////////////////////////////////
// Register operations

/// pmw3360_reg_write writes a value to a register.
void pmw3360_reg_write(uint8_t addr, uint8_t data);

/// pmw3360_reg_read reads a value from a register.
uint8_t pmw3360_reg_read(uint8_t addr);

typedef enum {
    pmw3360_Product_ID                 = 0x00,
    pmw3360_Revision_ID                = 0x01,
    pmw3360_Motion                     = 0x02,
    pmw3360_Delta_X_L                  = 0x03,
    pmw3360_Delta_X_H                  = 0x04,
    pmw3360_Delta_Y_L                  = 0x05,
    pmw3360_Delta_Y_H                  = 0x06,
    pmw3360_SQUAL                      = 0x07,
    pmw3360_Raw_Data_Sum               = 0x08,
    pmw3360_Maximum_Raw_data           = 0x09,
    pmw3360_Minimum_Raw_data           = 0x0A,
    pmw3360_Shutter_Lower              = 0x0B,
    pmw3360_Shutter_Upper              = 0x0C,
    pmw3360_Control                    = 0x0D,
    pmw3360_Config1                    = 0x0F,
    pmw3360_Config2                    = 0x10,
    pmw3360_Angle_Tune                 = 0x11,
    pmw3360_Frame_Capture              = 0x12,
    pmw3360_SROM_Enable                = 0x13,
    pmw3360_Run_Downshift              = 0x14,
    pmw3360_Rest1_Rate_Lower           = 0x15,
    pmw3360_Rest1_Rate_Upper           = 0x16,
    pmw3360_Rest1_Downshift            = 0x17,
    pmw3360_Rest2_Rate_Lower           = 0x18,
    pmw3360_Rest2_Rate_Upper           = 0x19,
    pmw3360_Rest2_Downshift            = 0x1A,
    pmw3360_Rest3_Rate_Lower           = 0x1B,
    pmw3360_Rest3_Rate_Upper           = 0x1C,
    pmw3360_Observation                = 0x24,
    pmw3360_Data_Out_Lower             = 0x25,
    pmw3360_Data_Out_Upper             = 0x26,
    pmw3360_Raw_Data_Dump              = 0x29,
    pmw3360_SROM_ID                    = 0x2A,
    pmw3360_Min_SQ_Run                 = 0x2B,
    pmw3360_Raw_Data_Threshold         = 0x2C,
    pmw3360_Config5                    = 0x2F,
    pmw3360_Power_Up_Reset             = 0x3A,
    pmw3360_Shutdown                   = 0x3B,
    pmw3360_Inverse_Product_ID         = 0x3F,
    pmw3360_LiftCutoff_Tune3           = 0x41,
    pmw3360_Angle_Snap                 = 0x42,
    pmw3360_LiftCutoff_Tune1           = 0x4A,
    pmw3360_Motion_Burst               = 0x50,
    pmw3360_LiftCutoff_Tune_Timeout    = 0x58,
    pmw3360_LiftCutoff_Tune_Min_Length = 0x5A,
    pmw3360_SROM_Load_Burst            = 0x62,
    pmw3360_Lift_Config                = 0x63,
    pmw3360_Raw_Data_Burst             = 0x64,
    pmw3360_LiftCutoff_Tune2           = 0x65,
} pmw3360_reg_t;

enum {
    pmw3360_MAXCPI = 0x77, // = 119: 12000 CPI
};

//////////////////////////////////////////////////////////////////////////////
// SPI operations

bool pmw3360_spi_start(void);

void inline pmw3360_spi_stop(void) {
    spi_stop();
}

spi_status_t inline pmw3360_spi_write(uint8_t data) {
    return spi_write(data);
}

spi_status_t inline pmw3360_spi_read(void) {
    return spi_read();
}
