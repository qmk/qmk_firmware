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
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 * The first section contains "names" for physical keys of the keyboard
 * and defines their position on the board.
 * The second section defines position of the keys on the switch matrix
 * (where COLUMNS and ROWS crosses). 
 This looks so much better in an terminal window :-(*/
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
// due to a nasty PCB layout bug the R1.03 board has "6" and "7" keyboard coulmns swapped...

#define LAYOUT_all( \
	K_MO0,  K_PSCR, K_SLCK, K_PAUS, K_ESC,  K_F1,  K_F2,  K_F3,  K_F4,  K_F5,  K_F6,  K_F7,  K_F8,   K_F9,   K_F10,  K_F11,  K_F12,           K_HOME, K_PGUP, \
	K_PMNS, K_PAST, K_PSLS, K_NLCK, K_GRV,  K_1,    K_2,   K_3,   K_4,   K_5,   K_6,   K_7,   K_8,   K_9,    K_0,    K_MINS, K_EQL, K_BSPL, K_BSPC,   K_INS,  \
	K_PPLS, K_P9,   K_P8,   K_P7,   K_TAB,  K_Q,    K_W,   K_E,   K_R,   K_T,   K_Y,   K_U,   K_I,   K_O,    K_P,    K_LBRC, K_RBRC,      K_BSLS,     K_DEL,  \
	K_PEQ,  K_P6,   K_P5,   K_P4,   K_CAPS, K_A,    K_S,   K_D,   K_F,   K_G,   K_H,   K_J,   K_K,   K_L,    K_SCLN, K_QUOT, K_ENTL,      K_ENT,      K_PGDN, \
	K_PTAB, K_P3,   K_P2,   K_P1,   K_LSFT, K_NUBS, K_Z,   K_X,   K_C,   K_V,   K_B,   K_N,   K_M,   K_COMM, K_DOT,  K_SLSH, K_RSFT,          K_UP,   K_END,  \
	K_PENT, K_PDOT, K_PMM,  K_P0,   K_LCTL, K_LGUI, K_LALT,                     K_SPC,                       K_RALT, K_APP,  K_RCTL,  K_LEFT, K_DOWN, K_RGHT  \
	) \
	{ \
	{  K_MO0, K_SLCK,  K_ESC,   K_F2,   K_F4,  K_F7,   K_F8,  K_F10,  K_F12, K_PGUP }, \
	{ K_PSCR, K_PAUS,   K_F1,   K_F3,   K_F5,  K_F6,   K_F9,  K_F11, K_HOME, K_BSPL }, \
	{ K_PMNS, K_PSLS,  K_GRV,    K_2,    K_4,   K_7,    K_8,    K_0,  K_EQL, K_INS  }, \
	{ K_PAST, K_NLCK,    K_1,    K_3,    K_5,   K_6,    K_9, K_MINS, K_BSPC, K_PTAB }, \
	{ K_PPLS,   K_P8,  K_TAB,    K_W,    K_R,   K_U,    K_I,    K_P, K_RBRC, K_DEL  }, \
	{   K_P9,   K_P7,    K_Q,    K_E,    K_T,   K_Y,    K_O, K_LBRC, K_BSLS, K_PMM  }, \
	{  K_PEQ,   K_P5, K_CAPS,    K_S,    K_F,   K_J,    K_K, K_SCLN, K_ENTL, K_PGDN }, \
	{   K_P6,   K_P4,    K_A,    K_D,    K_G,   K_H,    K_L, K_QUOT,  K_ENT, K_RGHT }, \
	{ K_PENT,   K_P2, K_LSFT,    K_Z,    K_C,   K_N,    K_M,  K_DOT, K_RSFT, K_END  }, \
	{   K_P3,   K_P1, K_NUBS,    K_X,    K_V,   K_B, K_COMM, K_SLSH,   K_UP, K_DOWN }, \
	{ K_PDOT,   K_P0, K_LCTL, K_LGUI, K_LALT, K_SPC, K_RALT,  K_APP, K_RCTL, K_LEFT } \
}
