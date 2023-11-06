/* Copyright 2020 Guillaume Gérard
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
#include "underglow.h"

void keyboard_post_init_rgb(void) {
    user_config_t user_config;
    user_config.raw = eeconfig_read_user();
    if (!user_config.rgb_layer_change) {
        return;
    }
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_ORANGE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_LAYER:
            if (record->event.pressed) {
                user_config_t user_config;
                user_config.raw = eeconfig_read_user();
                user_config.rgb_layer_change ^= 1;
                eeconfig_update_user(user_config.raw);
                if (user_config.rgb_layer_change) {
                    layer_state_set(layer_state);
                }
            }
            return false;
        case RGB_MODE_FORWARD ... RGB_MODE_RGBTEST:
            if (record->event.pressed) {
                user_config_t user_config;
                user_config.raw = eeconfig_read_user();
                if (user_config.rgb_layer_change) {
                    user_config.rgb_layer_change = false;
                    eeconfig_update_user(user_config.raw);
                }
            }
            return true;
    }
    return true;
}

layer_state_t layer_state_set_rgb(layer_state_t state) {
    user_config_t user_config;
    user_config.raw = eeconfig_read_user();
    if (!user_config.rgb_layer_change) {
        return state;
    }
    switch (get_highest_layer(state)) {
        case _QWERTY:
#ifdef LAYERS_PROGRAMMER
        case _PROGRAMMER_SHIFTED:
#endif
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
#ifdef LAYERS_ORTHO
        case _LOWER:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case _RAISE:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
#endif
#ifdef LAYER_FN
        case _FN:
            rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
            break;
#endif
#ifdef LAYER_GIT
        case _GIT:
            rgblight_sethsv_noeeprom(HSV_TEAL);
            break;
#endif
        default:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            break;
    }
    return state;
}

bool led_update_rgb(led_t led_state) {
    user_config_t user_config;
    user_config.raw = eeconfig_read_user();
    if (!user_config.rgb_layer_change) {
        return true;
    }
    if (led_state.caps_lock) {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
    } else {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    }
    return true;
}
