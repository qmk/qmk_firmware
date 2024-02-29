/* Copyright 2023 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "matrix.h"
#include "eeconfig.h"

typedef struct PACKED {
    uint8_t  actuation_mode;                              // 0: normal board-wide APC, 1: Rapid trigger from specific board-wide actuation point, 2: Rapid trigger from resting point
    uint16_t mode_0_actuation_threshold;                  // threshold for key press in mode 0
    uint16_t mode_0_release_threshold;                    // threshold for key release in mode 0
    uint16_t mode_1_initial_deadzone_offset;              // threshold for key press in mode 1
    uint8_t  mode_1_actuation_offset;                     // offset for key press in mode 1 and 2 (1-255)
    uint8_t  mode_1_release_offset;                       // offset for key release in mode 1 and 2 (1-255)
    uint16_t bottoming_reading[MATRIX_ROWS][MATRIX_COLS]; // bottoming reading
} eeprom_ec_config_t;

typedef struct {
    uint8_t  actuation_mode;                                                    // 0: normal board-wide APC, 1: Rapid trigger from specific board-wide actuation point (it can be very near that baseline noise and be "full travel")
    uint16_t mode_0_actuation_threshold;                                        // threshold for key press in mode 0
    uint16_t mode_0_release_threshold;                                          // threshold for key release in mode 0
    uint16_t mode_1_initial_deadzone_offset;                                    // threshold for key press in mode 1 (initial deadzone)
    uint16_t rescaled_mode_0_actuation_threshold[MATRIX_ROWS][MATRIX_COLS];     // threshold for key press in mode 0 rescaled to actual scale
    uint16_t rescaled_mode_0_release_threshold[MATRIX_ROWS][MATRIX_COLS];       // threshold for key release in mode 0 rescaled to actual scale
    uint16_t rescaled_mode_1_initial_deadzone_offset[MATRIX_ROWS][MATRIX_COLS]; // threshold for key press in mode 1 (initial deadzone) rescaled to actual scale
    uint8_t  mode_1_actuation_offset;                                           // offset for key press in mode 1 (1-255)
    uint8_t  mode_1_release_offset;                                             // offset for key release in mode 1 (1-255)
    uint16_t extremum[MATRIX_ROWS][MATRIX_COLS];                                // extremum values for mode 1
    uint16_t noise_floor[MATRIX_ROWS][MATRIX_COLS];                             // noise floor detected during startup
    bool     bottoming_calibration;                                             // calibration mode for bottoming out values (true: calibration mode, false: normal mode)
    bool     bottoming_calibration_starter[MATRIX_ROWS][MATRIX_COLS];           // calibration mode for bottoming out values (true: calibration mode, false: normal mode)
    uint16_t bottoming_reading[MATRIX_ROWS][MATRIX_COLS];                       // bottoming reading
} ec_config_t;

// Check if the size of the reserved persistent memory is the same as the size of struct eeprom_ec_config_t
_Static_assert(sizeof(eeprom_ec_config_t) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");

extern eeprom_ec_config_t eeprom_ec_config;

extern ec_config_t ec_config;

void init_row(void);
void init_amux(void);
void select_amux_channel(uint8_t channel, uint8_t col);
void disable_unused_amux(uint8_t channel);
void discharge_capacitor(void);
void charge_capacitor(uint8_t row);

int      ec_init(void);
void     ec_noise_floor(void);
bool     ec_matrix_scan(matrix_row_t current_matrix[]);
uint16_t ec_readkey_raw(uint8_t channel, uint8_t row, uint8_t col);
bool     ec_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value);
void     ec_print_matrix(void);

uint16_t rescale(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
