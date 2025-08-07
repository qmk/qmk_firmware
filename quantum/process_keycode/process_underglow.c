// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_underglow.h"
#if defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif
#include "action_util.h"
#include "keycodes.h"
#include "modifiers.h"

// TODO: Remove this
#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
#    include "rgb_matrix.h"
#endif

bool process_underglow(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#if defined(RGBLIGHT_ENABLE) || (defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES))
        const uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
#endif

        switch (keycode) {
            case QK_UNDERGLOW_TOGGLE:
#if defined(RGBLIGHT_ENABLE)
                rgblight_toggle();
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                rgb_matrix_toggle();
#endif
                return false;
            case QK_UNDERGLOW_MODE_NEXT:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_step_reverse();
                } else {
                    rgblight_step();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_step_reverse();
                } else {
                    rgb_matrix_step();
                }
#endif
                return false;
            case QK_UNDERGLOW_MODE_PREVIOUS:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_step();
                } else {
                    rgb_matrix_step_reverse();
                }
#endif
                return false;
            case QK_UNDERGLOW_HUE_UP:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_decrease_hue();
                } else {
                    rgblight_increase_hue();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_decrease_hue();
                } else {
                    rgb_matrix_increase_hue();
                }
#endif
                return false;
            case QK_UNDERGLOW_HUE_DOWN:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_increase_hue();
                } else {
                    rgb_matrix_decrease_hue();
                }
#endif
                return false;
            case QK_UNDERGLOW_SATURATION_UP:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_decrease_sat();
                } else {
                    rgblight_increase_sat();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_decrease_sat();
                } else {
                    rgb_matrix_increase_sat();
                }
#endif
                return false;
            case QK_UNDERGLOW_SATURATION_DOWN:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_increase_sat();
                } else {
                    rgb_matrix_decrease_sat();
                }
#endif
                return false;
            case QK_UNDERGLOW_VALUE_UP:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_decrease_val();
                } else {
                    rgblight_increase_val();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_decrease_val();
                } else {
                    rgb_matrix_increase_val();
                }
#endif
                return false;
            case QK_UNDERGLOW_VALUE_DOWN:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_increase_val();
                } else {
                    rgb_matrix_decrease_val();
                }
#endif
                return false;
            case QK_UNDERGLOW_SPEED_UP:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_decrease_speed();
                } else {
                    rgblight_increase_speed();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_decrease_speed();
                } else {
                    rgb_matrix_increase_speed();
                }
#endif
                return false;
            case QK_UNDERGLOW_SPEED_DOWN:
#if defined(RGBLIGHT_ENABLE)
                if (shifted) {
                    rgblight_increase_speed();
                } else {
                    rgblight_decrease_speed();
                }
#endif

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                if (shifted) {
                    rgb_matrix_increase_speed();
                } else {
                    rgb_matrix_decrease_speed();
                }
#endif
                return false;
        }
    }

    return true;
}
