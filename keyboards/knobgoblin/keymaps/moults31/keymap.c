/* Copyright 2020 MrT1ddl3s
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

#include "moults31.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho(
                  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
         KC_MPLY, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
         KC_MUTE, MO(10),  KC_P0,   KC_PDOT, KC_PENT
				 ),

	[1] = LAYOUT_ortho(
                  KC_ESC,  KC_TRNS, KC_TRNS,  KC_TRNS,
                  KC_HOME, KC_TRNS, KC_PGUP,  KC_TRNS,
                  KC_END , KC_UP,   KC_PGDN,  KC_TRNS,
         KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_SPC,
         KC_TRNS, MO(10), KC_BSPC, KC_DEL,   KC_TRNS
				 ),

	[2] = LAYOUT_ortho(
                          KC_2,               KC_TRNS,              KC_TRNS,         KC_TRNS,
                          M_VSC_MVEDTRPRVGRP, M_VSC_MVEDTRNXTGRP,   KC_TRNS,         KC_TRNS,
                          M_VSC_EDGRPPRV,     M_VSC_EDGRPNXT,       KC_TRNS,         KC_TRNS,
         KC_TRNS,         M_VSC_SIDEBARFOCUS, M_VSC_SIDEBARCLOSE,   M_VSC_TERMFOCUS, KC_TRNS,
         M_VSC_CLOSEFILE, MO(10),             KC_TRNS,              KC_TRNS,         KC_TRNS
				 ),

	[3] = LAYOUT_ortho(
                             KC_3,             KC_TRNS,      KC_TRNS,       KC_TRNS,
                             KC_TRNS,          KC_TRNS,      KC_TRNS,       M_GDB_PAUSE,
                             M_GDB_RESTART,    M_GDB_STOP,   KC_TRNS,       M_GDB_PAUSE,
         M_VSC_DBGCNSLFOCUS, M_GDB_STEPOVER,   M_GDB_STEPIN, M_GDB_STEPOUT, M_GDB_PLAY,
         KC_TRNS,            MO(10),           KC_TRNS,      KC_TRNS,       M_GDB_PLAY
				 ),

	[4] = LAYOUT_ortho(
                  KC_4,               KC_TRNS,           KC_TRNS,             KC_TRNS,
                  M_OBS_VOICE_UNMUTE, M_OBS_MOOSIC_MUTE, M_OBS_MOOSIC_UNMUTE, KC_TRNS,
                  M_OBS_DSKT_MUTE,    M_OBS_DSKT_UNMUTE, M_OBS_VOICE_MUTE,    KC_TRNS,
         KC_TRNS, M_OBS_BRB,          M_OBS_GAME,        M_OBS_JSTCHT,        KC_TRNS,
         KC_TRNS, MO(10),             KC_TRNS,           KC_TRNS,             KC_TRNS
				 ),

	[5] = LAYOUT_ortho(
                  KC_5, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, MO(10), KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	[6] = LAYOUT_ortho(
                  KC_6, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, MO(10), KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	[7] = LAYOUT_ortho(
                  KC_7, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, MO(10), KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	[8] = LAYOUT_ortho(
                  KC_8, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, MO(10), KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	[9] = LAYOUT_ortho(
                  KC_9, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, MO(10), KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	[10] = LAYOUT_ortho(
                  RESET,  KC_TRNS,    KC_TRNS, KC_TRNS,
                  TO(7),    TO(8),      TO(9),   KC_TRNS,
                  TO(4),    TO(5),      TO(6),   KC_TRNS,
         KC_TRNS, TO(1),    TO(2),      TO(3),   KC_TRNS,
         KC_TRNS, KC_TRNS,  TO(0),      KC_TRNS, KC_TRNS
				 ),



};
