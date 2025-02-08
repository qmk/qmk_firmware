/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pointing_device.h"

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// Definitions for the PMW3320 serial line.
#ifndef PMW3320_SCLK_PIN
#    ifdef POINTING_DEVICE_SCLK_PIN
#        define PMW3320_SCLK_PIN POINTING_DEVICE_SCLK_PIN
#    else
#        error "No clock pin defined -- missing POINTING_DEVICE_SCLK_PIN or PMW3320_SCLK_PIN"
#    endif
#endif

#ifndef PMW3320_SDIO_PIN
#    ifdef POINTING_DEVICE_SDIO_PIN
#        define PMW3320_SDIO_PIN POINTING_DEVICE_SDIO_PIN
#    else
#        error "No data pin defined -- missing POINTING_DEVICE_SDIO_PIN or PMW3320_SDIO_PIN"
#    endif
#endif

#ifndef PMW3320_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define PMW3320_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing POINTING_DEVICE_CS_PIN or PMW3320_CS_PIN define"
#    endif
#endif

typedef struct {
    int8_t dx;
    int8_t dy;
} report_pmw3320_t;

const pointing_device_driver_t pmw3320_pointing_device_driver;

// A bunch of functions to implement the PMW3320-specific serial protocol.
// Mostly taken from ADNS5050 driver.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.
void             pmw3320_init(void);
void             pmw3320_sync(void);
uint8_t          pmw3320_serial_read(void);
void             pmw3320_serial_write(uint8_t data);
uint8_t          pmw3320_read_reg(uint8_t reg_addr);
void             pmw3320_write_reg(uint8_t reg_addr, uint8_t data);
report_pmw3320_t pmw3320_read_burst(void);
void             pmw3320_set_cpi(uint16_t cpi);
uint16_t         pmw3320_get_cpi(void);
int8_t           convert_twoscomp(uint8_t data);
bool             pmw3320_check_signature(void);
report_mouse_t   pmw3320_get_report(report_mouse_t mouse_report);

#if !defined(PMW3320_CPI)
#    define PMW3320_CPI 1000
#endif

#define PMW3320_CPI_STEP 250
#define PMW3320_CPI_MIN 250
#define PMW3320_CPI_MAX 3500

// PMW3320 register addresses
// clang-format off
#define REG_Product_ID                 0x00
#define REG_Revision_ID                0x01
#define REG_Motion                     0x02
#define REG_Delta_X                    0x03
#define REG_Delta_Y                    0x04
#define REG_SQUAL                      0x05
#define REG_Shutter_Upper              0x06
#define REG_Shutter_Lower              0x07
#define REG_Maximum_Pixel              0x08
#define REG_Pixel_Accum                0x09
#define REG_Minimum_Pixel              0x0a
#define REG_Pixel_Grab                 0x0b
#define REG_Delta_XY                   0x0c
#define REG_Resolution                 0x0d
#define REG_Run_Downshift              0x0e
#define REG_Rest1_Period               0x0f
#define REG_Rest1_Downshift            0x10
#define REG_Rest2_Preiod               0x11
#define REG_Rest2_Downshift            0x12
#define REG_Rest3_Period               0x13
#define REG_Min_SQ_Run                 0x17
#define REG_Axis_Control               0x1a
#define REG_Performance                0x22
#define REG_Low_Motion_Jitter          0x23
#define REG_Shutter_Max_HI             0x36
#define REG_Shutter_Max_LO             0x37
#define REG_Frame_Rate                 0x39
#define REG_Power_Up_Reset             0x3a
#define REG_Shutdown                   0x3b
#define REG_Inverse_Revision_ID        0x3f
#define REG_Led_Control                0x40
#define REG_Motion_Control             0x41
#define REG_Burst_Read_First           0x42
#define REG_Rest_Mode_Status           0x45
#define REG_Inverse_Product_ID         0x4f
#define REG_Motion_Burst               0x63
// clang-format on
