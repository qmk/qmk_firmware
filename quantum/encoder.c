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
#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif

// for memcpy
#include <string.h>

#ifndef ENCODER_RESOLUTION
#    define ENCODER_RESOLUTION 4
#endif

#if !defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B"
#endif

static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[] = ENCODERS_PAD_B;

#ifdef ENCODERS_PAD_C
    #define NUMBER_OF_ENCODERS_AB (sizeof(encoders_pad_a) / sizeof(pin_t))
    #define NUMBER_OF_ENCODERS_C (sizeof(encoders_pad_c) / sizeof(pin_t))
    #define NUMBER_OF_ENCODERS (NUMBER_OF_ENCODERS_C * NUMBER_OF_ENCODERS_AB)
    static pin_t encoders_pad_c[] = ENCODERS_PAD_C;
#else
    #define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
    #define NUMBER_OF_ENCODERS_AB (sizeof(encoders_pad_a) / sizeof(pin_t))
#endif

static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state[NUMBER_OF_ENCODERS] = {0};

#ifdef SPLIT_KEYBOARD
// right half encoders come over as second set of encoders
static int8_t encoder_value[NUMBER_OF_ENCODERS * 2] = {0};
// row offsets for each hand
static uint8_t thisHand, thatHand;
#else
static int8_t encoder_value[NUMBER_OF_ENCODERS] = {0};
#endif

__attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}

__attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) { encoder_update_user(index, clockwise); }

void encoder_init(void) {
#if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    if (!isLeftHand) {
        const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
        for (uint8_t i = 0; i < NUMBER_OF_ENCODERS_AB; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
        }
    }
#endif

    #ifdef ENCODERS_PAD_C
        for (int i = 0; i < NUMBER_OF_ENCODERS_C; i++) {
            setPinOutput(encoders_pad_c[i]);
            if (i != 0)
                writePinHigh(encoders_pad_c[i]);
            else
                writePinLow(encoders_pad_c[i]);
        }

        for (int j = 0; j < NUMBER_OF_ENCODERS_C; j++) {
            writePinLow(encoders_pad_c[j]);
            wait_us(10);
            for (int i = 0; i < NUMBER_OF_ENCODERS_AB; i++) {
                setPinInputHigh(encoders_pad_a[i]);
                setPinInputHigh(encoders_pad_b[i]);

                encoder_state[j+(i*NUMBER_OF_ENCODERS_C)] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);

            }
            writePinHigh(encoders_pad_c[j]);
        }
        // need to disable these pins to prevent matrix activation
        for (int i = 0; i < NUMBER_OF_ENCODERS_AB; i++) {
            setPinInput(encoders_pad_a[i]);
            setPinInput(encoders_pad_b[i]);
        }
        for (int i = 0; i < NUMBER_OF_ENCODERS_C; i++) {
            setPinInputLow(encoders_pad_c[i]);
        }

    #else
        for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
            setPinInputHigh(encoders_pad_a[i]);
            setPinInputHigh(encoders_pad_b[i]);

            encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        }
    #endif

#ifdef SPLIT_KEYBOARD
    thisHand = isLeftHand ? 0 : NUMBER_OF_ENCODERS;
    thatHand = NUMBER_OF_ENCODERS - thisHand;
#endif
}

static void encoder_update(int8_t index, uint8_t state) {
    encoder_value[index] += encoder_LUT[state & 0xF];
    if (encoder_value[index] >= ENCODER_RESOLUTION) {
        encoder_update_kb(index, false);
    }
    if (encoder_value[index] <= -ENCODER_RESOLUTION) { // direction is arbitrary here, but this clockwise
        encoder_update_kb(index, true);
    }
    encoder_value[index] %= ENCODER_RESOLUTION;
}

void encoder_read(void) {
#ifdef ENCODERS_PAD_C
    // setup row pins to act as C pins for the encoders, prep the first one
    for (int i = 0; i < NUMBER_OF_ENCODERS_C; i++) {
            setPinOutput(encoders_pad_c[i]);
            if (i != 0)
                writePinHigh(encoders_pad_c[i]);
            else
                writePinLow(encoders_pad_c[i]);
    }
    // pull these back up because we disabled them earlier
    for (int i = 0; i < NUMBER_OF_ENCODERS_AB; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);
    }
    for (int j = 0; j < NUMBER_OF_ENCODERS_C; j++) {
        writePinLow(encoders_pad_c[j]);
        wait_us(10);
        for (int i = 0; i < NUMBER_OF_ENCODERS_AB; i++) {
            encoder_state[j+(i*NUMBER_OF_ENCODERS_C)] <<= 2;
            encoder_state[j+(i*NUMBER_OF_ENCODERS_C)] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
#if SPLIT_KEYBOARD
            encoder_update(j+(i*NUMBER_OF_ENCODERS_C) + thisHand, encoder_state[j+(i*NUMBER_OF_ENCODERS_C)]);
#else
            encoder_update(j+(i*NUMBER_OF_ENCODERS_C), encoder_state[j+(i*NUMBER_OF_ENCODERS_C)]);
#endif
        }
        writePinHigh(encoders_pad_c[j]);    
    }
    // need to disable these pins again to prevent matrix activation
    for (int i = 0; i < NUMBER_OF_ENCODERS_AB; i++) {
        setPinInput(encoders_pad_a[i]);
        setPinInput(encoders_pad_b[i]);
    }
    // revert row pins back to input
    for (int i = 0; i < NUMBER_OF_ENCODERS_C; i++) {
        setPinInputLow(encoders_pad_c[i]);
    }

#else
        for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
            encoder_state[i] <<= 2;
            encoder_state[i] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
#if SPLIT_KEYBOARD
            encoder_update(i + thisHand, encoder_state[i]);
#else
            encoder_update(i, encoder_state[i]);
#endif
        }
#endif
}

#ifdef SPLIT_KEYBOARD
void encoder_state_raw(uint8_t* slave_state) { memcpy(slave_state, encoder_state, sizeof(encoder_state)); }

void encoder_update_raw(uint8_t* slave_state) {
    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_update(i + thatHand, slave_state[i]);
    }
}
#endif
