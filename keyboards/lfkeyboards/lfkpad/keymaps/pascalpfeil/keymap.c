/* Copyright 2021 Pascal Pfeil
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_6x4(
        KC_ESC,  KC_TAB,  KC_BSPC, MO(1),
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
            KC_P0,        KC_PDOT, KC_PENT
    ),

    /* RGB */
    [1] = LAYOUT_numpad_6x4(
        RGB_SAI, RGB_VAI, RGB_HUI, _______,
        RGB_SAD, RGB_VAD, RGB_HUD, QK_BOOT,
        RGB_M_X, RGB_M_G, RGB_MOD,
        RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_RMOD,
        RGB_M_P, RGB_M_B, RGB_M_R,
            XXXXXXX,      XXXXXXX, RGB_TOG
    ),

    /* VIA wants four keymaps */
    [2] = LAYOUT_numpad_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
            _______,      _______, _______
    ),

    /* VIA wants four keymaps */
    [3] = LAYOUT_numpad_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
            _______,      _______, _______
    ),
};

const uint8_t number_leds[] = {8, 9, 10, 11, 12, 13, 15, 16, 17};
const uint8_t number_leds_size = sizeof(number_leds) / sizeof(uint8_t);

bool led_update_user(led_t led_state) {
    for (uint8_t i = 0; i < number_leds_size; i++)
        if (led_state.num_lock)
            // set to whatever the other leds are doing
            // this is needed so that upon disabling num lock, the leds don't stay red 
            rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), numer_leds[i]); 
        else
            rgblight_setrgb_red_at(numer_leds[i]); // set to red

    return true;
}
