// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "joystick.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                    JS_BUTTON0,JS_BUTTON1,JS_BUTTON2,JS_BUTTON3,JS_BUTTON4,JS_BUTTON5,JS_BUTTON6,
        JS_BUTTON8, MO(1), JS_BUTTON7,
                                    JS_BUTTON0,JS_BUTTON1,JS_BUTTON2,JS_BUTTON3,JS_BUTTON4,JS_BUTTON5,JS_BUTTON6
    ),
    [1] = LAYOUT_all(
                                    JS_BUTTON9, _______,JS_BUTTON10, _______,JS_BUTTON11, _______,JS_BUTTON12,
        _______, _______, _______,
                                    JS_BUTTON10, _______,JS_BUTTON9, _______,JS_BUTTON11, _______,JS_BUTTON12
    ),
};

#if defined(ENCODER_ENABLE)

enum encoder_direction {
    DIRECTION_CW,
    DIRECTION_CCW
};

#ifdef ENCODERS
int16_t encoder_stationary_release_delay_ms = 25;

static uint8_t encoder_state[] = {0};
static keypos_t encoder_cw[] = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[] = ENCODERS_CCW_KEY;
static uint16_t encoder_last_update_time[] = {0};
static enum encoder_direction encoder_last_direction[] = {DIRECTION_CW};
#endif

void encoder_action_unregister(uint8_t index) {
#ifdef ENCODERS
    if (encoder_state[index]) {
        keyevent_t encoder_event = (keyevent_t) {
            .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
            .pressed = false,
            .time = (timer_read() | 1)
        };
        encoder_state[index] = 0;
        action_exec(encoder_event);
    }
#endif
}

void encoder_action_register(uint8_t index, bool clockwise) {
#ifdef ENCODERS
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };

    // Record the time that the encoder was detected as rotated
    encoder_last_update_time[index] = timer_read();

    // Check if the encoder direction has reversed, and if so unregister the opposite direction's event
    enum encoder_direction new_direction = clockwise ? DIRECTION_CW : DIRECTION_CCW;
    if (encoder_last_direction[index] != new_direction) {
        encoder_action_unregister(index);
    }
    encoder_last_direction[index] = new_direction;

    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
#endif
}

void matrix_scan_user(void) {
    // If an encoder has been stationary for encoder_stationary_release_delay_ms, then unregister its event
    uint16_t current_time = timer_read();
    for (int index = 0; index < ENCODERS; ++index) {
        uint16_t elapsed_time_since_last_update = current_time - encoder_last_update_time[index];
        if (elapsed_time_since_last_update >= encoder_stationary_release_delay_ms) {
            encoder_action_unregister(index);
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
}

#endif
