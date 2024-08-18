/* Copyright 2020 Richard Sutherland <rich@brickbots.com>
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

void adns_begin(void);

void adns_end(void);

void adns_write(uint8_t reg_addr, uint8_t data);

uint8_t adns_read(uint8_t reg_addr);


int16_t convertDeltaToInt(uint8_t high, uint8_t low);

struct _motion_delta {
    int16_t delta_x;
    int16_t delta_y;
    int8_t motion_ind;
};
typedef struct _motion_delta motion_delta_t;

motion_delta_t readSensor(void);
