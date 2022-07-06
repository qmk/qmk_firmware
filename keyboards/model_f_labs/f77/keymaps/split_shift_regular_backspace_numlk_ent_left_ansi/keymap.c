/* Copyright 2022 Matthew J Wolf
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
 *
 * -----
 * Based on zF77_-_HHKB_Split_Shift,_everything_else_ANSI_-_0-9.json from Joe of Model F Labs 
 */
/* all
 * - Base
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  ┌───┬───┬───┐
 * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ + │   │Bsp│  │Nlk│ - │ + │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤  ├───┼───┼───┤
 * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \   │  │Kp7│Kp8│Kp9│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────│  ├───┼───┼───┤
 * │Caps  │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │Ent │  │Kp4│Kp5│Kp6│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤  ├───┼───┼───┤
 * │Lsft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Rsft │Fn1│  │Kp1│Kp2│Kp3│
 * ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴─┬─┴──┬┴───┴┬───┬─┴───┤  ├───┼───┼───┤
 * │Lctl │GUI│Lalt │        Space         │    │Ratl │Nlk│Rctl │  │Kp0│Dot│Ent│
 * └─────┴───┴─────┴──────────────────────┴────┴─────┴───┴─────┘  └───┴───┴───┘
 * - FN1
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  ┌───┬───┬───┐
 * │ ` │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │Ins│  │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤  ├───┼───┼───┤
 * │     │   │   │   │   │   │   │   │Psc│Skl│Pau│Up │   │Del  │  │Hom│Up │PGu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────│  ├───┼───┼───┤
 * │      │Vo-│Vo+│Mut│Ejc│   │Kp*│Kp/│Hom│PGu│Lef│Rgh│   │    │  │Lef│   │Rgh│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤  ├───┼───┼───┤
 * │    │   │   │   │   │   │   │Kp+│Kp-│End│PGd│Dow│      │   │  │End│Dow│PGd│
 * ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴─┬─┴──┬┴───┴┬───┬─┴───┤  ├───┼───┼───┤
 * │     │   │     │         Fn2          │    │     │   │     │  │Ins│Del│   │
 * └─────┴───┴─────┴──────────────────────┴────┴─────┴───┴─────┘  └───┴───┴───┘
 * - FN2
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  ┌───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │Dl-│Dl+│   │   │  │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤  ├───┼───┼───┤
 * │     │   │   │Epr│Res│HPt│   │   │   │   │   │   │   │     │  │   │   │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────│  ├───┼───┼───┤
 * │      │   │   │Deb│   │   │   │   │   │   │   │   │   │    │  │   │   │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤  ├───┼───┼───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │  │   │   │   │
 * ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴─┬─┴──┬┴───┴┬───┬─┴───┤  ├───┼───┼───┤
 * │     │   │     │                      │    │     │   │     │  │   │   │   │
 * └─────┴───┴─────┴──────────────────────┴────┴─────┴───┴─────┘  └───┴───┴───┘
 */
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN1,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
       KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,  _______, KC_BSPC,    KC_NUM, KC_PMNS, KC_PPLS, 
       KC_TAB,       KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_P7,  KC_P8,   KC_P9, 
       KC_CAPS,      KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,     KC_P4,  KC_P5,   KC_P6, 
       KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(_FN1),   KC_P1,  KC_P2,   KC_P3, 
       KC_LCTL, KC_LGUI, KC_LALT,               KC_SPC,            _______,   KC_RALT,         KC_NLCK, KC_RCTL,  KC_P0,  KC_PDOT, KC_PENT
    ),
    [_FN1] = LAYOUT_all(
       KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_INS,                   _______, _______, _______,
       _______,         _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,  _______,  KC_DEL,  KC_HOME, KC_UP,   KC_PGUP,
       _______,       KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, _______,   KC_LEFT, _______, KC_RGHT,
       _______, _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______,          KC_END,  KC_DOWN, KC_PGDN,
       _______, _______, _______,                     MO(_FN2),                           _______, _______, _______, _______,                KC_INS,  KC_DEL,  _______ 
    ),
    [_FN2] = LAYOUT_all(
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, HPT_DWLD, HPT_DWLI, _______, _______,  _______, _______, _______, 
       _______,   _______, _______, EEP_RST, RESET,   HPT_TOG, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, 
       _______,     _______, _______, DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, 
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______, _______, 
       _______, _______, _______,                       _______,                           _______, _______, _______, _______,                   _______, _______, _______
    )
};
