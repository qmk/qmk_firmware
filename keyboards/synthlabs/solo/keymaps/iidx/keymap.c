// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "joystick.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                    JS_0,JS_1,JS_2,JS_3,JS_4,JS_5,JS_6,
        JS_8, MO(1), JS_7,
                                    JS_0,JS_1,JS_2,JS_3,JS_4,JS_5,JS_6
    ),
    [1] = LAYOUT_all(
                                    JS_9,JS_0,JS_10, _______,JS_11,JS_1,JS_12,
        _______, _______, _______,
                                    JS_10,JS_0,JS_9, _______,JS_11,JS_1,JS_12
    ),
};

#if defined(ENCODER_MAP_ENABLE)
/* The amount of time the encoder has to remain stationary, before unregistering encoder bindings */
uint16_t encoder_stationary_release_delay_ms = 25;

uint16_t encoder_last_update_time = 0;

enum {
    CCW_JOYSTICK_BUTTON = 8,
    CW_JOYSTICK_BUTTON = 7,
};

enum {
    CCW_MACRO = SAFE_RANGE,
    CW_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CCW_MACRO:
            unregister_joystick_button(CW_JOYSTICK_BUTTON);
            register_joystick_button(CCW_JOYSTICK_BUTTON);
            encoder_last_update_time = timer_read(); /* Update the last time that the encoder was detected as rotated */
            return false;
        case CW_MACRO:
            unregister_joystick_button(CCW_JOYSTICK_BUTTON);
            register_joystick_button(CW_JOYSTICK_BUTTON);
            encoder_last_update_time = timer_read();  /* Update the last time that the encoder was detected as rotated */
            return false;
        default:
            return true;
    }
}

void housekeeping_task_user(void) {
    uint16_t current_time = timer_read();
    uint16_t elapsed_time_since_last_update = current_time - encoder_last_update_time;

    /* If an encoder has been stationary for encoder_stationary_release_delay_ms, then unregister the joystick buttons for both directions */
    if (elapsed_time_since_last_update >= encoder_stationary_release_delay_ms) {
        unregister_joystick_button(CCW_JOYSTICK_BUTTON);
        unregister_joystick_button(CW_JOYSTICK_BUTTON);
    }
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(
                CCW_MACRO,
                CW_MACRO
            ) },
    [1] =   { ENCODER_CCW_CW(_______, _______) },
};
#endif
