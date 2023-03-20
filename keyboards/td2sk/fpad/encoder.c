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

#ifndef ENCODER_MAP_KEY_DELAY
#    include "action.h"
#    define ENCODER_MAP_KEY_DELAY TAP_CODE_DELAY
#endif

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

__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
    return true;
}

__attribute__((weak)) bool encoder_update_kb(uint8_t index, bool clockwise) {
    return encoder_update_user(index, clockwise);
}

__attribute__((weak)) bool should_process_encoder(void) {
    return is_keyboard_master();
}

void encoder_init(void) {
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
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);
    }
    encoder_wait_pullup_charge();
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
    }
}

#ifdef ENCODER_MAP_ENABLE
static void encoder_exec_mapping(uint8_t index, bool clockwise) {
    // The delays below cater for Windows and its wonderful requirements.
    action_exec(clockwise ? ENCODER_CW_EVENT(index, true) : ENCODER_CCW_EVENT(index, true));
#    if ENCODER_MAP_KEY_DELAY > 0
    wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

    action_exec(clockwise ? ENCODER_CW_EVENT(index, false) : ENCODER_CCW_EVENT(index, false));
#    if ENCODER_MAP_KEY_DELAY > 0
    wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0
}
#endif // ENCODER_MAP_ENABLE

static bool encoder_update(uint8_t index, uint8_t state) {
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
#ifdef SPLIT_KEYBOARD
            if (should_process_encoder())
#endif // SPLIT_KEYBOARD
#ifdef ENCODER_MAP_ENABLE
                encoder_exec_mapping(index, ENCODER_COUNTER_CLOCKWISE);
#else  // ENCODER_MAP_ENABLE
        encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
#endif // ENCODER_MAP_ENABLE
        }

#ifdef ENCODER_DEFAULT_POS
        if (encoder_pulses[i] <= -1) {
#else
    if (encoder_pulses[i] <= -resolution) { // direction is arbitrary here, but this clockwise
#endif
            encoder_value[index]--;
            changed = true;
#ifdef SPLIT_KEYBOARD
            if (should_process_encoder())
#endif // SPLIT_KEYBOARD
#ifdef ENCODER_MAP_ENABLE
                encoder_exec_mapping(index, ENCODER_CLOCKWISE);
#else  // ENCODER_MAP_ENABLE
        encoder_update_kb(index, ENCODER_CLOCKWISE);
#endif // ENCODER_MAP_ENABLE
        }
        encoder_pulses[i] %= resolution;
#ifdef ENCODER_DEFAULT_POS
        encoder_pulses[i] = 0;
    }
#endif
    return changed;
}

bool encoder_read(void) {
    bool changed = false;
    for (uint8_t i = 0; i < thisCount; i++) {
        uint8_t new_status = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        if ((encoder_state[i] & 0x3) != new_status) {
            encoder_state[i] <<= 2;
            encoder_state[i] |= new_status;
            changed |= encoder_update(i, encoder_state[i]);
        }
    }
    return changed;
}

#ifdef SPLIT_KEYBOARD
void last_encoder_activity_trigger(void);

void encoder_state_raw(uint8_t *slave_state) {
    memcpy(slave_state, &encoder_value[thisHand], sizeof(uint8_t) * thisCount);
}

void encoder_update_raw(uint8_t *slave_state) {
    bool changed = false;
    for (uint8_t i = 0; i < thatCount; i++) { // Note inverted logic -- we want the opposite side
        const uint8_t index = i + thatHand;
        int8_t        delta = slave_state[i] - encoder_value[index];
        while (delta > 0) {
            delta--;
            encoder_value[index]++;
            changed = true;
#    ifdef ENCODER_MAP_ENABLE
            encoder_exec_mapping(index, ENCODER_COUNTER_CLOCKWISE);
#    else  // ENCODER_MAP_ENABLE
            encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
#    endif // ENCODER_MAP_ENABLE
        }
        while (delta < 0) {
            delta++;
            encoder_value[index]--;
            changed = true;
#    ifdef ENCODER_MAP_ENABLE
            encoder_exec_mapping(index, ENCODER_CLOCKWISE);
#    else  // ENCODER_MAP_ENABLE
            encoder_update_kb(index, ENCODER_CLOCKWISE);
#    endif // ENCODER_MAP_ENABLE
        }
    }

    // Update the last encoder input time -- handled external to encoder_read() when we're running a split
    if (changed) last_encoder_activity_trigger();
}
#endif
