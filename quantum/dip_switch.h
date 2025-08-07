/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2018 Drashna Jaelre (Christopher Courtney) <drashna@live.com>
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

#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"
#include "util.h"

#if defined(DIP_SWITCH_PINS)
#    define NUM_DIP_SWITCHES ARRAY_SIZE(((pin_t[])DIP_SWITCH_PINS))
#elif defined(DIP_SWITCH_MATRIX_GRID)
typedef struct matrix_intersection_t {
    uint8_t row;
    uint8_t col;
} matrix_intersection_t;
#    define NUM_DIP_SWITCHES ARRAY_SIZE(((matrix_intersection_t[])DIP_SWITCH_MATRIX_GRID))
#endif

#ifndef NUM_DIP_SWITCHES
#    define NUM_DIP_SWITCHES 0
#endif

bool dip_switch_update_kb(uint8_t index, bool active);
bool dip_switch_update_user(uint8_t index, bool active);
bool dip_switch_update_mask_user(uint32_t state);
bool dip_switch_update_mask_kb(uint32_t state);

void dip_switch_read(bool forced);

void dip_switch_init(void);
void dip_switch_task(void);

#ifdef DIP_SWITCH_MAP_ENABLE
#    define NUM_DIP_STATES 2
#    define DIP_SWITCH_OFF_ON(off, on) \
        { (off), (on) }
extern const uint16_t dip_switch_map[NUM_DIP_SWITCHES][NUM_DIP_STATES];
#endif // DIP_SWITCH_MAP_ENABLE
