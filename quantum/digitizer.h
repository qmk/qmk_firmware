/* Copyright 2021
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

#include "quantum.h"

#include <stdint.h>

enum digitizer_status { DZ_INITIALIZED = 1, DZ_UPDATED = 2 };

typedef struct {
    int8_t  tipswitch;
    int8_t  inrange;
    uint8_t id;
    float   x;
    float   y;
    uint8_t status : 2;
} digitizer_t;

extern digitizer_t digitizer;

digitizer_t digitizer_get_report(void);

void digitizer_set_report(digitizer_t newDigitizerReport);

void digitizer_task(void);

void host_digitizer_send(digitizer_t *digitizer);
