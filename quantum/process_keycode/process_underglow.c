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
            case RGB_MODE_PLAIN:
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                return false;
#if defined(RGBLIGHT_EFFECT_BREATHING)
            case RGB_MODE_BREATHE:
                rgblight_mode(RGBLIGHT_MODE_BREATHING);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_RAINBOW_MOOD)
            case RGB_MODE_RAINBOW:
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_RAINBOW_SWIRL)
            case RGB_MODE_SWIRL:
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_SNAKE)
            case RGB_MODE_SNAKE:
                rgblight_mode(RGBLIGHT_MODE_SNAKE);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_KNIGHT)
            case RGB_MODE_KNIGHT:
                rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_CHRISTMAS)
            case RGB_MODE_XMAS:
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_STATIC_GRADIENT)
            case RGB_MODE_GRADIENT:
                rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_RGB_TEST)
            case RGB_MODE_RGBTEST:
                rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
                return false;
#endif
#if defined(RGBLIGHT_EFFECT_TWINKLE)
            case RGB_MODE_TWINKLE:
                rgblight_mode(RGBLIGHT_MODE_TWINKLE);
                return false;
#endif
        }
    }

    return true;
}
