/* Copyright 2022 @ Adam Lickel
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

enum encoder_names {
    _LEFT,
    _RIGHT,
    _MIDDLE,
};

enum bdn9_layers {
    _MEDIA = 0,
    _XCODE,
    _CUST1,
    _CUST2,
};

#define KC_XCRUN LGUI(KC_R)
#define KC_XCPAUSE LCTL(LGUI(KC_Y))
#define KC_XCSTOP LGUI(KC_DOT)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT(
        TO(_XCODE), RGB_SPD,    RGB_SPI,
        RGB_MOD,    KC_MPLY,    KC_MSTP,
        RGB_RMOD,   KC_MNXT,    KC_MPRV
    ),
    [_XCODE] = LAYOUT(
        TG(_XCODE), KC_NO,      KC_NO,
        KC_XCRUN,   KC_XCPAUSE, KC_XCSTOP,
        KC_F6,      KC_F7,      KC_F8
    ),
    [_CUST1] = LAYOUT(
        TG(_CUST1), _______,    _______,
        _______,    _______,    _______,
        _______,    _______,    _______
    ),
    [_CUST2] = LAYOUT(
        TG(_CUST2), _______,    _______,
        _______,    _______,    _______,
        _______,    _______,    _______
    ),
};

// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    uint8_t layer = get_highest_layer(state);

    switch (layer) {
        case _MEDIA:  // Reset
            rgblight_reload_from_eeprom();
            break;

        case _XCODE:
            rgblight_sethsv_noeeprom(HSV_BLUE);
#    if defined(RGB_MATRIX_ENABLE) && defined(ENABLE_RGB_MATRIX_BREATHING)
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
#    elif defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_EFFECT_BREATHING)
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);
#    endif
            break;

        case _CUST1:
            rgblight_sethsv_noeeprom(HSV_GREEN);
#    if defined(RGB_MATRIX_ENABLE) && defined(ENABLE_RGB_MATRIX_BREATHING)
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
#    elif defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_EFFECT_BREATHING)
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);
#    endif
            break;

        case _CUST2:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
#    if defined(RGB_MATRIX_ENABLE) && defined(ENABLE_RGB_MATRIX_BREATHING)
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
#    elif defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_EFFECT_BREATHING)
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);
#    endif
            break;

        default:
            break;
    }
#endif
    return state;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    [_MEDIA] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI), ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_XCODE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
#else
    [_MEDIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_XCODE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
#endif
    [_CUST1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_CUST2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#else
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case 0:  // Reset
            if (index == _LEFT) {
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
            } else if (index == _MIDDLE) {
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
            } else if (index == _RIGHT) {
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
            }
            break;
#endif

        default:
            if (index == _LEFT) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == _MIDDLE) {
                if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
            } else if (index == _RIGHT) {
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
            }
            break;
    }
    return true;
}
#endif
