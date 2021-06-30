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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_27_encoder(
        KC_ESC , KC_PWR , KC_SLEP, KC_F11 ,
		KC_NLCK, KC_BSPC, KC_PSLS, KC_PAST, KC_PMNS, 
		RGB_MOD, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, 
		RGB_RMOD, KC_P4  , KC_P5  , KC_P6  , 
		RGB_TOG, KC_P1  , KC_P2  , KC_P3  , KC_PENT,
		MO(1)  , KC_P0  ,          KC_PDOT,
        KC_VOLD, KC_MUTE, KC_VOLU
    ),
    [1] = LAYOUT_27_encoder(
        _______, _______, _______, _______,
		_______, _______, _______, _______, _______, 
		RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______, 
		RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, 
		_______, _______, _______, _______, RESET  ,
		_______, _______,          _______,
        KC_MPRV, KC_MPLY, KC_MNXT
    ),
    [2] = LAYOUT_27_encoder(
        _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, _______,
		_______, _______,          _______,
        _______, _______, _______
    ),
    [3] = LAYOUT_27_encoder(
        _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, _______,
		_______, _______,          _______,
        _______, _______, _______
    )
};
