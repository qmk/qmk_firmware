/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "process_rgb.h"
#include "rgb.h"

typedef void (*rgb_func_pointer)(void);

/**
 * Wrapper for inc/dec rgb keycode
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
static void __attribute__((noinline)) handleKeycodeRGB(const uint8_t is_shifted, const rgb_func_pointer inc_func, const rgb_func_pointer dec_func) {
    if (is_shifted) {
        dec_func();
    } else {
        inc_func();
    }
}

/**
 * Wrapper for animation mode
 *   - if not in animation family -> jump to that animation
 *   - otherwise -> wrap round animation speed
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
static void __attribute__((noinline, unused)) handleKeycodeRGBMode(const uint8_t start, const uint8_t end) {
    if ((start <= rgblight_get_mode()) && (rgblight_get_mode() < end)) {
        rgblight_step();
    } else {
        rgblight_mode(start);
    }
}

/**
 * Handle keycodes for both rgblight and rgbmatrix
 */
bool process_rgb(const uint16_t keycode, const keyrecord_t *record) {
#ifndef SPLIT_KEYBOARD
    if (record->event.pressed) {
#else
    // Split keyboards need to trigger on key-up for edge-case issue
    if (!record->event.pressed) {
#endif
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        switch (keycode) {
            case RGB_TOG:
                rgblight_toggle();
                return false;
            case RGB_MODE_FORWARD:
                handleKeycodeRGB(shifted, rgblight_step, rgblight_step_reverse);
                return false;
            case RGB_MODE_REVERSE:
                handleKeycodeRGB(shifted, rgblight_step_reverse, rgblight_step);
                return false;
            case RGB_HUI:
                handleKeycodeRGB(shifted, rgblight_increase_hue, rgblight_decrease_hue);
                return false;
            case RGB_HUD:
                handleKeycodeRGB(shifted, rgblight_decrease_hue, rgblight_increase_hue);
                return false;
            case RGB_SAI:
                handleKeycodeRGB(shifted, rgblight_increase_sat, rgblight_decrease_sat);
                return false;
            case RGB_SAD:
                handleKeycodeRGB(shifted, rgblight_decrease_sat, rgblight_increase_sat);
                return false;
            case RGB_VAI:
                handleKeycodeRGB(shifted, rgblight_increase_val, rgblight_decrease_val);
                return false;
            case RGB_VAD:
                handleKeycodeRGB(shifted, rgblight_decrease_val, rgblight_increase_val);
                return false;
            case RGB_SPI:
                handleKeycodeRGB(shifted, rgblight_increase_speed, rgblight_decrease_speed);
                return false;
            case RGB_SPD:
                handleKeycodeRGB(shifted, rgblight_decrease_speed, rgblight_increase_speed);
                return false;
            case RGB_MODE_PLAIN:
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                return false;
            case RGB_MODE_BREATHE:
#ifdef RGBLIGHT_EFFECT_BREATHING
                handleKeycodeRGBMode(RGBLIGHT_MODE_BREATHING, RGBLIGHT_MODE_BREATHING_end);
#endif
                return false;
            case RGB_MODE_RAINBOW:
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
                handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_MOOD, RGBLIGHT_MODE_RAINBOW_MOOD_end);
#endif
                return false;
            case RGB_MODE_SWIRL:
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
                handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_SWIRL, RGBLIGHT_MODE_RAINBOW_SWIRL_end);
#endif
                return false;
            case RGB_MODE_SNAKE:
#ifdef RGBLIGHT_EFFECT_SNAKE
                handleKeycodeRGBMode(RGBLIGHT_MODE_SNAKE, RGBLIGHT_MODE_SNAKE_end);
#endif
                return false;
            case RGB_MODE_KNIGHT:
#ifdef RGBLIGHT_EFFECT_KNIGHT
                handleKeycodeRGBMode(RGBLIGHT_MODE_KNIGHT, RGBLIGHT_MODE_KNIGHT_end);
#endif
                return false;
            case RGB_MODE_XMAS:
#ifdef RGBLIGHT_EFFECT_CHRISTMAS
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
#endif
                return false;
            case RGB_MODE_GRADIENT:
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
                handleKeycodeRGBMode(RGBLIGHT_MODE_STATIC_GRADIENT, RGBLIGHT_MODE_STATIC_GRADIENT_end);
#endif
                return false;
            case RGB_MODE_RGBTEST:
#ifdef RGBLIGHT_EFFECT_RGB_TEST
                rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
#endif
                return false;
        }
    }

    return true;
}
