/*
Copyright 2026 Jubakuba (Jubakuba@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

typedef enum {
    COLOR_NONE,
    COLOR_BACKSPACE,
    COLOR_ALPHA,
    COLOR_NUM,
    COLOR_SYMBOL,
    COLOR_SPACE,
    COLOR_QUANTUM,
    COLOR_OTHER,
} key_type_t;

key_type_t led_history[4] = {COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE};

key_type_t get_key_category(uint16_t keycode) {
    bool shifted = (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));

    switch (keycode) {
        case QK_BASIC ... QK_BASIC_MAX:
            switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
                case KC_BSPC:
                    return COLOR_BACKSPACE;
                case KC_A ... KC_Z:
                    return COLOR_ALPHA;
                case KC_SPACE:
                    return COLOR_SPACE;
                case KC_1 ... KC_0:
                    if (shifted) {
                        return COLOR_SYMBOL;
                    }
                    return COLOR_NUM;
                case KC_MINUS ... KC_SLASH:
                    return COLOR_SYMBOL;
                case KC_NO:
                case KC_TRNS:
                    return COLOR_NONE;
                default:
                    return COLOR_OTHER;
            }
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return COLOR_QUANTUM;

        default:
            return COLOR_OTHER;
    }
}

void update_custom_leds(void) {
    bool caps_on = host_keyboard_led_state().caps_lock;

    for (uint8_t i = 0; i < 4; i++) {
        if (i == 0 && caps_on) {
            rgblight_sethsv_at(HSV_RED, i);
            continue;
        }

        switch (led_history[i]) {
            case COLOR_BACKSPACE:
                rgblight_sethsv_at(HSV_RED, i);
                break;
            case COLOR_ALPHA:
                rgblight_sethsv_at(HSV_BLUE, i);
                break;
            case COLOR_NUM:
                rgblight_sethsv_at(HSV_WHITE, i);
                break;
            case COLOR_SYMBOL:
                rgblight_sethsv_at(HSV_YELLOW, i);
                break;
            case COLOR_OTHER:
                rgblight_sethsv_at(HSV_ORANGE, i);
                break;
            case COLOR_SPACE:
                rgblight_sethsv_at(HSV_GREEN, i);
                break;
            case COLOR_QUANTUM:
                rgblight_sethsv_at(HSV_PURPLE, i);
                break;
            default:
                rgblight_sethsv_at(HSV_BLUE, i);
                break;
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        key_type_t new_color = get_key_category(keycode);

        if (new_color != COLOR_NONE) {
            led_history[0] = led_history[1];
            led_history[1] = led_history[2];
            led_history[2] = led_history[3];

            led_history[3] = new_color;

            update_custom_leds();
        }
    }
    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    update_custom_leds();
    return led_update_user(led_state);
}
