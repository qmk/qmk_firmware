/*
Copyright 2020 <me@homedrop.org>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT_60_ansi(
        KC_GESC, KC_2, KC_4, KC_6, KC_8, KC_0, KC_EQL, KC_BSPC,
        KC_1, KC_3, KC_5, KC_7, KC_9, KC_MINS, KC_DEL,

        KC_TAB, KC_Q, KC_E, KC_T, KC_U, KC_O, KC_LBRC, KC_RBRC, 
        KC_W, KC_R, KC_Y, KC_I, KC_P, KC_BSLS, 
        
        KC_CAPS, KC_A, KC_D, KC_G, KC_J, KC_L, KC_QUOT, KC_NUHS,  
        KC_S, KC_F, KC_H, KC_K, KC_SCLN, KC_ENT,

        KC_LSFT, KC_Z, KC_C, KC_B, KC_M, KC_DOT, KC_RSFT, 
        KC_NUBS, KC_X, KC_V, KC_N, KC_COMM, KC_SLSH, KC_RSFT, MO(1),

        KC_LCTL, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_RCTL, KC_LEFT, 
        KC_LGUI, MO(1), KC_RGHT
    ),

    [_LAYER1] = LAYOUT_60_ansi(
        KC_GESC, KC_F2, KC_F4, KC_F6, KC_F8, KC_F10, KC_F12, KC_TRNS,
        KC_F1, KC_F3, KC_F5, KC_F7, KC_F9, KC_F11, KC_TRNS,

        KC_TRNS, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_SLCK, KC_PAUSE, 
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_PSCR, RESET,

        KC_TRNS, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  
        RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, BL_TOGG, BL_DEC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, BL_INC, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AUDIO_VOL_DOWN, 
        KC_TRNS, KC_TRNS, KC_AUDIO_VOL_UP
    ),

    [_LAYER2] = LAYOUT_60_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_LAYER3] = LAYOUT_60_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS
    ),

};