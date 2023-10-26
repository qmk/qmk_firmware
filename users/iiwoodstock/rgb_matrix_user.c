/*
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

#include QMK_KEYBOARD_H
#include "rgb_matrix_user.h"
#include "keymap_user.h"

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

void keyboard_post_init_user(void) {
    // Set up led_index_key_position
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);
    bool    caps          = host_keyboard_led_state().caps_lock;
    bool    shift         = get_mods() & MOD_MASK_SHIFT;

    // instead of making some checks and then draw every led, lets make it the other way around
    // iterate over the LEDs, and draw each one however you like
    for (uint8_t i = led_min; i < led_max; ++i) {
        uint16_t keycode = keymap_key_to_keycode(current_layer, led_index_key_position[i]);

        // -- Locate some keycodes
#ifdef NKRO_INDICATOR_COLOR
            if (keymap_config.nkro && keycode == NK_TOGG) {
                rgb_matrix_set_color(i, NKRO_INDICATOR_COLOR);
                continue; // iterate the loop into to next LED
            }
#endif
#ifdef GUILOCK_INDICATOR_COLOR
            if (keymap_config.no_gui && keycode == GU_TOGG) {
                rgb_matrix_set_color(i, GUILOCK_INDICATOR_COLOR);
                continue;
            }
#endif
#ifdef CURRENT_LAYER_INDICATOR_COLOR
            uint8_t default_layer = get_highest_layer(default_layer_state);
            if (keycode == DF(default_layer)) {
                rgb_matrix_set_color(i, CURRENT_LAYER_INDICATOR_COLOR);
                continue;
            }
#endif


        // -- "Complex" logic
        switch (current_layer) {
            case MAC_BASE:
            case WIN_BASE:
                // -- Background
#ifdef MAC_LAYER_DEFAULT_COLOR
                // im guessing `MAC_LAYER_DEFAULT_COLOR` is a "background" color for the layer
                // you were making it after some other stuff, which would override your previous drawing, lets do it the first thing instead
                // also, calling `set_color_all` ruins the purpose of the `advanced` function, which is to draw the LEDs in smaller batches
                if (current_layer == MAC_BASE) {
                    rgb_matrix_set_color(i, MAC_LAYER_DEFAULT_COLOR);
                }
#endif
                // TODO: add equivalent code for default windows color, if you like
#ifdef WIN_LAYER_DEFAULT_COLOR
                if (current_layer == WIN_BASE) {
                    rgb_matrix_set_color(i, WIN_LAYER_DEFAULT_COLOR);
                }
#endif
                // -- Indicators
#ifdef CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
                if (shift ^ caps) { // this is: either, but not both
                    if (KC_A <= keycode && keycode <= KC_Z) {
                        // renamed, as these are not caps-LOCK and perhaps you want different colors for alphas and the lock
                        rgb_matrix_set_color(i, CAPS_LOCK_INDICATOR_COLOR);
                    }
                }
#endif

#ifdef CAPS_LOCK_INDICATOR_COLOR
                if (caps) {
                    if (keycode == KC_CAPS || keycode == KC_LSFT || keycode == KC_RSFT) {
                        rgb_matrix_set_color(i, CAPS_LOCK_INDICATOR_COLOR);
                    }
                }
#endif

#ifdef SHIFT_INDICATOR_COLOR
                if (shift && is_shift_indicator(keycode)) {
                    rgb_matrix_set_color(i, SHIFT_INDICATOR_COLOR);
                }
#endif
                break;

            case MAC_FN:
            case WIN_FN:
                // -- Background
#ifdef MAC_LAYER_DEFAULT_COLOR
                if (current_layer == MAC_FN && keycode == KC_TRNS) {
                    rgb_matrix_set_color(i, MAC_LAYER_DEFAULT_COLOR);
                }
#endif
                // TODO: add equivalent code for default windows color, if you like
#ifdef WIN_LAYER_DEFAULT_COLOR
                if (current_layer == WIN_FN && keycode == KC_TRNS) {
                    rgb_matrix_set_color(i, WIN_LAYER_DEFAULT_COLOR);
                }
#endif
#ifdef FN_LAYER_KEYS_COLOR
                if (keycode != KC_TRNS) {
                    rgb_matrix_set_color(i, FN_LAYER_KEYS_COLOR);
                }
#endif
            break;
        }
    }

    return false;
}

// check if keycode is affected by shift on the number row
bool is_shift_indicator(uint16_t keycode) {
    return (KC_1 <= keycode && keycode <= KC_0) || keycode == KC_MINS || keycode == KC_EQL || keycode == KC_GRV || keycode == KC_BSLS || keycode == KC_LBRC || keycode == KC_RBRC || keycode == KC_SCLN || keycode == KC_QUOT || keycode == KC_COMM || keycode == KC_DOT || keycode == KC_SLSH || keycode == QK_GESC || keycode == KC_LSFT || keycode == KC_RSFT;
}