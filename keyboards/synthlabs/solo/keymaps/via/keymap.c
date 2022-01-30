// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN,
        KC_VOLD, KC_MUTE, KC_VOLU,
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN
    ),
    [1] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______
    )
};

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)

#ifdef ENCODERS
static uint8_t encoder_state[] = {0};
static keypos_t encoder_cw[] = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[] = ENCODERS_CCW_KEY;
#endif

void encoder_action_unregister(void) {
#ifdef ENCODERS
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
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
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
#endif
}

void matrix_scan_user(void) {
    encoder_action_unregister();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
}

#endif
