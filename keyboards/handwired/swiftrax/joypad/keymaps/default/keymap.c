  /* Copyright 2020 swiftrax
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

[0] = LAYOUT_ortho_6x4(
  KC_MUTE, KC_F13 , KC_F14 , KC_F15 ,
  KC_NUM , KC_PSLS, KC_PAST, KC_PMNS,
  KC_P7  , KC_P8  , KC_P9  , KC_PPLS,
  KC_P4  , KC_P5  , KC_P6  , KC_PPLS,
  KC_P1  , KC_P2  , KC_P3  , KC_PENT,
  KC_P0  , KC_P0  , KC_PDOT, KC_PENT),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
