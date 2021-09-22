/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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
#include "report.h"
#include "i2c_master.h"

#ifndef PIMORONI_TRACKBALL_ADDRESS
#    define PIMORONI_TRACKBALL_ADDRESS 0x0A
#endif
#ifndef PIMORONI_TRACKBALL_INTERVAL_MS
#    define PIMORONI_TRACKBALL_INTERVAL_MS 8
#endif
#ifndef PIMORONI_TRACKBALL_SCALE
#    define PIMORONI_TRACKBALL_SCALE 5
#endif
#ifndef PIMORONI_TRACKBALL_DEBOUNCE_CYCLES
#    define PIMORONI_TRACKBALL_DEBOUNCE_CYCLES 20
#endif
#ifndef PIMORONI_TRACKBALL_ERROR_COUNT
#    define PIMORONI_TRACKBALL_ERROR_COUNT 10
#endif

#ifndef PIMORONI_TRACKBALL_TIMEOUT
#    define PIMORONI_TRACKBALL_TIMEOUT 100
#endif

#ifndef PIMORONI_TRACKBALL_DEBUG_INTERVAL
#    define PIMORONI_TRACKBALL_DEBUG_INTERVAL 100
#endif

typedef struct {
    uint8_t left;
    uint8_t right;
    uint8_t up;
    uint8_t down;
    uint8_t click;
} pimoroni_data_t;

void         pimironi_trackball_device_init(void);
void         pimoroni_trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
int16_t      pimoroni_trackball_get_offsets(uint8_t negative_dir, uint8_t positive_dir, uint8_t scale);
void         pimoroni_trackball_adapt_values(int8_t* mouse, int16_t* offset);
float        pimoroni_trackball_get_precision(void);
void         pimoroni_trackball_set_precision(float precision);
i2c_status_t read_pimoroni_trackball(pimoroni_data_t* data);
