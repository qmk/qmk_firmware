// Copyright 2018 Jack Humbert <jack.humb@gmail.com>
// Copyright 2018-2023 Nick Brassel (@tzarc)
// Copyright 2025 @esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdint.h>
#include "encoder.h"
#include "quantum.h"
#include "./drivers/encoder_dynamic_res.h"

#ifdef ENCODER_ENABLE

static uint8_t encoder_resolutions[NUM_ENCODERS] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
static uint8_t encoder_state[NUM_ENCODERS]       = {0};
static int8_t  encoder_pulses[NUM_ENCODERS]      = {0};
static int8_t  encoder_LUT[]                     = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static void dynamic_res_encoder_handle_state_change(uint8_t index, uint8_t state) {
    uint8_t i = index;

    const uint8_t resolution = encoder_resolutions[i];

    static uint32_t timer = 0;
    if (timer_elapsed32(timer) > 1000) {
        for (uint8_t j = 0; j < NUM_ENCODERS; ++j) {
            dprintf("enc[%u] res: %d pul: %d\n", j, encoder_resolutions[j], encoder_pulses[j]);
        }
        timer = timer_read32();
    }

    encoder_pulses[i] += encoder_LUT[state & 0xF];

#    ifdef ENCODER_DEFAULT_POS
    if ((encoder_pulses[i] >= resolution) || (encoder_pulses[i] <= -resolution) || ((state & 0x3) == ENCODER_DEFAULT_POS)) {
        if (encoder_pulses[i] >= 1) {
#    else
    if (encoder_pulses[i] >= resolution) {
#    endif

            encoder_queue_event(i, ENCODER_COUNTER_CLOCKWISE);
        }

#    ifdef ENCODER_DEFAULT_POS
        if (encoder_pulses[i] <= -1) {
#    else
    if (encoder_pulses[i] <= -resolution) { // direction is arbitrary here, but this clockwise
#    endif
            encoder_queue_event(i, ENCODER_CLOCKWISE);
        }
        encoder_pulses[i] %= resolution;
#    ifdef ENCODER_DEFAULT_POS
        encoder_pulses[i] = 0;
    }
#    endif
}

void dynamic_res_encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state) {
    uint8_t state = pin_a_state | (pin_b_state << 1);
    if ((encoder_state[index] & 0x3) != state) {
        encoder_state[index] <<= 2;
        encoder_state[index] |= state;
        dynamic_res_encoder_handle_state_change(index, encoder_state[index]);
    }
}

void dynamic_res_encoder_update_res(uint8_t index, uint8_t res) {
    switch (res) {
        case 0:
            encoder_resolutions[index] = 1;
            break;
        case 1:
            encoder_resolutions[index] = 2;
            break;
        case 2:
            encoder_resolutions[index] = 4;
            break;
        case 3:
            encoder_resolutions[index] = 8;
            break;
        default:
            encoder_resolutions[index] = 4;
    }
    encoder_state[index]  = 0;
    encoder_pulses[index] = 0;
}
#endif
