// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_underglow.h"
#include "rgblight.h"
#include "action_util.h"
#include "keycodes.h"
#include "modifiers.h"

bool process_underglow(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        switch (keycode) {
            case QK_UNDERGLOW_TOGGLE:
                rgblight_toggle();
                return false;
            case QK_UNDERGLOW_MODE_NEXT:
                if (shifted) {
                    rgblight_step_reverse();
                } else {
                    rgblight_step();
                }
                return false;
            case QK_UNDERGLOW_MODE_PREVIOUS:
                if (shifted) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
                return false;
            case QK_UNDERGLOW_HUE_UP:
                if (shifted) {
                    rgblight_decrease_hue();
                } else {
                    rgblight_increase_hue();
                }
                return false;
            case QK_UNDERGLOW_HUE_DOWN:
                if (shifted) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                return false;
            case QK_UNDERGLOW_SATURATION_UP:
                if (shifted) {
                    rgblight_decrease_sat();
                } else {
                    rgblight_increase_sat();
                }
                return false;
            case QK_UNDERGLOW_SATURATION_DOWN:
                if (shifted) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                return false;
            case QK_UNDERGLOW_VALUE_UP:
                if (shifted) {
                    rgblight_decrease_val();
                } else {
                    rgblight_increase_val();
                }
                return false;
            case QK_UNDERGLOW_VALUE_DOWN:
                if (shifted) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                return false;
            case QK_UNDERGLOW_SPEED_UP:
                if (shifted) {
                    rgblight_decrease_speed();
                } else {
                    rgblight_increase_speed();
                }
                return false;
            case QK_UNDERGLOW_SPEED_DOWN:
                if (shifted) {
                    rgblight_increase_speed();
                } else {
                    rgblight_decrease_speed();
                }
                return false;
        }
    }

    return true;
}
