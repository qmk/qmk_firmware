/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keycodes.h"
#include "matrix.h"
#include "analog_matrix_eeconfig.h"
#include "analog_matrix_type.h"

#define FULL_TRAVEL_UNIT 40

#ifndef DEFAULT_ACTUATION_POINT
#    define DEFAULT_ACTUATION_POINT 20
#endif

#ifndef DEFAULT_RAPID_TRIGGER_SENSITIVITY
#    define DEFAULT_RAPID_TRIGGER_SENSITIVITY 4
#endif

#ifndef DEFAULT_ZERO_TRAVEL_VALUE
#    define DEFAULT_ZERO_TRAVEL_VALUE 3000
#endif

#ifndef DEFAULT_FULL_RANGE
#    define DEFAULT_FULL_RANGE 900
#endif

#define DEFAULT_FULL_TRAVEL_VALUE (DEFAULT_ZERO_TRAVEL_VALUE - DEFAULT_FULL_RANGE)

#ifndef VALID_ANALOG_RAW_VALUE_MIN
#    define VALID_ANALOG_RAW_VALUE_MIN 1200
#endif

#ifndef VALID_ANALOG_RAW_VALUE_MAX
#    define VALID_ANALOG_RAW_VALUE_MAX 3500
#endif

#ifndef STATIC_HYSTERESIS
#    define STATIC_HYSTERESIS 5
#endif

#ifndef RAPID_TRIGGER_TICK
#    define RAPID_TRIGGER_TICK 10
#endif

#ifndef MIN_ACTUATION
#    define MIN_ACTUATION 5
#endif

#ifndef ZERO_TRAVEL_DEAD_ZONE
#    define ZERO_TRAVEL_DEAD_ZONE 20
#endif

#ifndef BOTTOM_DEAD_ZONE
#    define BOTTOM_DEAD_ZONE 38
#endif

#ifndef BOTTOM_JITTER
#    define BOTTOM_JITTER 80
#endif

#define TRAVEL_SCALE 6

#ifndef ANALOG_DEBOUCE_TIME
#    define ANALOG_DEBOUCE_TIME 3
#endif

// Threshold value when the magnet switch is not installed
#ifndef ABNORMAL_ANALOG_RAW_THRESHOLD_VALUE
#    define ABNORMAL_ANALOG_RAW_THRESHOLD_VALUE 3250
#endif

//
#ifndef AUTO_CALIB_FULL_TRAVEL_THRESHOLD_VALUE
#    define AUTO_CALIB_FULL_TRAVEL_THRESHOLD_VALUE (DEFAULT_ZERO_TRAVEL_VALUE - DEFAULT_FULL_RANGE + 100)
#endif

#ifndef AUTO_CALIB_ZERO_TRAVEL_JITTER_VALUE
#    define AUTO_CALIB_ZERO_TRAVEL_JITTER_VALUE 50
#endif

#ifndef AUTO_CALIB_FULL_TRAVEL_JITTER_VALUE
#    define AUTO_CALIB_FULL_TRAVEL_JITTER_VALUE 100
#endif

#ifndef AUTO_CALIB_ZERO_TRAVEL_THRESHOLD_VALUE
#    define AUTO_CALIB_ZERO_TRAVEL_THRESHOLD_VALUE (DEFAULT_FULL_RANGE - AUTO_CALIB_FULL_TRAVEL_JITTER_VALUE)
#endif

#ifndef AUTO_CALIB_VALID_RELASING_TIME
#    define AUTO_CALIB_VALID_RELASING_TIME 1000
#endif

void analog_matrix_init(void);
void analog_matrix_eeconfig_init(void);
bool update_raw_value(uint8_t row, uint8_t col, uint16_t value);
void update_travel_configs(void);
void update_key_config(uint8_t row, uint8_t col);

void analog_matrix_set_mins(uint16_t *min);
void analog_matrix_set_maxs(uint16_t *max);

uint8_t  analog_matrix_get_travel(uint8_t row, uint8_t col);
uint8_t analog_matrix_get_key_mode(uint8_t row, uint8_t col);
bool    analog_matrix_get_key_state(uint8_t row, uint8_t col);
bool    analog_matrix_calibrating(void);
matrix_row_t analog_matrix_get_row(uint8_t row);
void    analog_matrix_rx(uint8_t *data, uint8_t length);
void    analog_matrix_task(void);
void    analog_matrix_indicator(void);
