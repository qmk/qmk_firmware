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
#include "pointing_device.h"

#if defined(POINTING_DEVICE_DRIVER_pmw3360)
#    include "pmw3360.h"
#elif defined(POINTING_DEVICE_DRIVER_pmw3389)
#    include "pmw3389.h"
#endif

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

// Support single and plural spellings
#ifndef PMW33XX_CS_PINS
#    ifndef PMW33XX_CS_PIN
#        ifdef POINTING_DEVICE_CS_PIN
#            define PMW33XX_CS_PIN POINTING_DEVICE_CS_PIN
#            define PMW33XX_CS_PINS \
                { PMW33XX_CS_PIN }
#        else
#            error "No chip select pin defined -- missing PMW33XX_CS_PIN or PMW33XX_CS_PINS"
#        endif
#    else
#        define PMW33XX_CS_PINS \
            { PMW33XX_CS_PIN }
#    endif
#endif

// Support single spelling and default to be the same as left side
#if !defined(PMW33XX_CS_PINS_RIGHT)
#    if !defined(PMW33XX_CS_PIN_RIGHT)
#        define PMW33XX_CS_PIN_RIGHT PMW33XX_CS_PIN
#    endif
#    define PMW33XX_CS_PINS_RIGHT \
        { PMW33XX_CS_PIN_RIGHT }
#endif

// Defines so the old variable names are swapped by the appropiate value on each half
#define cs_pins (is_keyboard_left() ? cs_pins_left : cs_pins_right)
#define in_burst (is_keyboard_left() ? in_burst_left : in_burst_right)
#define pmw33xx_number_of_sensors (is_keyboard_left() ? ARRAY_SIZE((pin_t[])PMW33XX_CS_PINS) : ARRAY_SIZE((pin_t[])PMW33XX_CS_PINS_RIGHT))

#if PMW33XX_CPI > PMW33XX_CPI_MAX || PMW33XX_CPI < PMW33XX_CPI_MIN || (PMW33XX_CPI % PMW33XX_CPI_STEP) != 0U
#    pragma message "PMW33XX_CPI has to be in the range of " STR(PMW33XX_CPI_MAX) "-" STR(PMW33XX_CPI_MIN) " in increments of " STR(PMW33XX_CPI_STEP) ". But it is " STR(PMW33XX_CPI) "."
#    error Use correct PMW33XX_CPI value.
#endif

#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

#define pmw3360_pointing_device_driver pmw33xx_pointing_device_driver;
#define pmw3389_pointing_device_driver pmw33xx_pointing_device_driver;
const pointing_device_driver_t pmw33xx_pointing_device_driver;

/**
 * @brief Initializes the given sensor so it is in a working state and ready to
 * be polled for data.
 *
 * @param sensor Index of the sensors chip select pin
 * @return true Initialization was a success
 * @return false Initialization failed, do not proceed operation
 */
bool __attribute__((cold)) pmw33xx_init(uint8_t sensor);

/**
 * @brief Gets the currently set CPI value from the sensor. CPI is often
 * refereed to as the sensors sensitivity.
 *
 * @param sensor Index of the sensors chip select pin
 * @return uint16_t Current CPI value of the sensor
 */
uint16_t pmw33xx_get_cpi(uint8_t sensor);

/**
 * @brief Sets the given CPI value for the given PMW33XX sensor. CIP is often
 * refereed to as the sensors sensitivity. Values outside of the allow range are
 * constrained into legal values.
 *
 * @param sensor Index of the sensors chip select pin
 * @param cpi CPI value to set, legal range depends on the PMW sensor type
 */
void pmw33xx_set_cpi(uint8_t sensor, uint16_t cpi);

/**
 * @brief Sets the given CPI value to all registered PMW33XX sensors. CPI is
 * often refereed to as the sensors sensitivity. Values outside of the allow
 * range are constrained into legal values.
 *
 * @param sensor Index of the sensors chip select pin
 * @param cpi CPI value to set, legal range depends on the PMW sensor type
 */
void pmw33xx_set_cpi_all_sensors(uint16_t cpi);

/**
 * @brief Reads and clears the current delta, and motion register values on the
 * given sensor.
 *
 * @param sensor Index of the sensors chip select pin
 * @return pmw33xx_report_t Current values of the sensor, if errors occurred all
 * fields are set to zero
 */
pmw33xx_report_t pmw33xx_read_burst(uint8_t sensor);

/**
 * @brief Read one byte of data from the given register on the sensor
 *
 * @param sensor Index of the sensors chip select pin
 * @param reg_addr Register address to read from
 * @return uint8_t
 */
uint8_t pmw33xx_read(uint8_t sensor, uint8_t reg_addr);

/**
 * @brief Writes one byte of data to the given register on the sensor
 *
 * @param sensor Index of the sensors chip select pin
 * @param reg_addr Registers address to write to
 * @param data Data to write to the register
 * @return true Write was a success
 * @return false Write failed, do not proceed operation
 */
bool pmw33xx_write(uint8_t sensor, uint8_t reg_addr, uint8_t data);

void           pmw33xx_init_wrapper(void);
void           pmw33xx_set_cpi_wrapper(uint16_t cpi);
uint16_t       pmw33xx_get_cpi_wrapper(void);
report_mouse_t pmw33xx_get_report(report_mouse_t mouse_report);
