/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Bckspc│ │Hom│Scr│Pse│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │ │End│Scr│Pse│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │   Enter│
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │LSft│ \ │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │ RSft │RSt│     │ ↑ │
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │LCrl │GUI│ LAlt│           Space           │ RAlt│ Fn│ RCrl│ │ ← │ ↓ │ → │
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │ │   │   │   │   │ │   │   │   │   │ │   │   │   │
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │ │   │   │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │ │   │   │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │LSft│ | │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │ RSft │RSt│     │   │
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │     │   │     │                           │     │   │     │ │   │   │   │
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3      4      5       6      7      8      9        10       11       12       13       14       15       16      */
	[_BASE] = LAYOUT_all(
                KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5,  KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SLCK, KC_PAUSE,
                KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,   KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
                KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
                KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
                KC_LSFT, KC_NUBS, KC_Z,    KC_X,  KC_C,  KC_V,   KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,          KC_UP,
                KC_LCTL, KC_LGUI, KC_LALT,               KC_SPC,                               KC_RALT, MO(_FN), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RIGHT
    ),

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Rst│   │MeP│VoD│VoU│Mut│ │Stp│Prv│Ply│Nxt│ │Mai│Hom│Cal│Sch│ │Rod│Mod│Tog│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │NKO│   │   │   │   │   │   │   │   │   │   │Spd│Spi│       │ │C_E│   │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │1Hd│1Hi│1Sd│1Si│1Vd│1Vi│   │   │   │   │   │   │     │ │   │   │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │      │2Hd│2Hi│2Sd│2Si│2Vd│2Vi│   │   │   │   │   │        │
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │    │   │Pre│Ref│Flp│   │   │   │   │   │   │   │      │   │     │Vai│
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │     │   │     │                           │     │ Fn│     │ │Hud│Vad│Hui│
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15       16     */
	[_FN] = LAYOUT_all(
                QK_BOOT, KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MAIL, KC_WHOM, KC_CALC, KC_WSCH,          RGB_RMOD, RGB_MOD, RGB_TOG,
                NK_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______, RGB_C_E,  _______, _______,
                _______, G1_HUD,  G1_HUI,  G1_SAD,  G1_SAI,  G1_VAD,  G1_VAI,  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                _______, G2_HUD,  G2_HUI,  G2_SAD,  G2_SAI,  G2_VAD,  G2_VAI,  _______, _______, _______, _______, _______,          _______,
                _______, _______, G_PRE,   REF_G,   G_FLIP,  _______, _______, _______, _______, _______, _______, _______, _______, _______,           RGB_VAI,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RGB_HUD,  RGB_VAD, RGB_HUI
    ),
};
