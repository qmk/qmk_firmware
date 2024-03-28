// Copyright 2022 Pablo Martinez (@elpekenin)
// Copyright 2022 Daniel Kao (dkao)
// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2022 Ulrich Spörlein (@uqs)
// Copyright 2021 Alabastard (@Alabastard-64)
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2019 Sunjun Kim
// Copyright 2020 Ploopy Corporation
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keyboard.h"
#include <stdint.h>
#include "spi_master.h"
#include "util.h"

#if defined(POINTING_DEVICE_DRIVER_pmw3360)
#    include "pmw3360.h"
#elif defined(POINTING_DEVICE_DRIVER_pmw3389)
#    include "pmw3389.h"
#endif

typedef struct {
    uint8_t Product_ID;
    uint8_t Motion;
    uint8_t Delta_X_L;
    uint8_t Delta_X_H;
    uint8_t Delta_Y_L;
    uint8_t Delta_Y_H;
    uint8_t Config2;
    uint8_t Angle_Tune;
    uint8_t SROM_Enable;
    uint8_t SROM_ID;
    uint8_t Inverse_Product_ID;
    uint8_t Motion_Burst;
    uint8_t SROM_Load_Burst;
    uint8_t Lift_Config;
    uint8_t Power_Up_Reset;
} pmw33xx_regs_common_t;
typedef struct __attribute__((packed)) {
    union {
        struct {
            bool    capture_from_raw_data : 1;     // FRAME_RData_1st
            uint8_t operation_mode : 2;            // OP_MODE
            bool    is_lifted : 1;                 // Lift_stat
            bool    raw_data_grab_is_raw_data : 1; // RData_1st
            uint8_t _reserved : 2;                 // 1 + Reserved
            bool    is_motion : 1;                 // MOT
        } b;
        uint8_t w;
    } motion;
    uint8_t observation;
    int16_t delta_x; // displacement on x directions. Unit: Count. (CPI * Count = Inch value)
    int16_t delta_y; // displacement on y directions.
} pmw33xx_report_t;

_Static_assert(sizeof(pmw33xx_report_t) == 6, "pmw33xx_report_t must be 6 bytes in size");
_Static_assert(sizeof((pmw33xx_report_t){0}.motion) == 1, "pmw33xx_report_t.motion must be 1 byte in size");

#if !defined(PMW33XX_CLOCK_SPEED)
#    define PMW33XX_CLOCK_SPEED 2000000
#endif

#if !defined(PMW33XX_SPI_DIVISOR)
#    ifdef __AVR__
#        define PMW33XX_SPI_DIVISOR (F_CPU / PMW33XX_CLOCK_SPEED)
#    else
#        define PMW33XX_SPI_DIVISOR 64
#    endif
#endif

#if !defined(PMW33XX_LIFTOFF_DISTANCE)
#    define PMW33XX_LIFTOFF_DISTANCE 0x02
#endif

#if !defined(ROTATIONAL_TRANSFORM_ANGLE)
#    define ROTATIONAL_TRANSFORM_ANGLE 0x00
#endif

#if ROTATIONAL_TRANSFORM_ANGLE > 127 || ROTATIONAL_TRANSFORM_ANGLE < (-127)
#    error ROTATIONAL_TRANSFORM_ANGLE has to be in the range of +/- 127 for all PMW33XX sensors.
#endif

#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

bool __attribute__((cold)) pmw33xx_init(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, const uint8_t *firmware_data, const uint16_t firmware_length, const uint8_t *firmware_signature);
uint16_t         pmw33xx_get_cpi(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg);
void             pmw33xx_set_cpi(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, uint16_t cpi);
pmw33xx_report_t pmw33xx_read_burst(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg);
uint8_t          pmw33xx_read(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, uint8_t addr);
bool             pmw33xx_write(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, uint8_t addr, uint8_t data);
report_mouse_t   pmw33xx_get_report(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg);
