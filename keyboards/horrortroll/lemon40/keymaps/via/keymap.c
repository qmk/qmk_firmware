/* Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
    _FN1
};

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌─────┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬────┐
       │ Tab │ q │ w │ e │ r │ t │      │ y │ u │ i │ o │ p │ ` │Bksp│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐     └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
       │ Caps │ a │ s │ d │ f │ g │      │ h │ j │ k │ l │ \ │ Enter │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬┬┴──┬┴──┬────┤
       │ LShift │ z │ x │ c │ v │ b │  │ n │ m │ , │ . ││ / │ ↑ │RSft│
       └┬────┬──┴─┬─┼───┴┬──┴───┴───┤  ├───┴───┴┬──┴─┬─┘├───┼───┼───┬┘
        │LCrl│GUI │ │LAlt│  Space   │  │  Space │ Fn │  │ ← │ ↓ │ → │
        └────┴────┘ └────┴──────────┘  └────────┴────┘  └───┴───┴───┘
       ┌─────┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬────┐
       │     │ Q │ W │ E │ R │ T │      │ Y │ U │ I │ O │ P │ ~ │    │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐     └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
       │ Caps │ A │ S │ D │ F │ G │      │ H │ J │ K │ L │ | │       │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬┬┴──┬┴──┬────┤
       │ LShift │ Z │ X │ C │ V │ B │  │ N │ M │ < │ > ││ ? │   │RSft│
       └┬────┬──┴─┬─┼───┴┬──┴───┴───┤  ├───┴───┴┬──┴─┬─┘├───┼───┼───┬┘
        │    │    │ │    │          │  │        │    │  │   │   │   │
        └────┴────┘ └────┴──────────┘  └────────┴────┘  └───┴───┴───┘
*/
    /*  Row:    0        1        2        3     4       5             6     7       8        9        10       11       12     */
    [_BASE] = LAYOUT(
                KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R,   KC_T,         KC_Y, KC_U,   KC_I,    KC_O,    KC_P,    KC_GRV,  KC_BSPC,
                KC_CAPS, KC_A,    KC_S,    KC_D, KC_F,   KC_G,         KC_H, KC_J,   KC_K,    KC_L,    KC_BSLS,          KC_ENT,
                KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V,   KC_B,         KC_N, KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,
                KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC,                     KC_SPC,          MO(_FN), KC_LEFT, KC_DOWN, KC_RIGHT
            ),

/*
       ┌─────┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬────┐
       │ Esc │ 1 │ 2 │ 3 │ 4 │ 5 │      │ 6 │ 7 │ 8 │ 9 │ 0 │   │ Del│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐     └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
       │Reset │   │   │End│   │   │      │Hom│   │Ins│   │PSc│  Fn1  │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬┬┴──┬┴──┬────┤
       │        │   │   │Cal│   │   │  │   │Mut│VoD│VoU││   │PgU│    │
       └┬────┬──┴─┬─┼───┴┬──┴───┴───┤  ├───┴───┴┬──┴─┬─┘├───┼───┼───┬┘
        │    │    │ │    │          │  │        │    │  │   │PgD│   │
        └────┴────┘ └────┴──────────┘  └────────┴────┘  └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5                 6        7        8        9        10       11       12      */
    [_FN]   = LAYOUT(
                KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_DEL,
                QK_BOOT, _______, _______, KC_END,  _______, _______,          KC_HOME, _______, KC_INS,  _______, KC_PSCR,          MO(_FN1),
                _______, _______, _______, KC_CALC, _______, _______,          _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_PGUP, _______,
                _______, _______, _______,          _______,                            _______,          _______, _______, KC_PGDN, _______
            ),

/*
       ┌─────┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬────┐
       │     │   │   │   │   │   │      │   │   │   │   │Mod│Rod│ Tog│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐     └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
       │      │   │   │   │   │   │      │   │   │   │   │   │       │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬┬┴──┬┴──┬────┤
       │        │   │   │   │   │   │  │   │   │   │   ││Sad│Vai│ Sai│
       └┬────┬──┴─┬─┼───┴┬──┴───┴───┤  ├───┴───┴┬──┴─┬─┘├───┼───┼───┬┘
        │    │    │ │    │          │  │        │    │  │Hud│Vad│Hui│
        └────┴────┘ └────┴──────────┘  └────────┴────┘  └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5                 6        7        8        9        10       11        12     */
    [_FN1]  = LAYOUT(
                _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, RGB_MOD, RGB_RMOD, RGB_TOG,
                _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,           _______,
                _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, RGB_SAD, RGB_VAI,  RGB_SAI,
                _______, _______, _______,          _______,                            _______,          _______, RGB_HUD, RGB_VAD,  RGB_HUI
            ),
};
