/* Copyright 2018 Jumail Mundekkat / MxBlue
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
#include "mxss_frontled.h"

hs_set caps_color = { .hue = 0, .sat = 255 };

// Colors for layers
// Format: {hue, saturation}
// {0, 0} to turn off the LED
// Add additional rows to handle more layers
hs_set layer_colors[4] = {
    [0] = {.hue = 0,     .sat = 0},  // Color for Layer 0
    [1] = {.hue = 86,    .sat = 255},  // Color for Layer 1
    [2] = {.hue = 36,    .sat = 255},  // Color for Layer 2
    [3] = {.hue = 185,   .sat = 255},  // Color for Layer 3
};
size_t lc_size = ARRAY_SIZE(layer_colors);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT( /* Base */
	QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT,           KC_SPACE,           KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
),

    LAYOUT( /* L1 */
	KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PSCR, FLED_VAD, FLED_VAI, FLED_MOD, RGB_VAI,
    QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, RGB_MOD, RGB_SAI, RGB_TOG,
    KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,           KC_TRNS, KC_TRNS, RGB_HUD, RGB_SAD, RGB_HUI
),
};
