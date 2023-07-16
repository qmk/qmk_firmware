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

#include <stdint.h>
#include "encoder.h"
#include "gpio.h"
#include "keyboard.h"
#include "action.h"
#include "keycodes.h"
#include "wait.h"

#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif

// for memcpy
#include <string.h>

#if !defined(ENCODER_RESOLUTIONS) && !defined(ENCODER_RESOLUTION)
#    define ENCODER_RESOLUTION 4
#endif

#if !defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B"
#endif

extern volatile bool isLeftHand;

static pin_t encoders_pad_a[NUM_ENCODERS_MAX_PER_SIDE] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[NUM_ENCODERS_MAX_PER_SIDE] = ENCODERS_PAD_B;

#ifdef ENCODER_RESOLUTIONS
static uint8_t encoder_resolutions[NUM_ENCODERS] = ENCODER_RESOLUTIONS;
#endif

#ifndef ENCODER_DIRECTION_FLIP
#    define ENCODER_CLOCKWISE true
#    define ENCODER_COUNTER_CLOCKWISE false
#else
#    define ENCODER_CLOCKWISE false
#    define ENCODER_COUNTER_CLOCKWISE true
#endif
static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state[NUM_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUM_ENCODERS] = {0};

// encoder counts
static uint8_t thisCount;
#ifdef SPLIT_KEYBOARD
// encoder offsets for each hand
static uint8_t thisHand, thatHand;
// encoder counts for each hand
static uint8_t thatCount;
#endif

static uint8_t encoder_value[NUM_ENCODERS] = {0};

__attribute__((weak)) void encoder_wait_pullup_charge(void) {
    wait_us(100);
}

__attribute__((weak)) void encoder_init_pin(uint8_t index, bool pad_b) {
    setPinInputHigh(pad_b ? encoders_pad_b[index] : encoders_pad_a[index]);
}

__attribute__((weak)) uint8_t encoder_read_pin(uint8_t index, bool pad_b) {
    return readPin(pad_b ? encoders_pad_b[index] : encoders_pad_a[index]) ? 1 : 0;
}

void encoder_driver_init(void) {
#ifdef SPLIT_KEYBOARD
    thisHand  = isLeftHand ? 0 : NUM_ENCODERS_LEFT;
    thatHand  = NUM_ENCODERS_LEFT - thisHand;
    thisCount = isLeftHand ? NUM_ENCODERS_LEFT : NUM_ENCODERS_RIGHT;
    thatCount = isLeftHand ? NUM_ENCODERS_RIGHT : NUM_ENCODERS_LEFT;
#else // SPLIT_KEYBOARD
    thisCount                = NUM_ENCODERS;
#endif

#ifdef ENCODER_TESTS
    // Annoying that we have to clear out values during initialisation here, but
    // because all the arrays are static locals, rerunning tests in the same
    // executable doesn't reset any of these. Kinda crappy having test-only code
    // here, but it's the simplest solution.
    memset(encoder_value, 0, sizeof(encoder_value));
    memset(encoder_state, 0, sizeof(encoder_state));
    memset(encoder_pulses, 0, sizeof(encoder_pulses));
    static const pin_t encoders_pad_a_left[] = ENCODERS_PAD_A;
    static const pin_t encoders_pad_b_left[] = ENCODERS_PAD_B;
    for (uint8_t i = 0; i < thisCount; i++) {
        encoders_pad_a[i] = encoders_pad_a_left[i];
        encoders_pad_b[i] = encoders_pad_b_left[i];
    }
#endif

#if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    // Re-initialise the pads if it's the right-hand side
    if (!isLeftHand) {
        static const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        static const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
        for (uint8_t i = 0; i < thisCount; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
        }
    }
#endif // defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)

    // Encoder resolutions is handled purely master-side, so concatenate the two arrays
#if defined(SPLIT_KEYBOARD) && defined(ENCODER_RESOLUTIONS)
#    if defined(ENCODER_RESOLUTIONS_RIGHT)
    static const uint8_t encoder_resolutions_right[NUM_ENCODERS_RIGHT] = ENCODER_RESOLUTIONS_RIGHT;
#    else  // defined(ENCODER_RESOLUTIONS_RIGHT)
    static const uint8_t encoder_resolutions_right[NUM_ENCODERS_RIGHT] = ENCODER_RESOLUTIONS;
#    endif // defined(ENCODER_RESOLUTIONS_RIGHT)
    for (uint8_t i = 0; i < NUM_ENCODERS_RIGHT; i++) {
        encoder_resolutions[NUM_ENCODERS_LEFT + i] = encoder_resolutions_right[i];
    }
#endif // defined(SPLIT_KEYBOARD) && defined(ENCODER_RESOLUTIONS)

    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_init_pin(i, false);
        encoder_init_pin(i, true);
    }
    encoder_wait_pullup_charge();
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_state[i] = (encoder_read_pin(i, false) << 0) | (encoder_read_pin(i, true) << 1);
    }
}

static bool encoder_handle_state_change(uint8_t index, uint8_t state) {
    bool    changed = false;
    uint8_t i       = index;

#ifdef ENCODER_RESOLUTIONS
    const uint8_t resolution = encoder_resolutions[i];
#else
    const uint8_t resolution = ENCODER_RESOLUTION;
#endif

#ifdef SPLIT_KEYBOARD
    index += thisHand;
#endif
    encoder_pulses[i] += encoder_LUT[state & 0xF];

#ifdef ENCODER_DEFAULT_POS
    if ((encoder_pulses[i] >= resolution) || (encoder_pulses[i] <= -resolution) || ((state & 0x3) == ENCODER_DEFAULT_POS)) {
        if (encoder_pulses[i] >= 1) {
#else
    if (encoder_pulses[i] >= resolution) {
#endif

            encoder_value[index]++;
            changed = true;
            encoder_queue_event(index, ENCODER_COUNTER_CLOCKWISE);
        }

#ifdef ENCODER_DEFAULT_POS
        if (encoder_pulses[i] <= -1) {
#else
    if (encoder_pulses[i] <= -resolution) { // direction is arbitrary here, but this clockwise
#endif
            encoder_value[index]--;
            changed = true;
            encoder_queue_event(index, ENCODER_CLOCKWISE);
        }
        encoder_pulses[i] %= resolution;
#ifdef ENCODER_DEFAULT_POS
        encoder_pulses[i] = 0;
    }
#endif
    return changed;
}

void encoder_driver_task(void) {
    for (uint8_t i = 0; i < thisCount; i++) {
        uint8_t new_status = (encoder_read_pin(i, false) << 0) | (encoder_read_pin(i, true) << 1);
        if ((encoder_state[i] & 0x3) != new_status) {
            encoder_state[i] <<= 2;
            encoder_state[i] |= new_status;
            encoder_handle_state_change(i, encoder_state[i]);
        }
    }
}
