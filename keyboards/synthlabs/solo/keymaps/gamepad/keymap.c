// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "joystick.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                    JS_BUTTON0,JS_BUTTON1,JS_BUTTON2,JS_BUTTON3,JS_BUTTON4,JS_BUTTON5,JS_BUTTON6,
          KC_NO,   JS_BUTTON7,  KC_NO,
                                    JS_BUTTON0,JS_BUTTON1,JS_BUTTON2,JS_BUTTON3,JS_BUTTON4,JS_BUTTON5,JS_BUTTON6
    )
};

#if defined(JOYSTICK_ENABLE) && defined(ENCODER_ENABLE)

int16_t joystick_position = 0;
int16_t pulses_per_revolution = 24;     // Depends on encoder model. Usually 18ppr or 24ppr for Bourns EC11s.
int16_t full_joystick_value = 32767;    // Equivalent to max value of int16. +full_joystick_value is +1.0 axis output. -full_joystick_value is -1.0 axis output.
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    joystick_position += (clockwise ? 2 : -2) * (full_joystick_value / pulses_per_revolution);  // +2 and -2 are used, since +1.0 and -1.0 axis output refers to positions at half of a full rotation

    if (joystick_position != joystick_status.axes[0]) {
        joystick_status.axes[0] = joystick_position;
        joystick_status.status |= JS_UPDATED;
    }
    return true;
}

#endif
