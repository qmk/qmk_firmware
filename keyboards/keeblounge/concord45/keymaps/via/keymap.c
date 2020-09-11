/* Copyright 2020 Digid3ar
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

    /* Default QWERTY layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │Del│BkS│   │PgU│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │Tab │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ' │Enter │   │PgD│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │LShift│ Z │ X │ C │ V │ B │ N │ M │ , │ . │Sft/│ ┌───┐ │TO3│
     * ├────┬─┴─┬─┴──┬┴───┴───┴───┴───┴───┴───│───┴┬───┘ │ ↑ │ └───┘
     * │LCtl│OS │LAlt│             Space      │ Ln │ ┌───┤───├───┐
     * └────┴───┴────┴────────────────────────┴────┘ │ ← │ ↓ │ → │
     *                                               └───┴───┴───┘
     */
    [0] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_BSPC, KC_PGUP, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOTE, KC_ENTER, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), KC_UP, MO(2), KC_LCTL, KC_LGUI, KC_LALT, KC_SPACE, MO(1), KC_LEFT, KC_DOWN, KC_RIGHT),
    /* Main Numbers, Symbols & Function Layer (MOMENTARY)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │   │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ [ │ ] │ \ │   │   │Hme│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │      │   │End│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │ ( │ ) │ ; │ . │   │ - │ + │ * │ / │ =  │ ┌───┐ │   │
     * ├────┬─┴─┬─┴──┬┴───┴───┴───┴───┴───┴───│───┴┬───┘ │   │ └───┘
     * │    │   │    │                        │    │ ┌───┤───├───┐
     * └────┴───┴────┴────────────────────────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    [1] = LAYOUT(XXXXXX, KC_EXLM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_BSLS, XXXXXX, KC_HOME, XXXXXX, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_ENTER, KC_END, XXXXXX, KC_LPRN, KC_RPRN, KC_SCLN, KC_DOT, XXXXXX, KC_MINS, KC_PLUS, KC_ASTR, KC_SLSH, KC_EQL, XXXXXX, KC_NO, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX),

    /* ALTERNATE Function layer (MOMENTARY)
     * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ PWR│F1 │F2 │F3 │F4 │F5 │F6 │   │   │   │   │PRV│NXT│   │VL+│
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┼───┼───┤
     * │ SLP │F7 │F8 │F9 │F10│F11│F12│   │   │   │   │ PLAY │   │VL-│
     * ├─────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┴───│───│
     * │ WAKE  │   │   │   │   │   │   │   │   │   │    │ ┌───┐ │   │
     * ├────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───│───┴┬───┘ │   │ └───┘
     * │RSET│    │    │                        │    │ ┌───│───│───┐
     * └────┴────┴────┴────────────────────────┴────┘ │   │   │   │
     *                                                └───┴───┴───┘
     */
    [2] = LAYOUT(KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_MPRV, KC_MNXT, KC_VOLU, KC_SLEP, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_MPLY, KC_VOLD, KC_WAKE, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, RESET, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX),
    [3] = LAYOUT(XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX),
};
void matrix_scan_user(void){
    // Empty
};
