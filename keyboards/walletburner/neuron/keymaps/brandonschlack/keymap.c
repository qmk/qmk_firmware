/* Copyright 2020 Brandon Schlack
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
#include "brandonschlack.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base Layer
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │Bsp│
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │HyTb│ A │ S │ D │ F │ G │ H │ J │ K │ L │ Enter│
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │Shift │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│?/Lw│
 * ├┬┬┬┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┴┬┬┬┬┤
 * │││││Opt │Cmd │         SpcRse         │Ctrl│││││
 * └┴┴┴┴────┴────┴────────────────────────┴────┴┴┴┴┘
 */
[_BASE] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    HY_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLH_LWR,
             KC_LOPT, KC_LCMD,          XXXXXXX, SPC_RAI, XXXXXXX,                   XXXXXXX, KC_LCTL
),
/* Lower
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │Del│BrD│BrU│Msn│LHP│   │   │   │Hom│ ↑ │PgU│SlD│
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │    │Mut│VlU│NxW│PvT│Bck│Fwd│NxT│ ← │ → │  Ply │
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │SfCaps│Prv│VlD│Nxt│1PX│1Ps│   │End│ ↓ │PgD│    │
 * ├┬┬┬┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┴┬┬┬┬┤
 * │││││    │    │                        │    │││││
 * └┴┴┴┴────┴────┴────────────────────────┴────┴┴┴┴┘
 */
[_LOWER] = LAYOUT(
    KC_DEL,  KC_BRMD, KC_BRMU, MC_MSSN, MC_LHPD, _______, _______, _______, KC_HOME, KC_UP,   KC_PGUP, MC_SLPD,
    _______, KC_MUTE, KC_VOLU, NXT_WIN, PRV_TAB, MC_BACK, MC_FWRD, NXT_TAB, KC_LEFT, KC_RGHT,          KC_MPLY,
    SF_CAPS,          KC_MPRV, KC_VOLD, KC_MNXT, PX_AFLL, OP_AFLL, _______, KC_END,  KC_DOWN, KC_PGDN, _______,
             _______, _______,          XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______
),
/* Raise
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│   │
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │    │ F1│ F2│ F3│ F4│ F5│ F6│_ -│+ =│: ;│   " '│
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │      │ F7│ F8│ F9│F10│F11│F12│   │{ [│} ]│|\Lw│
 * ├┬┬┬┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┴┬┬┬┬┤
 * │││││    │    │                        │    │││││
 * └┴┴┴┴────┴────┴────────────────────────┴────┴┴┴┴┘
 */
/*
[_RAISE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_SCLN,          KC_QUOT,
    _______,          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_LBRC, KC_RBRC, BSL_LWR,
             _______, _______,          XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______
), */
/* Raise
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │~ `│ F1│ F2│ F3│ F4│{ [│} ]│& 7│* 8│( 9│) 0│   │
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │    │ F5│ F6│ F7│ F8│_ -│ + │$ 4│% 5│^ 6│   " '│
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │      │ F9│F10│F11│F12│+ =│! 1│@ 2│# 3│: ;│|\Lw│
 * ├┬┬┬┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┴┬┬┬┬┤
 * │││││    │    │                        │    │││││
 * └┴┴┴┴────┴────┴────────────────────────┴────┴┴┴┴┘
 */
[_RAISE] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LBRC, KC_RBRC, KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_MINS, KC_PLUS, KC_4,    KC_5,    KC_6,             KC_QUOT,
    _______,          KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_SCLN, BSL_LWR,
             _______, _______,          XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______
),
/* Adjust/Macro
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │Mke│   │   │EEP│RST│   │   │   │   │   │   │   │
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │    │   │   │   │   │   │   │   │   │   │      │
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │      │   │   │   │   │   │   │   │   │   │    │
 * ├┬┬┬┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┴┬┬┬┬┤
 * │││││    │    │                        │    │││││
 * └┴┴┴┴────┴────┴────────────────────────┴────┴┴┴┴┘
 */

[_ADJUST] = LAYOUT(
    QM_MAKE, _______, _______, EE_CLR,  QK_BOOT, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______,          XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______
)
/* Blank Layer
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │    │   │   │   │   │   │   │   │   │   │      │
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │      │   │   │   │   │   │   │   │   │   │    │
 * ├┬┬┬┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┴┬┬┬┬┤
 * │││││    │    │                        │    │││││
 * └┴┴┴┴────┴────┴────────────────────────┴────┴┴┴┴┘
 */
/*
[BLANK] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______,          XXXXXXX, _______, XXXXXXX,                   XXXXXXX, _______
)
*/

};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

