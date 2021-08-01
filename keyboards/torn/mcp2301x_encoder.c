/*
 * Copyright 2020 Richard Titmuss <richard.titmuss@gmail.com>
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

#include QMK_KEYBOARD_H
#include "mcp2301x.h"

#ifndef ENCODER_RESOLUTION
#    define ENCODER_RESOLUTION 4
#endif

#define ENCODER_OFFSET NUMBER_OF_ENCODERS

#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(mcp2301x_pin_t))
static mcp2301x_pin_t encoders_pad_a[] = MCP2301X_ENCODERS_PAD_A;
static mcp2301x_pin_t encoders_pad_b[] = MCP2301X_ENCODERS_PAD_B;

#define ENCODER_CLOCKWISE true
#define ENCODER_COUNTER_CLOCKWISE false

static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};

static bool encoder_read_state(uint8_t *state) {
    mcp2301x_pin_t    pins;
    mcp2301x_status_t status = mcp2301x_readPins(&pins);
    if (status == 0) {
        for (uint8_t index = 0; index < NUMBER_OF_ENCODERS; index++) {
            state[index] = ((pins & encoders_pad_a[index]) > 0) << 0 | ((pins & encoders_pad_b[index]) > 0) << 1;
        }
        return true;
    }
    return false;
}

static void encoder_update(uint8_t index, uint8_t state) {
    encoder_pulses[index] += encoder_LUT[state & 0xF];
    if (encoder_pulses[index] >= ENCODER_RESOLUTION) {
        encoder_update_kb(ENCODER_OFFSET + index, ENCODER_CLOCKWISE);
    }
    if (encoder_pulses[index] <= -ENCODER_RESOLUTION) {  // direction is arbitrary here, but this clockwise
        encoder_update_kb(ENCODER_OFFSET + index, ENCODER_COUNTER_CLOCKWISE);
    }
    encoder_pulses[index] %= ENCODER_RESOLUTION;
}

/**
 * Read the secondary encoder over i2c
 */
void mcp2301x_encoder_read(void) {
    uint8_t state[NUMBER_OF_ENCODERS];
    if (encoder_read_state(state)) {
        for (uint8_t index = 0; index < NUMBER_OF_ENCODERS; index++) {
            encoder_state[index] <<= 2;
            encoder_state[index] |= state[index];
            encoder_update(index, encoder_state[index]);
        }
    }
}

/**
 * Initialize the secondary encoder over i2c
 */
void mcp2301x_encoder_init(void) { encoder_read_state(encoder_state); }
