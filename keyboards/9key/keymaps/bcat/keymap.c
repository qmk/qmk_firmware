/* Copyright 2021 Jonathan Rascher
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

#include "bcat.h"

#define KY_LOCK LGUI(KC_L) /* Chrome OS: Lock screen */
#define KY_MICM LSG(KC_1)  /* Meet Shortcuts: Mute mic */
#define KY_MICU LSG(KC_2)  /* Meet Shortcuts: Unmute mic */
#define KY_RHAND LSG(KC_3) /* Meet Shortcuts: Raise/lower hand */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [LAYER_DEFAULT] = LAYOUT(
        KC_MPLY,  KC_VOLU,  KY_RHAND,
        KY_LOCK,  KC_VOLD,  KY_MICU,
        LY_FN1,   KC_MUTE,  KY_MICM
    ),
    [LAYER_FUNCTION_1] = LAYOUT(
        EE_CLR,   _______,  QK_BOOT,
        _______,  _______,  _______,
        _______,  _______,  _______
    ),
    // clang-format on
};
