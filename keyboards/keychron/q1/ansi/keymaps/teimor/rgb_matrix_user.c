/* Copyright 2022 @ Teimor Epstein
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

void rgb_matrix_init_user(void) {
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
    switch (current_layer) {
        case MAC_BASE:
        case WIN_BASE:
#if defined CAPS_LOCK_INDICATOR_COLOR && defined MAC_LAYER_DEFAULT_COLOR && defined WIN_LAYER_DEFAULT_COLOR
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);
            } else if (current_layer == MAC_BASE)
                rgb_matrix_set_color_all(MAC_LAYER_DEFAULT_COLOR);
            else if (current_layer == WIN_BASE)
                rgb_matrix_set_color_all(WIN_LAYER_DEFAULT_COLOR);
#endif
            break;
        case MAC_FN:
        case WIN_FN:
#if defined MAC_LAYER_DEFAULT_COLOR && defined WIN_LAYER_DEFAULT_COLOR
            if (current_layer == MAC_FN) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_not_transparent, MAC_LAYER_DEFAULT_COLOR);
            } else if (current_layer == WIN_FN) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_not_transparent, WIN_LAYER_DEFAULT_COLOR);
            }
#endif
#ifdef FN_LAYER_TRANSPARENT_KEYS_OFF
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, RGB_OFF);
#endif
            break;
    }
    return false;
}

void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
#if defined MAC_LAYER_DEFAULT_COLOR && defined WIN_LAYER_DEFAULT_COLOR
        else {
            if (layer == MAC_BASE)
                rgb_matrix_set_color(i, MAC_LAYER_DEFAULT_COLOR);
            else if (layer == WIN_BASE)
                rgb_matrix_set_color(i, WIN_LAYER_DEFAULT_COLOR);
        }
#endif
    }
}

bool is_caps_lock_indicator(uint16_t keycode) {
    bool indicator = keycode == KC_CAPS || keycode == KC_LGMAC || keycode == KC_LGWIN;
#ifdef CAPS_LOCK_INDICATOR_LIGHT_60
    return (KC_A <= keycode && keycode <= KC_CAPS) || (KC_LEFT_CTRL <= keycode && keycode <= KC_RIGHT_GUI) || keycode == KC_MACFN || keycode == KC_WINFN || indicator;
#else
    return indicator;
#endif
}

bool is_transparent(uint16_t keycode) { return keycode == KC_TRNS; }
bool is_not_transparent(uint16_t keycode) { return keycode != KC_TRNS; }
