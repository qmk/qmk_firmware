// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_rgb_matrix.h"
#include "rgb_matrix.h"
#include "action_util.h"
#include "keycodes.h"
#include "modifiers.h"

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_TRIGGER_ON_KEYDOWN
    if (record->event.pressed) {
#else
    if (!record->event.pressed) {
#endif
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        switch (keycode) {
            case QK_RGB_MATRIX_ON:
                rgb_matrix_enable();
                return false;
            case QK_RGB_MATRIX_OFF:
                rgb_matrix_disable();
                return false;
            case QK_RGB_MATRIX_TOGGLE:
                rgb_matrix_toggle();
                return false;
            case QK_RGB_MATRIX_MODE_NEXT:
                if (shifted) {
                    rgb_matrix_step_reverse();
                } else {
                    rgb_matrix_step();
                }
                return false;
            case QK_RGB_MATRIX_MODE_PREVIOUS:
                if (shifted) {
                    rgb_matrix_step();
                } else {
                    rgb_matrix_step_reverse();
                }
                return false;
            case QK_RGB_MATRIX_HUE_UP:
                if (shifted) {
                    rgb_matrix_decrease_hue();
                } else {
                    rgb_matrix_increase_hue();
                }
                return false;
            case QK_RGB_MATRIX_HUE_DOWN:
                if (shifted) {
                    rgb_matrix_increase_hue();
                } else {
                    rgb_matrix_decrease_hue();
                }
                return false;
            case QK_RGB_MATRIX_SATURATION_UP:
                if (shifted) {
                    rgb_matrix_decrease_sat();
                } else {
                    rgb_matrix_increase_sat();
                }
                return false;
            case QK_RGB_MATRIX_SATURATION_DOWN:
                if (shifted) {
                    rgb_matrix_increase_sat();
                } else {
                    rgb_matrix_decrease_sat();
                }
                return false;
            case QK_RGB_MATRIX_VALUE_UP:
                if (shifted) {
                    rgb_matrix_decrease_val();
                } else {
                    rgb_matrix_increase_val();
                }
                return false;
            case QK_RGB_MATRIX_VALUE_DOWN:
                if (shifted) {
                    rgb_matrix_increase_val();
                } else {
                    rgb_matrix_decrease_val();
                }
                return false;
            case QK_RGB_MATRIX_SPEED_UP:
                if (shifted) {
                    rgb_matrix_decrease_speed();
                } else {
                    rgb_matrix_increase_speed();
                }
                return false;
            case QK_RGB_MATRIX_SPEED_DOWN:
                if (shifted) {
                    rgb_matrix_increase_speed();
                } else {
                    rgb_matrix_decrease_speed();
                }
                return false;
        }
    }

    return true;
}
