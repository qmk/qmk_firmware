/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

 // clang-format off

enum layers {
    BASE,
    FUNC,
    L2,
    L3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE,   MO(FUNC), KC_ESC,  KC_BSPC,  KC_TAB,
        MC_0,   KC_NUM,   KC_PSLS, KC_PAST,  KC_PMNS,
        MC_2,   KC_P7,    KC_P8,   KC_P9,    KC_PPLS,
        MC_3,   KC_P4,    KC_P5,   KC_P6,
        MC_4,   KC_P1,    KC_P2,   KC_P3,    KC_PENT,
        MC_5,   KC_P0,             KC_PDOT),

    [FUNC] = LAYOUT_numpad_6x5(
        RGB_TOG,   _______,  KC_MUTE, KC_VOLD,  KC_VOLU,
        MC_1,   RGB_MOD,  RGB_VAI, RGB_HUI,  KC_DEL,
        MC_2,   RGB_RMOD, RGB_VAD, RGB_HUD,  _______,
        MC_3,   RGB_SAI,  RGB_SPI, KC_MPRV,
        MC_4,   RGB_SAD,  RGB_SPD, KC_MPLY,  _______,
        MC_5,   RGB_TOG,           KC_MNXT),

    [L2] = LAYOUT_numpad_6x5(
        _______, _______,  _______, _______,  _______,
        _______, _______,  _______, _______,  _______,
        _______, _______,  _______, _______,  _______,
        _______, _______,  _______, _______,
        _______, _______,  _______, _______,  _______,
        _______, _______,           _______),

    [L3] = LAYOUT_numpad_6x5(
        _______, _______,  _______, _______,   _______,
        _______, _______,  _______, _______,   _______,
        _______, _______,  _______, _______,   _______,
        _______, _______,  _______, _______,
        _______, _______,  _______, _______,   _______,
        _______, _______,           _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FUNC]       = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [L2] = { ENCODER_CCW_CW(_______, _______) },
    [L3] = { ENCODER_CCW_CW(_______, _______) }
};
#endif // ENCODER_MAP_ENABLE
