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
#include "quantum.h"
#include "util.h"

bool dip_switch_update_kb(uint8_t index, bool active);
bool dip_switch_update_user(uint8_t index, bool active);
bool dip_switch_update_mask_user(uint32_t state);
bool dip_switch_update_mask_kb(uint32_t state);

void dip_switch_init(void);
void dip_switch_read(bool forced);

#ifdef DIP_SWITCH_MATRIX_GRID
typedef struct matrix_index_t {
    uint8_t row;
    uint8_t col;
} matrix_index_t;
#endif

#ifdef SPLIT_KEYBOARD
void dip_switch_state_raw(bool *slave_state);
void dip_switch_update_raw(bool *slave_state);
#    if defined(DIP_SWITCH_PINS)
#        if defined(DIP_SWITCH_PINS_RIGHT)
#            define NUM_DIP_SWITCHES_LEFT (ARRAY_SIZE((pin_t[])DIP_SWITCH_PINS))
#            define NUM_DIP_SWITCHES_RIGHT (ARRAY_SIZE((pin_t[])DIP_SWITCH_PINS_RIGHT))
#        else
#            define NUM_DIP_SWITCHES_LEFT (ARRAY_SIZE((pin_t[])DIP_SWITCH_PINS))
#            define NUM_DIP_SWITCHES_RIGHT NUM_DIP_SWITCHES_LEFT
#        endif
#    elif defined(DIP_SWITCH_MATRIX_GRID)
#        if defined(DIP_SWITCH_MATRIX_GRID_RIGHT)
#            define NUM_DIP_SWITCHES_LEFT (ARRAY_SIZE((pin_t[])DIP_SWITCH_MATRIX_GRID))
#            define NUM_DIP_SWITCHES_RIGHT (ARRAY_SIZE((pin_t[])DIP_SWITCH_MATRIX_GRID_RIGHT)))
#        else
#            define NUM_DIP_SWITCHES_LEFT (ARRAY_SIZE((pin_t[])DIP_SWITCH_MATRIX_GRID))
#            define NUM_DIP_SWITCHES_RIGHT NUM_DIP_SWITCHES_LEFT
#        endif
#    endif
#    define NUM_DIP_SWITCHES (NUM_DIP_SWITCHES_LEFT + NUM_DIP_SWITCHES_RIGHT)
#else // SPLIT_KEYBOARD
#    if defined(DIP_SWITCH_PINS)
#        define NUM_DIP_SWITCHES (ARRAY_SIZE((pin_t[])DIP_SWITCH_PINS))
#    elif defined(DIP_SWITCH_MATRIX_GRID)
#        define NUM_DIP_SWITCHES (ARRAY_SIZE((pin_t[])DIP_SWITCH_MATRIX_GRID))
#    endif
#    define NUM_DIP_SWITCHES_LEFT NUM_DIP_SWITCHES
#    define NUM_DIP_SWITCHES_RIGHT 0
#endif // SPLIT_KEYBOARD

#ifndef NUM_DIP_SWITCHES
#    define NUM_DIP_SWITCHES 0
#    define NUM_DIP_SWITCHES_LEFT 0
#    define NUM_DIP_SWITCHES_RIGHT 0
#endif // NUM_ENCODERS

#define NUM_DIP_SWITCHES_MAX_PER_SIDE MAX(NUM_DIP_SWITCHES_LEFT, NUM_DIP_SWITCHES_RIGHT)
