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

// this is for unit testing
#if defined(ENCODER_MOCK_SINGLE)
#    include "encoder/tests/mock.h"
#elif defined(ENCODER_MOCK_SPLIT)
#    include "encoder/tests/mock_split.h"
#else
#    include <gpio.h>
#    ifdef SPLIT_KEYBOARD
#        include "split_util.h"
#    endif
#endif

// for memcpy
#include <string.h>

#if !defined(ENCODER_RESOLUTIONS) && !defined(ENCODER_RESOLUTION)
#    define ENCODER_RESOLUTION 4
#endif

#if (!defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)) && (!defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B))
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B or ENCODERS_PAD_A_RIGHT and ENCODERS_PAD_B_RIGHT"
#endif

// on split keyboards, these are the pads and resolutions for the left half
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
#ifdef ENCODER_RESOLUTIONS
static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
#endif

#ifndef SPLIT_KEYBOARD
#    define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
#else
// if no pads for right half are defined, we assume the keyboard is symmetric (i.e. same pads)
#    ifndef ENCODERS_PAD_A_RIGHT
#        define ENCODERS_PAD_A_RIGHT ENCODERS_PAD_A
#    endif
#    ifndef ENCODERS_PAD_B_RIGHT
#        define ENCODERS_PAD_B_RIGHT ENCODERS_PAD_B
#    endif
#    if defined(ENCODER_RESOLUTIONS) && !defined(ENCODER_RESOLUTIONS_RIGHT)
#        define ENCODER_RESOLUTIONS_RIGHT ENCODER_RESOLUTIONS
#    endif

#    define NUMBER_OF_ENCODERS ((sizeof(encoders_pad_a) + sizeof(encoders_pad_a_right)) / sizeof(pin_t))
#    define NUMBER_OF_ENCODERS_LEFT (sizeof(encoders_pad_a) / sizeof(pin_t))
#    define NUMBER_OF_ENCODERS_RIGHT (sizeof(encoders_pad_a_right) / sizeof(pin_t))
static pin_t   encoders_pad_a_right[]      = ENCODERS_PAD_A_RIGHT;
static pin_t   encoders_pad_b_right[]      = ENCODERS_PAD_B_RIGHT;
#    ifdef ENCODER_RESOLUTIONS_RIGHT
static uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
#    endif
#endif

#ifndef ENCODER_DIRECTION_FLIP
#    define ENCODER_CLOCKWISE true
#    define ENCODER_COUNTER_CLOCKWISE false
#else
#    define ENCODER_CLOCKWISE false
#    define ENCODER_COUNTER_CLOCKWISE true
#endif
static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};

static uint8_t encoder_value[NUMBER_OF_ENCODERS] = {0};

__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) { return true; }

__attribute__((weak)) bool encoder_update_kb(uint8_t index, bool clockwise) { return encoder_update_user(index, clockwise); }

// number of encoders connected to this controller
static uint8_t numEncodersHere;
// index of the first encoder connected to this controller (only for right halves, this will be nonzero)
static uint8_t firstEncoderHere;
#ifdef SPLIT_KEYBOARD
// index of the first encoder connected to the other half
static uint8_t firstEncoderThere;
#endif
// the pads for this controller
static pin_t* pad_a;
static pin_t* pad_b;

void encoder_init(void) {
#ifndef SPLIT_KEYBOARD
    numEncodersHere  = NUMBER_OF_ENCODERS;
    pad_a            = encoders_pad_a;
    pad_b            = encoders_pad_b;
    firstEncoderHere = 0;
#else
    if (isLeftHand) {
        numEncodersHere   = NUMBER_OF_ENCODERS_LEFT;
        pad_a             = encoders_pad_a;
        pad_b             = encoders_pad_b;
        firstEncoderHere  = 0;
        firstEncoderThere = NUMBER_OF_ENCODERS_LEFT;
    } else {
        numEncodersHere   = NUMBER_OF_ENCODERS_RIGHT;
        pad_a             = encoders_pad_a_right;
        pad_b             = encoders_pad_b_right;
        firstEncoderHere  = NUMBER_OF_ENCODERS_LEFT;
        firstEncoderThere = 0;
    }
#endif

    for (int i = 0; i < numEncodersHere; i++) {
        setPinInputHigh(pad_a[i]);
        setPinInputHigh(pad_b[i]);

        encoder_state[firstEncoderHere + i] = (readPin(pad_a[i]) << 0) | (readPin(pad_b[i]) << 1);
    }
}

static bool encoder_update(int8_t index, uint8_t state) {
    bool changed = false;

#ifdef ENCODER_RESOLUTIONS
#    ifndef SPLIT_KEYBOARD
    int8_t resolution = encoder_resolutions[index];
#    else
    int8_t resolution = isLeftHand ? encoder_resolutions[index] : encoder_resolutions_right[index - NUMBER_OF_ENCODERS_LEFT];
#    endif
#else
    uint8_t resolution = ENCODER_RESOLUTION;
#endif
    encoder_pulses[index] += encoder_LUT[state & 0xF];
    if (encoder_pulses[index] >= resolution) {
        encoder_value[index]++;
        changed = true;
        encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
    }
    if (encoder_pulses[index] <= -resolution) {  // direction is arbitrary here, but this clockwise
        encoder_value[index]--;
        changed = true;
        encoder_update_kb(index, ENCODER_CLOCKWISE);
    }
    encoder_pulses[index] %= resolution;
#ifdef ENCODER_DEFAULT_POS
    if ((state & 0x3) == ENCODER_DEFAULT_POS) {
        encoder_pulses[index] = 0;
    }
#endif
    return changed;
}

bool encoder_read(void) {
    bool changed = false;
    for (uint8_t i = 0; i < numEncodersHere; i++) {
        encoder_state[firstEncoderHere + i] <<= 2;
        encoder_state[firstEncoderHere + i] |= (readPin(pad_a[i]) << 0) | (readPin(pad_b[i]) << 1);
        changed |= encoder_update(firstEncoderHere + i, encoder_state[firstEncoderHere + i]);
    }
    return changed;
}

#ifdef SPLIT_KEYBOARD
void last_encoder_activity_trigger(void);

void encoder_state_raw(uint8_t* slave_state) { memcpy(slave_state, &encoder_value[firstEncoderHere], sizeof(uint8_t) * numEncodersHere); }

void encoder_update_raw(uint8_t* slave_state) {
    bool changed = false;
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS - numEncodersHere; i++) {
        uint8_t index = firstEncoderThere + i;
        int8_t  delta = slave_state[i] - encoder_value[index];
        while (delta > 0) {
            delta--;
            encoder_value[index]++;
            changed = true;
            encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
        }
        while (delta < 0) {
            delta++;
            encoder_value[index]--;
            changed = true;
            encoder_update_kb(index, ENCODER_CLOCKWISE);
        }
    }

    // Update the last encoder input time -- handled external to encoder_read() when we're running a split
    if (changed) last_encoder_activity_trigger();
}
#endif
