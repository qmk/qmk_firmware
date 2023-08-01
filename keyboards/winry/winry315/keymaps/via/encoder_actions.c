/* Copyright 2020 Neil Brian Ramirez
 * Copyright 2021 drashna jael're (@drashna)
 * Copyright 2022 Sergey Vlasov (@sigprof)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "encoder_actions.h"

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)

#    ifndef ENCODER_TAP_DURATION_MS
#        define ENCODER_TAP_DURATION_MS 10
#    endif

#    define ENCODER_STATE_CW 0x01
#    define ENCODER_STATE_CCW 0x02

static uint8_t  encoder_state[NUM_ENCODERS] = {0};
static uint16_t encoder_timer[NUM_ENCODERS] = {0};
static keypos_t encoder_cw[NUM_ENCODERS]    = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[NUM_ENCODERS]   = ENCODERS_CCW_KEY;

static void exec_encoder_action(uint8_t index, bool clockwise, bool pressed) {
    // clang-format off
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = pressed,
        .time = timer_read(),
        .type = KEY_EVENT
    };
    // clang-format on
    action_exec(encoder_event);
}

void encoder_action_unregister(void) {
    for (int index = 0; index < NUM_ENCODERS; ++index) {
        if (encoder_state[index] && (timer_elapsed(encoder_timer[index]) >= ENCODER_TAP_DURATION_MS)) {
            bool clockwise       = !!(encoder_state[index] & ENCODER_STATE_CW);
            encoder_state[index] = 0;
            exec_encoder_action(index, clockwise, false);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    if (encoder_state[index]) {
        bool was_clockwise   = !!(encoder_state[index] & ENCODER_STATE_CW);
        encoder_state[index] = 0;
        exec_encoder_action(index, was_clockwise, false);
    }
    encoder_state[index] = clockwise ? ENCODER_STATE_CW : ENCODER_STATE_CCW;
    encoder_timer[index] = timer_read();
    exec_encoder_action(index, clockwise, true);
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    // don't return user actions, because they are in the keymap
    // encoder_update_user(index, clockwise);
    return true;
};

#endif
