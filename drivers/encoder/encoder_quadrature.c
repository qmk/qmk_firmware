// Copyright 2018 Jack Humbert <jack.humb@gmail.com>
// Copyright 2018-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

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

#undef ENCODER_DEFAULT_PIN_API_IMPL
#if defined(ENCODERS_PAD_A) && defined(ENCODERS_PAD_B)
// Inform the quadrature driver that it needs to implement pin init/read functions
#    define ENCODER_DEFAULT_PIN_API_IMPL
#endif

extern volatile bool isLeftHand;

__attribute__((weak)) void    encoder_quadrature_init_pin(uint8_t index, bool pad_b);
__attribute__((weak)) uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b);

#ifdef ENCODER_DEFAULT_PIN_API_IMPL

static pin_t encoders_pad_a[NUM_ENCODERS_MAX_PER_SIDE] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[NUM_ENCODERS_MAX_PER_SIDE] = ENCODERS_PAD_B;

__attribute__((weak)) void encoder_wait_pullup_charge(void) {
    wait_us(100);
}

__attribute__((weak)) void encoder_quadrature_init_pin(uint8_t index, bool pad_b) {
    pin_t pin = pad_b ? encoders_pad_b[index] : encoders_pad_a[index];
    if (pin != NO_PIN) {
        gpio_set_pin_input_high(pin);
    }
}

__attribute__((weak)) uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b) {
    pin_t pin = pad_b ? encoders_pad_b[index] : encoders_pad_a[index];
    if (pin != NO_PIN) {
        return gpio_read_pin(pin) ? 1 : 0;
    }
    return 0;
}

#endif // ENCODER_DEFAULT_PIN_API_IMPL

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

__attribute__((weak)) void encoder_quadrature_post_init_kb(void) {
    extern void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);
    // Unused normally, but can be used for things like setting up pin-change interrupts in keyboard code.
    // During the interrupt, read the pins then call `encoder_handle_read()` with the pin states and it'll queue up an encoder event if needed.
}

void encoder_quadrature_post_init(void) {
#ifdef ENCODER_DEFAULT_PIN_API_IMPL
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_quadrature_init_pin(i, false);
        encoder_quadrature_init_pin(i, true);
    }
    encoder_wait_pullup_charge();
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_state[i] = (encoder_quadrature_read_pin(i, false) << 0) | (encoder_quadrature_read_pin(i, true) << 1);
    }
#else
    memset(encoder_state, 0, sizeof(encoder_state));
#endif

    encoder_quadrature_post_init_kb();
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
    memset(encoder_state, 0, sizeof(encoder_state));
    memset(encoder_pulses, 0, sizeof(encoder_pulses));
    const pin_t encoders_pad_a_left[] = ENCODERS_PAD_A;
    const pin_t encoders_pad_b_left[] = ENCODERS_PAD_B;
    for (uint8_t i = 0; i < thisCount; i++) {
        encoders_pad_a[i] = encoders_pad_a_left[i];
        encoders_pad_b[i] = encoders_pad_b_left[i];
    }
#endif

#if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    // Re-initialise the pads if it's the right-hand side
    if (!isLeftHand) {
        const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
        for (uint8_t i = 0; i < thisCount; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
        }
    }
#endif // defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)

    // Encoder resolutions is defined differently in config.h, so concatenate
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

    encoder_quadrature_post_init();
}

static void encoder_handle_state_change(uint8_t index, uint8_t state) {
    uint8_t i = index;

#ifdef SPLIT_KEYBOARD
    index += thisHand;
#endif

#ifdef ENCODER_RESOLUTIONS
    const uint8_t resolution = encoder_resolutions[index];
#else
    const uint8_t resolution = ENCODER_RESOLUTION;
#endif

    encoder_pulses[i] += encoder_LUT[state & 0xF];

#ifdef ENCODER_DEFAULT_POS
    if ((encoder_pulses[i] >= resolution) || (encoder_pulses[i] <= -resolution) || ((state & 0x3) == ENCODER_DEFAULT_POS)) {
        if (encoder_pulses[i] >= 1) {
#else
    if (encoder_pulses[i] >= resolution) {
#endif

            encoder_queue_event(index, ENCODER_COUNTER_CLOCKWISE);
        }

#ifdef ENCODER_DEFAULT_POS
        if (encoder_pulses[i] <= -1) {
#else
    if (encoder_pulses[i] <= -resolution) { // direction is arbitrary here, but this clockwise
#endif
            encoder_queue_event(index, ENCODER_CLOCKWISE);
        }
        encoder_pulses[i] %= resolution;
#ifdef ENCODER_DEFAULT_POS
        encoder_pulses[i] = 0;
    }
#endif
}

void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state) {
    uint8_t state = pin_a_state | (pin_b_state << 1);
    if ((encoder_state[index] & 0x3) != state) {
        encoder_state[index] <<= 2;
        encoder_state[index] |= state;
        encoder_handle_state_change(index, encoder_state[index]);
    }
}

__attribute__((weak)) void encoder_driver_task(void) {
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_quadrature_handle_read(i, encoder_quadrature_read_pin(i, false), encoder_quadrature_read_pin(i, true));
    }
}
