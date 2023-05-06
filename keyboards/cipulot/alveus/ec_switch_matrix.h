/* Copyright 2023 Cipulot
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

#include "matrix.h"

typedef struct {
    uint16_t low_threshold_matrix[MATRIX_ROWS][MATRIX_COLS];  // threshold for key release
    uint16_t high_threshold_matrix[MATRIX_ROWS][MATRIX_COLS]; // threshold for key press
} ecsm_config_t;

ecsm_config_t ecsm_config;

int  ecsm_init(ecsm_config_t const* const ecsm_config);
int  ecsm_update(ecsm_config_t const* const ecsm_config);
bool ecsm_matrix_scan(matrix_row_t current_matrix[]);
void ecsm_print_matrix(void);

typedef struct _apc_config_t {
    bool    apc_enabled;
    uint8_t apc_actuation_level;
    uint8_t apc_deactuation_level;
} apc_config;

apc_config apc;
