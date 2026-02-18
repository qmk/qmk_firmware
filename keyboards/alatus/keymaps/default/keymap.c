/* Copyright 2026 Dominic Yeap-Holliday <DoomishGuy>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /*
     * QWERTY Layer
     *
     * .-----------------------------------.    .--------------------------------.
     * |  Q  |   W  |   E  |   R   |   T   |    |  Y  |   U  |   I  |   O  |  P  |
     * |-----+------+------+-------+-------|    |-----+------+------+------+-----|
     * |  A  |   S  |   D  |   F   |   G   |    |  H  |   J  |   K  |   L  | ; : |
     * |-----+------+------+-------+-------|    |-----+------+------+------+-----|
     * |  Z  |   X  |   C  |   V   |   B   |    |  N  |   M  |  , < |  . > | / ? |
     * '-----+------+------+-------+-------|    |-----+------+------+------+-----'
     *       | LCTL | LGUI | Space | Enter |    | Tab | BSPC | RSFT | RALT |
     *       '-----------------------------'    '--------------------------'
     */

    [_QWERTY] = LAYOUT(
        KC_Q, KC_W,    KC_E,    KC_R,     KC_T,        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,
        KC_A, KC_S,    KC_D,    KC_F,     KC_G,        KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z, KC_X,    KC_C,    KC_V,     KC_B,        KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLASH,
              KC_LCTL, KC_LGUI, KC_SPACE, KC_ENTER,    KC_TAB, KC_BSPC, KC_RSFT, KC_RALT
        )
};

// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_L, KC_R), ENCODER_CCW_CW(KC_U, KC_D)},
};
#endif
