/* Copyright 2021 Gompa (@Gompa)
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

#ifndef PAW3204_SCLK_PIN
#    error "No clock pin defined -- missing PAW3204_SCLK_PIN"
#endif
#ifndef PAW3204_SDIO_PIN
#    error "No data pin defined -- missing PAW3204_SDIO_PIN"
#endif

typedef struct {
    int16_t x;
    int16_t y;
    bool    isMotion;
} report_paw3204_t;

/**
 * @brief Initializes the sensor so it is in a working state and ready to
 * be polled for data.
 *
 * @return true Initialization was a success
 * @return false Initialization failed, do not proceed operation
 */
void paw3204_init(void);

/**
 * @brief Reads and clears the current delta, and motion register values on the
 * given sensor.
 *
 * @return pmw33xx_report_t Current values of the sensor, if errors occurred all
 * fields are set to zero
 */

report_paw3204_t paw3204_read(void);
/**
 * @brief Sets the given CPI value the sensor. CPI is  often refereed to
 * as the sensors sensitivity. Values outside of the allowed range are
 * constrained into legal values.
 *
 * @param cpi CPI value to set
 */
void paw3204_set_cpi(uint16_t cpi);

/**
 * @brief Gets the currently set CPI value from the sensor. CPI is often
 * refereed to as the sensors sensitivity.
 *
 * @return uint16_t Current CPI value of the sensor
 */
uint16_t paw3204_get_cpi(void);
