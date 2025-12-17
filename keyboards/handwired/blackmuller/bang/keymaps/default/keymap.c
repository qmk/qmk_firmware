/* Copyright 2025 BlackMullerLLC
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
    /*
     *        ┌───┬───┐ ┌───┬───┬───┬───┐      ┌───┬───┬───┬───┐
     *        │F7 │F8 │ │F9 │F10│F11│F12│      │Irt│PSc│Scr│Pse│
     *        └───┴───┘ └───┴───┴───┴───┘      └───┴───┴───┴───┘
     *     ┌───┬───┬───┬───┬───┬───┬────────┐  ┌───┬───┬───┬───┐
     *     │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp │  │Num│ / │ * │ - │
     *   ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤  ├───┼───┼───┼───┤
     *   │ Y │ U │ I │ O │ P │ [ │ ] │  \   │  │ 7 │ 8 │ 9 │   │
     *   └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──────┤  ├───┼───┼───┤ + │
     *     │ H │ J │ K │ L │ ; │ ' │  Enter │  │ 4 │ 5 │ 6 │   │
     *     └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤  ├───┼───┼───┼───┤
     *       │ N │ M │ , │ . │ / │    Shift │  │ 1 │ 2 │ 3 │   │
     *       └─┬─┴───┴──┬┴───┼───┴┬────┬────┤  ├───┴───┼───┤Ent│
     *         │        │ Alt│ GUI│Menu│Ctrl│  │   0   │ . │   │
     *         └────────┴────┴────┴────┴────┘  └───────┴───┴───┘
     */
    [0] = LAYOUT(
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_INS, KC_PSCR, KC_SCRL, KC_PAUS,

        KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_P4,   KC_P5,   KC_P6,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_P1,   KC_P2,   KC_P3,            KC_PENT,
        KC_SPC,           KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,                   KC_P0,            KC_PDOT
    )
};
