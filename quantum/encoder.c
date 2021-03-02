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

#ifdef SPLIT_KEYBOARD
    #ifndef ENCODERS_PAD_A_RIGHT
    #   define ENCODERS_PAD_A_RIGHT ENCODERS_PAD_A
    #endif

    #ifndef ENCODERS_PAD_B_RIGHT
    #   define ENCODERS_PAD_B_RIGHT ENCODERS_PAD_B
    #endif

    #if defined(ENCODER_RESOLUTIONS) && !defined(ENCODER_RESOLUTIONS_RIGHT)
    #   define ENCODER_RESOLUTIONS_RIGHT ENCODER_RESOLUTIONS
    #endif

#   define NUMBER_OF_ENCODERS ((sizeof(encoders_pad_a) + sizeof(encoders_pad_a_right)) / sizeof(pin_t))
#   define NUMBER_OF_ENCODERS_LEFT (sizeof(encoders_pad_a) / sizeof(pin_t))
#   define NUMBER_OF_ENCODERS_RIGHT (sizeof(encoders_pad_a_right) / sizeof(pin_t))
    static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
	#ifdef ENCODER_RESOLUTIONS
		static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
	#endif
    static pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
    static pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
    #ifdef ENCODER_RESOLUTIONS_RIGHT
		static uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
	#endif
#else
#   define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
    static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
	#ifdef ENCODER_RESOLUTIONS
		static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
	#endif
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

__attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}

__attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) { encoder_update_user(index, clockwise); }

#ifdef SPLIT_KEYBOARD
    // row offsets for each hand
    static uint8_t thisHand, thatHand;
#endif

void encoder_init(void) {
#ifndef SPLIT_KEYBOARD
    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);

        encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
    }
#else
    thisHand = is_keyboard_left() ? 0 : NUMBER_OF_ENCODERS_LEFT;
    thisHandNum = is_keyboard_left() ? NUMBER_OF_ENCODERS_LEFT : NUMBER_OF_ENCODERS_RIGHT;
    thatHand = NUMBER_OF_ENCODERS - thisHand;

    pin_t pad_a[] = is_keyboard_left() ? encoders_pad_a : encoders_pad_a_right;
    pin_t pad_b[] = is_keyboard_left() ? encoders_pad_b : encoders_pad_b_right;
    
    for (int i = 0; i < thisHandNum; i++) {
        setPinInputHigh(pad_a[i]);
        setPinInputHigh(pad_b[i]);

        encoder_state[thisHand + i] = (readPin(pad_a[i]) << 0) | (readPin(pad_b[i]) << 1);
    }
#endif

}

static bool encoder_update(int8_t index, uint8_t state) {
    bool    changed = false;
    
#ifdef ENCODER_RESOLUTIONS
    int8_t resolution = is_keyboard_left() ? encoder_resolutions[index] : encoder_resolutions_right[index - NUMBER_OF_ENCODERS_LEFT];
#else
    int8_t resolution = ENCODER_RESOLUTION;
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
    return changed;
}

bool encoder_read(void) {
    bool changed = false;
#ifndef SPLIT_KEYBOARD
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_state[i] <<= 2;
        encoder_state[i] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        changed |= encoder_update(i, encoder_state[i]);
    }
#else
    pin_t pad_a[] = is_keyboard_left() ? encoders_pad_a : encoders_pad_a_right;
    pin_t pad_b[] = is_keyboard_left() ? encoders_pad_b : encoders_pad_b_right;

    for (uint8_t i = 0; i < thisHandNum; i++) {
        encoder_state[thisHand + i] <<= 2;
        encoder_state[thisHand + i] |= (readPin(pad_a[i]) << 0) | (readPin(pad_b[i]) << 1);
        changed |= encoder_update(thisHand + i, encoder_state[thisHand + i]);
    }
#endif
    return changed;
}

#ifdef SPLIT_KEYBOARD
void last_encoder_activity_trigger(void);

void encoder_state_raw(uint8_t* slave_state) { memcpy(slave_state, &encoder_value[thisHand], sizeof(uint8_t) * thisHandNum); }

void encoder_update_raw(uint8_t* slave_state) {
    bool changed = false;
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS - thisHandNum; i++) {
        uint8_t index = i + thatHand;
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
