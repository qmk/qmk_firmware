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

#ifdef SHIFT_INDICATOR_COLOR
#    define is_shift_pressed (get_mods() & MOD_MASK_SHIFT)
#else
#    define is_shift_pressed false
#endif

void rgb_matrix_init_user(void) {
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
    uint8_t current_layer = get_highest_layer(layer_state);
    bool    caps          = host_keyboard_led_state().caps_lock;
    switch (current_layer) {
        case WIN_BASE:
        case MAC_BASE:
            // Light up letters if caps and light up letters and numbers if shift. If shift and caps light up just numbers.
#ifdef CAPS_LOCK_INDICATOR_COLOR
            if (caps && !is_shift_pressed) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);
#    ifdef CAPS_LOCK_INDICATOR_OTHER
                rgb_matrix_set_color_by_not_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_OTHER);
#    endif
            }
#    ifdef SHIFT_INDICATOR_COLOR
            else if (is_shift_pressed && !caps) {
                // Light up letters and other shift affected keys
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_shift_indicator, SHIFT_INDICATOR_COLOR);
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);
            } else if (is_shift_pressed && caps) {
                // Only shift affected keys light up
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_shift_indicator, SHIFT_INDICATOR_COLOR);
            }
#    endif // SHIFT_INDICATOR_COLOR
#endif     // CAPS_LOCK_INDICATOR_COLOR
            break;
        default:
#ifdef FN_LAYER_TRANSPARENT_KEYS_COLOR
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, FN_LAYER_TRANSPARENT_KEYS_COLOR);
#endif
#ifdef FN_LAYER_KEYS_COLOR
            rgb_matrix_set_color_by_not_keycode(led_min, led_max, current_layer, is_transparent, FN_LAYER_KEYS_COLOR);
#endif
#ifdef CURRENT_LAYER_INDICATOR_COLOR
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_default_layer, CURRENT_LAYER_INDICATOR_COLOR);
#endif
#ifdef NKRO_INDICATOR_COLOR
            if (keymap_config.nkro) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_nkro_indicator, NKRO_INDICATOR_COLOR);
            }
#endif
            break;
    }
    return false;
}

// set color of keys that match the keycode
void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

// set color of all leds that are not a certain keycode
void rgb_matrix_set_color_by_not_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if (!(*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

// check if keycode is a letter or shift or caps lock
bool is_caps_lock_indicator(uint16_t keycode) {
#ifdef CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
    return (KC_A <= keycode && keycode <= KC_Z) || keycode == KC_CAPS || keycode == KC_LSFT || keycode == KC_RSFT;
#else
    return keycode == KC_CAPS;
#endif
}

// check if keycode is the DF to default layer
#ifdef CURRENT_LAYER_INDICATOR_COLOR
bool is_default_layer(uint16_t keycode) {
    return keycode == DF(get_highest_layer(default_layer_state));
}
#endif

// check if keycode is the NKRO toggle
#ifdef NKRO_INDICATOR_COLOR
bool is_nkro_indicator(uint16_t keycode) {
    return keycode == NK_TOGG;
}
#endif

// check if keycode is transparent
bool is_transparent(uint16_t keycode) {
    return keycode == KC_TRNS;
}

// check if keycode is affected by shift on the number row
#ifdef SHIFT_INDICATOR_COLOR
bool is_shift_indicator(uint16_t keycode) {
    return (KC_1 <= keycode && keycode <= KC_0) || keycode == KC_MINS || keycode == KC_EQL || keycode == KC_GRV || keycode == KC_BSLS || keycode == KC_LBRC || keycode == KC_RBRC || keycode == KC_SCLN || keycode == KC_QUOT || keycode == KC_COMM || keycode == KC_DOT || keycode == KC_SLSH || keycode == QK_GESC || keycode == KC_LSFT || keycode == KC_RSFT;
}
#endif
