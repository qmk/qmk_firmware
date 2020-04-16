/* Copyright 2019 COSEYFANNITUTTI
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
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Bspc│
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │HyEsc │ A │ S │ D │ F │ G │ H │ J │ K │ L │   Enter│
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│ ↑Shft│
* ├────┬───┼───┼───┴───┴───┴───┴───┴───┴┬──┴─┬─┴─┬────┤
* │Ctrl│Opt│Cmd│          Space         │←Cmd│↓Fn│→Opt│
* └────┴───┴───┴────────────────────────┴────┴───┴────┘
*/
[_BASE] = LAYOUT_ansi_40( \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    HY_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,  \
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  UP_RSFT, \
    KC_LCTL, KC_LOPT, KC_LCMD,                            SPC_RAI,                   LFT_CMD, DWN_LWR, RGT_OPT  \
),
/* Lower
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │Del  │ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│     │
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │Caps  │ ← │ ↓ │ ↑ │ → │Mut│{ [│} ]│F11│F12│    Play│
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │        │Prv│Nxt│VlD│VlU│~ `│| \│: ;│" '│? /│      │
* ├────┬───┼───┼───┴───┴───┴───┴───┴───┴┬──┴─┬─┴─┬────┤
* │    │   │   │                        │    │   │    │
* └────┴───┴───┴────────────────────────┴────┴───┴────┘
*/
[_LOWER] = LAYOUT_ansi_40( \
    KC_DELT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MUTE, KC_LBRC, KC_RBRC, KC_F11,  KC_F12,           KC_MPLY, \
    _______,          KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_GRV,  KC_BSLS, KC_SCLN, KC_QUOT, KC_EQL,  _______, \
    _______, _______, _______,                            _______,                   _______, _______, _______  \
),
/* Raise
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │Del  │! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│     │
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │Caps  │ ← │ ↓ │ ↑ │ → │Mut│{ [│} ]│_ -│+ =│    Play│
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │        │Prv│Nxt│VlD│VlU│~ `│| \│: ;│" '│? /│      │
* ├────┬───┼───┼───┴───┴───┴───┴───┴───┴┬──┴─┬─┴─┬────┤
* │    │   │   │                        │    │   │    │
* └────┴───┴───┴────────────────────────┴────┴───┴────┘
*/
[_RAISE] = LAYOUT_ansi_40( \
    KC_DELT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MUTE, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,           KC_MPLY, \
    _______,          KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_GRV,  KC_BSLS, KC_SCLN, KC_QUOT, KC_SLSH, PGU_SFT, \
    _______, _______, _______,                            _______,                   HOM_CMD, PGD_LWR, END_OPT  \
),
/* Adjust/Macro Layer
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │Make │BrD│BrU│Msn│LHP│   │   │   │   │   │   │ SlpD│
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │NxW   │PvT│NxT│Bck│Fwd│   │   │   │   │   │   Reset│
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │        │   │   │   │1PX│1Ps│   │   │   │   │      │
* ├────┬───┼───┼───┴───┴───┴───┴───┴───┴┬──┴─┬─┴─┬────┤
* │    │   │   │                        │    │   │    │
* └────┴───┴───┴────────────────────────┴────┴───┴────┘
*/
[_ADJUST] = LAYOUT_ansi_40( \
    QM_MAKE, KC_BRMD, KC_BRMU, MC_MSSN, MC_LHPD, _______, _______, _______, _______, _______, _______, MC_SLPD, \
    NXT_WIN, PRV_TAB, NXT_TAB, MC_BACK, MC_FWRD, _______, _______, _______, _______, _______,          RESET,   \
    _______,          _______, _______, _______, PX_AFLL, OP_AFLL, _______, _______, _______, _______, _______, \
    _______, _______, _______,                            _______,                   _______, _______, _______  \
)
/* Blank Layer
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │     │   │   │   │   │   │   │   │   │   │   │     │
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │      │   │   │   │   │   │   │   │   │   │        │
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │        │   │   │   │   │   │   │   │   │   │      │
* ├────┬───┼───┼───┴───┴───┴───┴───┴───┴┬──┴─┬─┴─┬────┤
* │    │   │   │                        │    │   │    │
* └────┴───┴───┴────────────────────────┴────┴───┴────┘
*/
/*
[BLANK] = LAYOUT_ansi_40( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                            _______,                   _______, _______, _______  \
)
*/
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}
