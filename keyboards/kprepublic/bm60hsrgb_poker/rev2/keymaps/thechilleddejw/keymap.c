/* Copyright 2022 TheChilledDejw
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
        [0] = LAYOUT_60_ansi(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_RGUI, KC_RCTL),
        [1] = LAYOUT_60_ansi(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_TRNS, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_COPY, KC_PSTE, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, MO(2), KC_TRNS, KC_TRNS, KC_TRNS),
        [2] = LAYOUT_60_ansi(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS),
        [3] = LAYOUT_60_ansi(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(4)),
        [4] = LAYOUT_60_ansi(RGB_TOG, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};


#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

  if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(28, 3, 227, 252);
        RGB_MATRIX_INDICATOR_SET_COLOR(41, 3, 227, 252);
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 3, 227, 252);

    }
  else {
        RGB_MATRIX_INDICATOR_SET_COLOR(28, 0, 95,128);
        RGB_MATRIX_INDICATOR_SET_COLOR(41, 0, 95,128);
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 0, 95,128);

  }

switch (get_highest_layer(layer_state)) {
        case 0:
            RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 128, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(13, 0, 128, 128);
            break;
        case 1:
            RGB_MATRIX_INDICATOR_SET_COLOR(12, 128, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(1, 128, 0, 0);
            break;
        case 2:
            RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(11, 0, 128, 0);
            break;
        case 3:
            RGB_MATRIX_INDICATOR_SET_COLOR(3, 0, 0, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(10, 0, 0, 128);
            break;
        default:
            // white
            RGB_MATRIX_INDICATOR_SET_COLOR(2, 128, 128, 128);
            break;
    }
}
#endif
