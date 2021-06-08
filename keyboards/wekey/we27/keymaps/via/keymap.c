/* Copyright 2021 @wekey
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
#define _______ KC_TRNS

#ifdef ENCODER_ENABLE
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_27_encoder(
        KC_ESC , KC_PWR , KC_SLEP, KC_F11 , KC_VOLU, KC_MUTE, KC_VOLD,
		KC_NLCK, KC_BSPC, KC_PSLS, KC_PAST, KC_PMNS, 
		RGB_MOD, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, 
		RGB_RMOD, KC_P4  , KC_P5  , KC_P6  , 
		RGB_TOG, KC_P1  , KC_P2  , KC_P3  , KC_PENT,
		MO(1)  , KC_P0  ,          KC_PDOT
    ),
    [1] = LAYOUT_27_encoder(
        _______, _______, _______, _______, _______, KC_MPLY, _______,
		_______, _______, _______, _______, _______, 
		RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______, 
		RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, 
		_______, _______, _______, _______, RESET  ,
		_______, _______,          _______
    ),
    [2] = LAYOUT_27_encoder(
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, _______,
		_______, _______,          _______
    ),
    [3] = LAYOUT_27_encoder(
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, _______,
		_______, _______,          _______
    )
};

const uint8_t encoder_km_clockwise[NUMBER_OF_ENCODERS][2] = ENCODER_KEYMAP_CLOCKWISE;
const uint8_t encoder_km_couterclockwise[NUMBER_OF_ENCODERS][2] = ENCODER_KEYMAP_COUTERCLOCKWISE;

bool encoder_update_user(uint8_t index, bool clockwise) {
    extern layer_state_t layer_state;
    if (index == 0) { /* First encoder */
        keypos_t key = {
            .row = encoder_km_clockwise[index][0],
            .col = encoder_km_clockwise[index][1]
        };
        if (clockwise) {
            key.row = encoder_km_clockwise[index][0];
            key.col = encoder_km_clockwise[index][1];
        } else {
            key.row = encoder_km_couterclockwise[index][0];
            key.col = encoder_km_couterclockwise[index][1];
        }
        uint16_t keycode = keymap_key_to_keycode(get_highest_layer(layer_state), key);
        if (keycode != 0) {
            tap_code(keycode);
        }
    }
    return true;
}

#else

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_ESC , KC_PWR , KC_SLEP, KC_F11 , KC_MUTE, 
		KC_NLCK, KC_BSPC, KC_PSLS, KC_PAST, KC_PMNS, 
		RGB_MOD, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, 
		RGB_RMOD, KC_P4  , KC_P5  , KC_P6  , 
		RGB_TOG, KC_P1  , KC_P2  , KC_P3  , KC_PENT,
		MO(1)  , KC_P0  ,          KC_PDOT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, KC_MPLY, 
		_______, _______, _______, _______, _______, 
		RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______, 
		RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, 
		_______, _______, _______, _______, RESET  ,
		_______, _______,          _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, _______,
		_______, _______,          _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, _______,
		_______, _______,          _______
    )
};

#endif

