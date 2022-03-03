/* Copyright 2022 Christoph Jabs (BifbofII)
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

#include "bifbofii.h"

void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    rgblight_mode_noeeprom(mode);
}

void keyboard_post_init_rgb_light(void) {
    layer_state_set_rgb_light(layer_state);
}

layer_state_t layer_state_set_rgb_light(layer_state_t state) {
    switch (get_highest_layer(state | default_layer_state)) {
        case _FUNC:
            rgblight_set_hsv_and_mode(FUNC_HSV, RGBLIGHT_MODE_BREATHING + 3);
            break;
#ifdef RAISE_LOWER
        case _RAISE:
            rgblight_set_hsv_and_mode(RAISE_HSV, RGBLIGHT_MODE_BREATHING + 3);
            break;
        case _LOWER:
            rgblight_set_hsv_and_mode(LOWER_HSV, RGBLIGHT_MODE_BREATHING + 3);
            break;
#else
        case _FUNC2:
            rgblight_set_hsv_and_mode(FUNC2_HSV, RGBLIGHT_MODE_BREATHING + 3);
            break;
#endif
        case _ADJUST:
            rgblight_set_hsv_and_mode(ADJUST_HSV, RGBLIGHT_MODE_KNIGHT + 2);
            break;
        case _UNICODE:
            rgblight_set_hsv_and_mode(UNICODE_HSV, RGBLIGHT_MODE_BREATHING + 3);
            break;
#ifdef GAMING_ENABLE
        case _GAMING:
            rgblight_set_hsv_and_mode(GAMING_HSV, RGBLIGHT_MODE_STATIC_LIGHT);
            break;
#endif
        case _QWERTY:
            rgblight_set_hsv_and_mode(QWERTY_HSV, RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _COLEMAK:
            rgblight_set_hsv_and_mode(COLEMAK_HSV, RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _DVORAK:
            rgblight_set_hsv_and_mode(DVORAK_HSV, RGBLIGHT_MODE_STATIC_LIGHT);
            break;
    }
    return state;
}

bool led_update_rgb_light(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_set_hsv_and_mode(CAPS_HSV, RGBLIGHT_MODE_BREATHING + 3);
    }
    return true;
}
