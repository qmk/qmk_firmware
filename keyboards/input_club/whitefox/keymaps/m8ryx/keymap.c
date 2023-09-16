/*
Copyright 2023 Rick Rezinas (rick@rezinas.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ ` │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ ' │ = │INS│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │ Tab │ Q │ W │ f │ p │ b │ [ │ j │ l │ u │ y │ ; │ / │ Bspc│Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────┼───┤
     * │ Esc  │ A │ R │ S │ T │ G │ ] │ M │ N │ E │ I │ O │ Enter  │PgU│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Shft│ X │ C │ D │ V │ Z │ \ │ K │ H │ , │ . │ / │ Shift│ ↑ │PgD│
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │ Fn │Alt │Gui │                        │Gui│ Alt   │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_65_ansi_blocker_split_bs(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_QUOT, KC_EQL,  KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_SLSH, KC_BSPC, KC_DEL,
        KC_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_RBRC,    KC_M,    KC_N,    KC_E,    KC_I, KC_O, KC_ENT,  KC_PGUP,
        KC_LSFT, KC_X, KC_C,    KC_D,    KC_V,    KC_Z,    KC_BSLS, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_RSFT, KC_UP,   KC_PGDN,
        MO(1), KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* 
     * ┌───┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐───┬───┌───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │   │Mut│
     * ├───└───┴───┴───┴───┴───┴───┴───┴───┴───┴─┬─┴─┬─┴─┬─┴─┐─┴───└───┘
     * │     │   │   │   │   │   │   │   │   │   │Psc│Slk│Pse│     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──└───┴───┴───┘┬────┌───┐
     * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │Vl+│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┌───┼───┤
     * │    │   │   │   │   │   │   │   │   │   │   │   │      │PgU│Vl-│
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┌───┼───┼───┤
     * │    │    │    │                        │   │   │   │Hom│PgD│End│
     * └────┴────┴────┴────────────────────────┴───┴───┴───└───┴───┴───┘
     */
    [1] = LAYOUT_65_ansi_blocker_split_bs(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_VOLD,
        _______, _______, _______,                            _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
    )
};
