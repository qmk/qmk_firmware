// Copyright 2026 Sylvain Huguet (@shuguet)
// SPDX-License-Identifier: GPL-2.0-or-later

// Runtime lighting. Everything static lives in keyboard.json:
//
//   * the alphas_mods effect paints green alphas and blue modifiers,
//     picking the modifier keys by LED_FLAG_MODIFIER (0x01) in each
//     LED's "flags"
//   * hue/sat/val set the green, and speed is reused by that effect as
//     the hue offset for the modifiers
//
// Only the two things below need code, because both depend on state
// that does not exist until the keyboard is running.

#include "quantum.h"

// Both indicators are on by default. A keymap turns either off by adding a
// config.h containing, for example:
//
//     #define SHU89_LAYER_INDICATOR 0
//
#ifndef SHU89_CAPS_LOCK_INDICATOR
#    define SHU89_CAPS_LOCK_INDICATOR 1
#endif
#ifndef SHU89_LAYER_INDICATOR
#    define SHU89_LAYER_INDICATOR 1
#endif

// Caps Lock indicator colour, as an HSV hue and saturation. The value
// always follows the current RGB brightness, so it dims with the rest of
// the board. Defaults to pure red; set the saturation to 0 for white.
#ifndef SHU89_CAPS_LOCK_HUE
#    define SHU89_CAPS_LOCK_HUE 0
#endif
#ifndef SHU89_CAPS_LOCK_SAT
#    define SHU89_CAPS_LOCK_SAT 255
#endif

// Caps Lock's matrix position, needed to recolour it from host LED state.
#define CAPS_ROW 4
#define CAPS_COL 4

#if SHU89_LAYER_INDICATOR
// Mirrors the rule inside the alphas_mods effect, so keys lit by the
// layer view keep exactly the colour they have on the base layer.
static rgb_t key_color(uint8_t index) {
    hsv_t hsv = {rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val()};
    if (g_led_config.flags[index] & LED_FLAG_MODIFIER) {
        hsv.h += rgb_matrix_get_speed();
    }
    return hsv_to_rgb(hsv);
}
#endif

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false; // a keymap has taken over
    }

#if SHU89_LAYER_INDICATOR
    uint8_t layer = get_highest_layer(layer_state);

    if (layer > 0) {
        // A layer is held: show only the keys that do something on it.
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index == NO_LED || index < led_min || index >= led_max) {
                    continue; // no LED here, or it belongs to the other half
                }
                // Reads the dynamic keymap when VIA is enabled, so
                // this follows whatever the layer actually contains.
                uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){.row = row, .col = col});
                if (keycode == KC_NO || keycode == KC_TRANSPARENT) {
                    continue; // nothing bound here on this layer
                }
                rgb_t rgb = key_color(index);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }
#endif

#if SHU89_CAPS_LOCK_INDICATOR
    // Caps Lock stays lit whenever it is active, on every layer.
    if (host_keyboard_led_state().caps_lock) {
        uint8_t index = g_led_config.matrix_co[CAPS_ROW][CAPS_COL];
        if (index != NO_LED && index >= led_min && index < led_max) {
            hsv_t hsv = {SHU89_CAPS_LOCK_HUE, SHU89_CAPS_LOCK_SAT, rgb_matrix_get_val()};
            rgb_t rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
        }
    }
#endif

    return true;
}
