/* Copyright 2015-2017 Jack Humbert
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

/*                                   _
 *  ___   _ __     ___   __      __ | | __  _   _   _ __ ___     __ _
 * / __| | '_ \   / _ \  \ \ /\ / / | |/ / | | | | | '_ ` _ \   / _` |
 * \__ \ | | | | | (_) |  \ V  V /  |   <  | |_| | | | | | | | | (_| |
 * |___/ |_| |_|  \___/    \_/\_/   |_|\_\  \__,_| |_| |_| |_|  \__,_|
 *
 * https://github.com/snowkuma
 *
 * version 0.2
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "my_strings.h"
#include "snowkuma.h"

extern keymap_config_t keymap_config;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = LAYOUT_planck_wrapper(
			_________________COLEMAK_L1________________, T_ZOOM,  VOLUP,  _________________COLEMAK_R1________________,
			_________________COLEMAK_L2________________, _______, VOLDOWN, _________________COLEMAK_R2________________,
			_________________COLEMAK_L3________________, _______, MUTE,    _________________COLEMAK_R3________________,
			_______, _______, _______, ________MOD_LEFT_________, ________MOD_RIGHT________, _______, _______, _______
	),

	[_NAV] = LAYOUT_planck_wrapper(
     _________________NAV_L1____________________, _______, _______, _________________NAV_R1____________________, 
     _________________NAV_L2____________________, _______, _______, _________________NAV_R2____________________, 
     _________________NAV_L3____________________, _______, _______, _________________NAV_R3____________________, 
     _______, _______, _______, _______, DEL_SYM, _______, _______, _______, _______, _______, _______, _______
  ),

	[_SYMBOL] = LAYOUT_planck_wrapper(
     _________________SYM_L1____________________, _______, _______, _________________SYM_R1____________________, 
     _________________SYM_L2____________________, _______, _______, _________________SYM_R2____________________, 
     _________________SYM_L3____________________, _______, _______, _________________SYM_R3____________________, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

	[_NUMBER] = LAYOUT_planck_wrapper(
     _________________NUM_L1____________________, _______, _______, _________________NUM_R1____________________, 
     _________________NUM_L2____________________, _______, _______, _________________NUM_R2____________________, 
     _________________NUM_L3____________________, _______, _______, _________________NUM_R3____________________, 
     _______, _______, _______, _______, _______, _______, _______, ________NUM_R4___________, _______, _______
  ),

	[_MOUSE] = LAYOUT_planck_wrapper(
     _________________MOU_L1____________________, _______, _______, _________________MOU_R1____________________, 
     _________________MOU_L2____________________, _______, _______, _________________MOU_R2____________________, 
     _________________MOU_L3____________________, _______, _______, _________________MOU_R3____________________, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

	[_THUMB] = LAYOUT_planck_wrapper(
     _________________THU_L1____________________, T_KRAKEN,_______, _________________THU_R1____________________, 
     _________________THU_L2____________________, _______, _______, _________________THU_R2____________________, 
     _________________THU_L3____________________, _______, _______, _________________THU_R3____________________, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

	[_ARRANGE] = LAYOUT_planck_wrapper(

     _________________ARR_L1____________________, _______, _______, _________________ARR_R1____________________, 
     _________________ARR_L2____________________, _______, _______, _________________ARR_R2____________________, 
     _________________ARR_L3____________________, _______, _______, _________________ARR_R3____________________, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

	[_FUNCTION] = LAYOUT_planck_wrapper(

     _________________FUN_L1____________________, _______, _______, _________________FUN_R1____________________, 
     _________________FUN_L2____________________, _______, _______, _________________FUN_R2____________________, 
     _________________FUN_L3____________________, _______, _______, _________________FUN_R3____________________, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

#ifdef AUDIO_ENABLE
float plover_song[][2]     = SONG(PLOVER_SOUND);
float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
	if (muse_mode) {
		if (muse_counter == 0) {
			uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
			if (muse_note != last_muse_note) {
				stop_note(compute_freq_for_midi_note(last_muse_note));
				play_note(compute_freq_for_midi_note(muse_note), 0xF);
				last_muse_note = muse_note;
			}
		}
		muse_counter = (muse_counter + 1) % muse_tempo;
	}
#endif
}

void matrix_init_user(void) {
	set_unicode_input_mode(UC_OSX);
}
