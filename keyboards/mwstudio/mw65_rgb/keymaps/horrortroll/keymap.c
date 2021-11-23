/* Copyright 2021 TW59420 <https://github.com/TW59420>
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

#include "keymap_stuff.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
                                                                VolD ◯ VolU
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
       │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Bckspc│Hom│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │End│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │  Enter │PgU│
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
       │ LShift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │ RSft │ ↑ │PgD│
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
       │LCrl│GUI │LAlt│         Space          │RAlt│ Fn │ │ ← │ ↓ │ → │
       └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
                                                                     ◯
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
       │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
       │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
       │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │   │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
       │ LShift │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │ RSht │   │   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
       │    │    │    │                        │    │    │ │   │   │   │
       └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5     6         7     8     9        10       11       12       13       14     */
	[_BASE] = LAYOUT_65_ansi_blocker(
                KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_6,     KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_VOLD, KC_HOME, KC_VOLU,
                KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y,     KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
                KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H,     KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
                KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V, KC_B,     KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
                KC_LCTL, KC_LGUI, KC_LALT,                         KC_SPACE,             MO(_FN), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RIGHT
    ),

/*
                                                                     ◯
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
       │ ` │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  Home │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │Pause│Ins│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
       │      │   │   │   │   │   │   │   │   │   │   │   │  PrtSc │Del│
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
       │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
       │    │    │    │                        │ Fn │    │ │   │   │   │
       └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13        14     */
	[_FN] = LAYOUT_65_ansi_blocker(
                KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME,    _______, _______, _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUSE, KC_INS,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PSCR,  KC_DEL,
                _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
                _______, _______, _______,                            _______,                   _______, MO(_RN),          _______, _______,  _______
    ),

/*
                                                                     ◯
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
       │Rst│   │   │   │   │   │   │   │   │   │   │   │   │       │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
       │     │1Hd│1Hi│1Sd│1Si│1Vd│1Vi│   │Hud│Hui│   │C_E│   │     │Tog│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
       │      │2Hd│2Hi│2Sd│2Si│2Vd│2Vi│   │Sad│Sai│   │   │        │   │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
       │        │Pre│Ref│Flp│   │   │   │Spd│Spi│   │   │      │Vai│   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
       │    │    │    │                        │    │ Rn │ │Rod│Vad│Mod│
       └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12        13       14     */
	[_RN] = LAYOUT_65_ansi_blocker(
                RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______, _______,
                _______, G1_HUD,  G1_HUI,  G1_SAD,  G1_SAI,  G1_VAD,  G1_VAI,  _______, RGB_HUD, RGB_HUI, _______, RGB_C_E, _______,  _______, RGB_TOG,
                _______, G2_HUD,  G2_HUI,  G2_SAD,  G2_SAI,  G2_VAD,  G2_VAI,  _______, RGB_SAD, RGB_SAI, _______, _______,           _______, _______,
                _______,          G_PRE,   REF_G,   G_FLIP,  _______, _______, _______, RGB_SPD, RGB_SPI, _______, _______, _______,  RGB_VAI, _______,
                _______, _______, _______,                            _______,                   _______, _______,          RGB_RMOD, RGB_VAD, RGB_MOD
    ),
};
