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
         M_VSC_FILECLOSE, MO(10),             KC_TRNS,              KC_TRNS,         KC_TRNS
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
                  QK_BOOT,  KC_TRNS,    KC_TRNS, KC_TRNS,
                  TO(7),    TO(8),      TO(9),   KC_TRNS,
                  TO(4),    TO(5),      TO(6),   KC_TRNS,
         KC_TRNS, TO(1),    TO(2),      TO(3),   KC_TRNS,
         KC_TRNS, KC_TRNS,  TO(0),      KC_TRNS, KC_TRNS
				 ),



};

/* byte map for the goblin logo, knob goblin text, and level text */
static void render_goblin_logo(void) {
    static const char PROGMEM my_logo[] = {
		0x00, 0xe0, 0x40, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x60, 0x20, 0x10, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x10, 0x20, 0x60, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x40, 0xe0, 0x00,
		0x00, 0x03, 0x06, 0x3c, 0x49, 0x91, 0x21, 0x00, 0x40, 0x80, 0x80, 0x80, 0x80, 0x00, 0x60, 0x00,
		0x00, 0x60, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x00, 0x21, 0x91, 0x49, 0x3c, 0x06, 0x03, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1f, 0x60, 0x40, 0xc0, 0x06, 0x0e, 0x0f, 0x67, 0x50, 0xc0,
		0xc0, 0x50, 0x67, 0x0f, 0x0e, 0x06, 0xc0, 0x40, 0x60, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x7b, 0xc7, 0x8e, 0x1e, 0x3e, 0x3e,
		0x3e, 0x3e, 0x1e, 0x8e, 0xc7, 0x7b, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x04,
		0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0x03, 0x03, 0x03, 0x83, 0x03, 0x83, 0x03, 0x03, 0x03, 0x83,
		0x03, 0x03, 0x83, 0x83, 0x83, 0x03, 0x03, 0x83, 0x83, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x04, 0x06, 0x09, 0x10, 0x00, 0x1f, 0x03, 0x06, 0x0c, 0x1f,
		0x00, 0x0f, 0x10, 0x10, 0x10, 0x0f, 0x00, 0x1f, 0x12, 0x12, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x78, 0xfc, 0x84, 0xa4, 0xa4, 0x68, 0x00, 0x78, 0x84, 0x84, 0x84, 0x78, 0x00, 0xfc, 0x94,
		0x94, 0x68, 0x00, 0xfc, 0x80, 0x80, 0x80, 0x00, 0xfc, 0x00, 0xfc, 0x18, 0x30, 0x60, 0xfc, 0x00,
		0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
		0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
		0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x50, 0x50, 0x50, 0x00, 0xf0, 0x00, 0x00,
		0x00, 0xf0, 0x00, 0xf0, 0x50, 0x50, 0x50, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x00, 0x03, 0x02, 0x02, 0x02, 0x00, 0x00, 0x01, 0x02,
		0x01, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x00, 0x03, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(my_logo, sizeof(my_logo));
}

bool oled_task_user(void) {

	render_goblin_logo();

    oled_set_cursor(0,11);

	switch (get_highest_layer(layer_state)) {
		case 0:
			oled_write_P(PSTR(" NUM\n"), false);
			break;
		case 1:
			oled_write_P(PSTR(" NAV\n"), false);
			break;
		case 2:
			oled_write_P(PSTR(" CODE\n"), false);
			break;
		case 3:
			oled_write_P(PSTR(" GDB\n"), false);
			break;
		case 4:
			oled_write_P(PSTR(" OBS\n"), false);
			break;
		default:
			oled_write_P(PSTR(" NONE\n"), false);
			break;
	}
    return false;
}
