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

#if !defined(ENCODER_RESOLUTIONS) && !defined(ENCODER_RESOLUTION)
#    define ENCODER_RESOLUTION 4
#endif

#if !defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B"
#endif

#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
#ifdef ENCODER_RESOLUTIONS
static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
#endif

#ifndef ENCODER_DIRECTION_FLIP
#    define ENCODER_CLOCKWISE         true
#    define ENCODER_COUNTER_CLOCKWISE false
#else
#    define ENCODER_CLOCKWISE         false
#    define ENCODER_COUNTER_CLOCKWISE true
#endif
static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};

#ifdef SPLIT_KEYBOARD
// right half encoders come over as second set of encoders
static uint8_t encoder_value[NUMBER_OF_ENCODERS * 2] = {0};
// row offsets for each hand
static uint8_t thisHand, thatHand;
#else
static uint8_t encoder_value[NUMBER_OF_ENCODERS] = {0};
#endif

__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) { return true; }

__attribute__((weak)) bool encoder_update_kb(uint8_t index, bool clockwise) { return encoder_update_user(index, clockwise); }

static void encoder_update_handler(uint8_t index, bool clockwise) {
#ifdef ENCODER_KEYMAPPING
#    ifdef ENCODER_PROCESS_CALLBACKS
    if (encoder_update_kb(index, clockwise))
#    endif
    {
        encoder_update_keymapping(index, clockwise);
    }
#else
    encoder_update_kb(index, clockwise);
#endif
}

void encoder_init(void) {
#if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    if (!isLeftHand) {
        const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
#    if defined(ENCODER_RESOLUTIONS_RIGHT)
        const uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
#    endif
        for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
#    if defined(ENCODER_RESOLUTIONS_RIGHT)
            encoder_resolutions[i] = encoder_resolutions_right[i];
#    endif
        }
    }
#endif

    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);

        encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
    }
#ifdef ENCODER_KEYMAPPING
    encoder_init_keymapping();
#endif
#ifdef SPLIT_KEYBOARD
    thisHand = isLeftHand ? 0 : NUMBER_OF_ENCODERS;
    thatHand = NUMBER_OF_ENCODERS - thisHand;
#endif
}

static bool encoder_update(uint8_t index, uint8_t state) {
    bool    changed = false;
    uint8_t i       = index;

#ifdef ENCODER_RESOLUTIONS
    uint8_t resolution = encoder_resolutions[i];
#else
    uint8_t resolution = ENCODER_RESOLUTION;
#endif

#ifdef SPLIT_KEYBOARD
    index += thisHand;
#endif
    encoder_pulses[i] += encoder_LUT[state & 0xF];
    if (encoder_pulses[i] >= resolution) {
        encoder_value[index]++;
        changed = true;
        encoder_update_handler(index, ENCODER_COUNTER_CLOCKWISE);
    }
    if (encoder_pulses[i] <= -resolution) {  // direction is arbitrary here, but this clockwise
        encoder_value[index]--;
        changed = true;
        encoder_update_handler(index, ENCODER_CLOCKWISE);
    }
    encoder_pulses[i] %= resolution;
#ifdef ENCODER_DEFAULT_POS
    if ((state & 0x3) == ENCODER_DEFAULT_POS) {
        encoder_pulses[i] = 0;
    }
#endif

#ifdef ENCODER_KEYMAPPING
    encoder_map_cleanup();
#endif
    return changed;
}

bool encoder_read(void) {
    bool changed = false;
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_state[i] <<= 2;
        encoder_state[i] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        changed |= encoder_update(i, encoder_state[i]);
    }
    return changed;
}

#ifdef SPLIT_KEYBOARD
void last_encoder_activity_trigger(void);

void encoder_state_raw(uint8_t* slave_state) { memcpy(slave_state, &encoder_value[thisHand], sizeof(uint8_t) * NUMBER_OF_ENCODERS); }

void encoder_update_raw(uint8_t* slave_state) {
    bool changed = false;
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        uint8_t index = i + thatHand;
        int8_t  delta = slave_state[i] - encoder_value[index];
        while (delta > 0) {
            delta--;
            encoder_value[index]++;
            changed = true;
            encoder_update_handler(index, ENCODER_COUNTER_CLOCKWISE);
        }
        while (delta < 0) {
            delta++;
            encoder_value[index]--;
            changed = true;
            encoder_update_handler(index, ENCODER_CLOCKWISE);
        }
    }

    // Update the last encoder input time -- handled external to encoder_read() when we're running a split
    if (changed) last_encoder_activity_trigger();
}
#endif

#ifdef ENCODER_KEYMAPPING
#    ifdef SPLIT_KEYBOARD
#        define NUM_ENCODERS (NUMBER_OF_ENCODERS * 2)
#    else
#        define NUM_ENCODERS (NUMBER_OF_ENCODERS)
#    endif
uint8_t    encoder_keypos[NUM_ENCODERS][2][2] = { ENCODER_KEYMAPPING };
keyevent_t encoder_ccw[NUM_ENCODERS];
keyevent_t encoder_cw[NUM_ENCODERS];


void encoder_init_keymapping(void) {
    for (uint8_t index = 0; index < NUM_ENCODERS; index++) {
        encoder_cw[index].key.row  = encoder_keypos[index][0][0];
        encoder_cw[index].key.col  = encoder_keypos[index][0][1];
        encoder_cw[index].pressed  = false;
        encoder_cw[index].time     = 1;
        encoder_ccw[index].key.row = encoder_keypos[index][1][0];
        encoder_ccw[index].key.col = encoder_keypos[index][1][1];
        encoder_ccw[index].pressed = false;
        encoder_ccw[index].time    = 1;
    }
}

void encoder_map_cleanup(void) {
    for (uint8_t index = 0; index < NUM_ENCODERS; index++) {
        if (IS_PRESSED(encoder_ccw[index])) {
            encoder_ccw[index].pressed = false;
            encoder_ccw[index].time    = (timer_read() | 1);
            action_exec(encoder_ccw[index]);
        }
        if (IS_PRESSED(encoder_cw[index])) {
            encoder_cw[index].pressed = false;
            encoder_cw[index].time    = (timer_read() | 1);
            action_exec(encoder_cw[index]);
        }
    }
}

bool encoder_update_keymapping(uint8_t index, bool clockwise) {
    if (clockwise) {
        encoder_cw[index].pressed = true;
        encoder_cw[index].time    = (timer_read() | 1);
        action_exec(encoder_cw[index]);
    } else {
        encoder_ccw[index].pressed = true;
        encoder_ccw[index].time    = (timer_read() | 1);
        action_exec(encoder_ccw[index]);
    }
    return true;
}
#endif
