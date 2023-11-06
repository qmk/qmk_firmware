/* Copyright 2020 KiwiKey
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x3(
        KC_MUTE,    KC_VOLD,    KC_VOLU,    // Media volume: Mute - Up - Down
        KC_MPLY,    KC_MPRV,    KC_MNXT,    // Media track control: Play/Pause - Previous Track - Next Track
        MO(_FN),    LCTL(KC_C), LCTL(KC_V)  // FN - Copy - Paste
    ),
	[_FN] = LAYOUT_ortho_3x3(
        RGB_TOG,    RGB_MODE_REVERSE,    RGB_MODE_FORWARD,
        _______,    RGB_MODE_BREATHE,    RGB_MODE_RAINBOW,
        _______,    _______,             QK_BOOT
    )
};
