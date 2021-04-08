/* Copyright 2020 joshajohnson
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

#define MO_NLCK LT(1, KC_NLCK) // Numlock on tap, layer change on hold

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                 KC_MUTE,  KC_MPLY,
       KC_PMNS,  KC_PAST,  KC_PSLS,    MO_NLCK,
       KC_PPLS,    KC_P7,    KC_P8,      KC_P9,
       KC_PPLS,    KC_P4,    KC_P5,      KC_P6,
       KC_PENT,    KC_P1,    KC_P2,      KC_P3,
       KC_PENT,  KC_PDOT,    KC_P0,      KC_P0
),
    [1] = LAYOUT_all(
                   RESET,  _______,
       RGB_TOG, RGB_RMOD,  RGB_MOD,    _______,
       _______,  RGB_VAD,  RGB_VAI,    _______,
       _______,  RGB_HUD,  RGB_HUI,    _______,
       _______,  RGB_SAD,  RGB_SAI,    _______,
       _______,  _______,  _______,    _______
)
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    }
}

void matrix_init_user(void){

#ifdef RGB_MATRIX_ENABLE

g_led_config = (led_config_t){ {
    // Key Matrix to LED Index
    {NO_LED,NO_LED,NO_LED,NO_LED},
    { 7,      8,      9,     10},
    { 11,    12,     13,     14},
    { 15,    16,     17,     18},
    { 19,    20,     21,     22},
    { 23,    24,     25,     26}
    //todo: assign leds to keys differently for the different layouts
}, {
    // LED Index to Physical Position
    { 190, 50}, { 111, 50}, { 35, 50}, {38, 0}, {38, 35}, {186, 35}, {186, 0}, // UNDERGLOW
    //todo: underglow location needs to be recalculated. The top row is above row 4, and for now they have the same y value 0
    {  0,  0}, {75,  0}, {150,  0}, {225,  0}, // row 4
    {  0, 16}, {75, 16}, {150, 16}, {225, 16}, // row 3
    {  0, 32}, {75, 32}, {150, 32}, {225, 32}, // row 2
    {  0, 48}, {75, 48}, {150, 48}, {225, 48}, // row 1
    {  0, 64}, {75, 64}, {150, 64}, {225, 64}  // row 0

}, {
    // LED Index to Flag
    LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,  // UNDERGLOW
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 4
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 3
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 2
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 1
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT            // row 0

} };

#endif
}
