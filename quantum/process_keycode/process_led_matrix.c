// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_led_matrix.h"
#include "led_matrix.h"

bool process_led_matrix(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_BACKLIGHT_ON: // TODO: Remove backlight keycodes
            case QK_LED_MATRIX_ON:
                led_matrix_enable();
                return false;
            case QK_BACKLIGHT_OFF:
            case QK_LED_MATRIX_OFF:
                led_matrix_disable();
                return false;
            case QK_BACKLIGHT_TOGGLE:
            case QK_LED_MATRIX_TOGGLE:
                led_matrix_toggle();
                return false;
            case QK_BACKLIGHT_STEP:
            case QK_LED_MATRIX_MODE_NEXT:
                led_matrix_step();
                return false;
            case QK_LED_MATRIX_MODE_PREVIOUS:
                led_matrix_step_reverse();
                return false;
            case QK_BACKLIGHT_UP:
            case QK_LED_MATRIX_BRIGHTNESS_UP:
                led_matrix_increase_val();
                return false;
            case QK_BACKLIGHT_DOWN:
            case QK_LED_MATRIX_BRIGHTNESS_DOWN:
                led_matrix_decrease_val();
                return false;
            case QK_LED_MATRIX_SPEED_UP:
                led_matrix_increase_speed();
                return false;
            case QK_LED_MATRIX_SPEED_DOWN:
                led_matrix_decrease_speed();
                return false;
        }
    }

    return true;
}
