/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "util.h"

void encoder_init(void);
bool encoder_read(void);

bool encoder_update_kb(uint8_t index, bool clockwise);
bool encoder_update_user(uint8_t index, bool clockwise);

#ifdef SPLIT_KEYBOARD

void encoder_state_raw(uint8_t* slave_state);
void encoder_update_raw(uint8_t* slave_state);

#    if defined(ENCODERS_PAD_A_RIGHT)
#        define NUM_ENCODERS_LEFT (sizeof(((pin_t[])ENCODERS_PAD_A)) / sizeof(pin_t))
#        define NUM_ENCODERS_RIGHT (sizeof(((pin_t[])ENCODERS_PAD_A_RIGHT)) / sizeof(pin_t))
#    else
#        define NUM_ENCODERS_LEFT (sizeof(((pin_t[])ENCODERS_PAD_A)) / sizeof(pin_t))
#        define NUM_ENCODERS_RIGHT NUM_ENCODERS_LEFT
#    endif
#    define NUM_ENCODERS (NUM_ENCODERS_LEFT + NUM_ENCODERS_RIGHT)

#else // SPLIT_KEYBOARD

#    define NUM_ENCODERS (sizeof(((pin_t[])ENCODERS_PAD_A)) / sizeof(pin_t))
#    define NUM_ENCODERS_LEFT NUM_ENCODERS
#    define NUM_ENCODERS_RIGHT 0

#endif // SPLIT_KEYBOARD

#ifndef NUM_ENCODERS
#    define NUM_ENCODERS 0
#    define NUM_ENCODERS_LEFT 0
#    define NUM_ENCODERS_RIGHT 0
#endif // NUM_ENCODERS

#define NUM_ENCODERS_MAX_PER_SIDE MAX(NUM_ENCODERS_LEFT, NUM_ENCODERS_RIGHT)

#ifdef ENCODER_MAP_ENABLE
#    define ENCODER_CCW_CW(ccw, cw) \
        { (cw), (ccw) }
extern const uint16_t encoder_map[][NUM_ENCODERS][2];
#endif // ENCODER_MAP_ENABLE
