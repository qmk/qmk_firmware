// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_led_matrix.h"
#include "led_matrix.h"

bool process_led_matrix(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_BACKLIGHT_ON:
                led_matrix_enable();
                return false;
            case QK_BACKLIGHT_OFF:
                led_matrix_disable();
                return false;
            case QK_BACKLIGHT_DOWN:
                led_matrix_decrease_val();
                return false;
            case QK_BACKLIGHT_UP:
                led_matrix_increase_val();
                return false;
            case QK_BACKLIGHT_TOGGLE:
                led_matrix_toggle();
                return false;
            case QK_BACKLIGHT_STEP:
                led_matrix_step();
                return false;
        }
    }

    return true;
}
