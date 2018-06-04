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

#include "encoder.h"
#include <stdbool.h>

#ifndef ENCODER_RESOLUTION
  #define ENCODER_RESOLUTION 4
#endif

#if !defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)
  #error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B"
#endif

static LINE_TYPE encoders_pad_a[NUMBER_OF_ENCODERS] = ENCODERS_PAD_A;
static LINE_TYPE encoders_pad_b[NUMBER_OF_ENCODERS] = ENCODERS_PAD_B;

static int8_t encoder_LUT[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };

static uint8_t encoder_state[NUMBER_OF_ENCODERS] = {0};
static int8_t encoder_value[NUMBER_OF_ENCODERS] = {0};

__attribute__ ((weak))
void encoder_update_user(bool clockwise) { }

__attribute__ ((weak))
void encoder_update_kb(bool clockwise) {
  encoder_update_user(clockwise);
}

void encoder_init(void) {
  for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
    setPadMode(encoders_pad_a[i], PAD_MODE_INPUT);
    setPadMode(encoders_pad_b[i], PAD_MODE_INPUT);

    encoder_state[i] = (readPad(encoders_pad_a[i]) << 0) | (readPad(encoders_pad_b[i]) << 1);
  }
}

void encoder_read(void) {
  for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
    encoder_state[i] <<= 2;
    encoder_state[i] |= (readPad(encoders_pad_a[i]) << 0) | (readPad(encoders_pad_b[i]) << 1);
    encoder_value[i] += encoder_LUT[encoder_state[i] & 0xF];
    if (encoder_value[i] >= ENCODER_RESOLUTION) {
        encoder_update_kb(COUNTRECLOCKWISE);
    }
    if (encoder_value[i] <= -ENCODER_RESOLUTION) { // direction is arbitrary here, but this clockwise
        encoder_update_kb(CLOCKWISE);
    }
    encoder_value[i] %= ENCODER_RESOLUTION;
  }
}
