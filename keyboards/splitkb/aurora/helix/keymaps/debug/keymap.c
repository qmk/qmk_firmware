/* Copyright 2023 splitkb.com <support@splitkb.com>
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

enum layers {
    _DEFAULT = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F,                    S(KC_F), S(KC_E), S(KC_D), S(KC_C), S(KC_B), S(KC_A),
        KC_G, KC_H, KC_I, KC_J, KC_K, KC_L,                    S(KC_L), S(KC_K), S(KC_J), S(KC_I), S(KC_H), S(KC_G),
        KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R,                    S(KC_R), S(KC_Q), S(KC_P), S(KC_O), S(KC_N), S(KC_M),
        KC_S, KC_T, KC_U, KC_V, KC_W, KC_X, KC_Y,     S(KC_Y), S(KC_X), S(KC_W), S(KC_V), S(KC_U), S(KC_T), S(KC_S),
        KC_Z, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,     S(KC_6), S(KC_5), S(KC_4), S(KC_3), S(KC_2), S(KC_1), S(KC_Z)
    )
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0 is left-half encoder
    // 1 is right-half encoder
    if (index == 0) {
        tap_code(KC_0);
    } else if (index == 1) {
        tap_code(KC_1);
    }

    if (clockwise) {
        tap_code16(KC_PLUS);
    } else {
        tap_code(KC_MINUS);
    }

    return false;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // A 128x32 OLED rotated 90 degrees is 5 characters wide and 16 characters tall
    // This example string should fill that neatly
    oled_write_P(PSTR("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()[]{}-=_+?"), false);
    return false;
}
#endif