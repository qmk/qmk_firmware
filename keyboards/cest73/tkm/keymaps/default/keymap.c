 /* Copyright 2021 cest73
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
		_BASE,
		_FN
};

/*
 * ┌───┬───┬───┬───┐ ┌───┐ ┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐ ┌───┬───┐
 * │Fn │PSc│Scr│Pse│ │Esc│ │F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│ │Hme│PgU│
 * └───┴───┴───┴───┘ └───┘ └───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘ └───┴───┘
 *
 * ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┐
 * │ - │ * │ / │Num│ │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsl│Bsp│ │Ins│
 * ├───┼───┼───┼───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┤
 * │ + │ 9 │ 8 │ 7 │ │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│
 * ├───┼───┼───┼───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────│ ├───┤
 * │ = │ 6 │ 5 │ 4 │ │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │Etl│ Ent│ │PgD│
 * ├───┼───┼───┼───┤ ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┘ ├───┤
 * │Tab│ 3 │ 2 │ 1 │ │Shft│Shl│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│┌───┐│End│
 * ├───┼───┼───┼───┤ ├────┼───┼───┴┬──┴───┴───┴───┴───┴───┴─┬─┴─┬─┴─┬─┴──┬───┘│ ↑ │└───┘
 * │Ent│ . │ , │ 0 │ │Ctrl│GUI│Alt │                        │Alt│Mnu│Ctrl│┌───┼───┼───┐
 * └───┴───┴───┴───┘ └────┴───┴────┴────────────────────────┴───┴───┴────┘│ ← │ ↓ │ → │
 *                                                                        └───┴───┴───┘
 */
 /*
 * ┌───┬───┬───┬───┐ ┌───┐ ┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐ ┌───┬───┐
 * │_V_│   │   │   │ │Rst│ │   │ V+│ Vx│ V-││stp│rew│ply│fwd││   │   │   │   │ │   │   │
 * └───┴───┴───┴───┘ └───┘ └───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘ └───┴───┘
 *
 * ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┐
 * │   │Ma0│Ma1│Ma2│ │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │ │ejc│
 * ├───┼───┼───┼───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┤
 * │   │MB1│^W │NB2│ │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │
 * ├───┼───┼───┼───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────│ ├───┤
 * │   │<W │MB3│>W │ │      │   │   │   │   │   │ ← │ ↑ │ ↓ │ → │   │   │   │ Ent│ │   │
 * ├───┼───┼───┼───┤ ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┘ ├───┤
 * │   │MB4│vW │MB5│ │Shft│   │   │   │   │   │   │   │   │   │   │   │ Shift│┌───┐│   │
 * ├───┼───┼───┼───┤ ├────┼───┼───┴┬──┴───┴───┴───┴───┴───┴─┬─┴─┬─┴─┬─┴──┬───┘│M↑ │└───┘
 * │   │   │   │   │ │Ctrl│GUI│Alt │                        │Alt│Mnu│Ctrl│┌───┼───┼───┐
 * └───┴───┴───┴───┘ └────┴───┴────┴────────────────────────┴───┴───┴────┘│M← │M↓ │M→ │
 *                                                                        └───┴───┴───┘
 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_all(
	MO(_FN), KC_PSCR, KC_SLCK, KC_PAUS, KC_ESC,      KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,       KC_HOME, KC_PGUP,
	KC_PMNS, KC_PAST, KC_PSLS, KC_NLCK, KC_GRV,  KC_1,    KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,     KC_INS,
	KC_PPLS, KC_P9,   KC_P8,   KC_P7,   KC_TAB,      KC_Q,    KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC,   KC_BSLS,    KC_DEL,
	KC_PEQL, KC_P6,   KC_P5,   KC_P4,   KC_CAPS,       KC_A,    KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT, KC_NUHS,  KC_ENT,      KC_PGDN,
	KC_TAB,  KC_P3,   KC_P2,   KC_P1, OSM(MOD_LSFT), KC_NUBS,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT), KC_UP,  KC_END,
	KC_PENT, KC_PDOT, KC_PCMM, KC_P0,   KC_LCTL, KC_LGUI, KC_LALT,                      KC_SPC,                  KC_RALT, KC_APP, KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT
	),
	[_FN] = LAYOUT_all(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  RESET,        KC_F13, KC_VOLU, KC_MUTE, KC_VOLD, KC_MSTP, KC_MRWD, KC_MPLY, KC_MFFD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,
	KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_EJCT,
	KC_TRNS, KC_BTN1, KC_WH_U, KC_BTN2,  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS,
	KC_TRNS, KC_WH_L, KC_BTN3, KC_WH_R,  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
	KC_TRNS, KC_BTN4, KC_WH_D, KC_BTN5,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_MS_U,    KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,                 KC_MS_L, KC_MS_D, KC_MS_R
	)
};
