/* Copyright 2021 Tye (@tyetye)
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

#include "santoku.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
	if (clockwise) {
		tap_code(KC_WH_U);
	} else {
		tap_code(KC_WH_D);
	}
	return true;
}

#ifdef OLED_ENABLE
__attribute__((weak)) void oled_task_user(void) {
	// Vanity Text
	static bool show_vanity_text = true;
	if (show_vanity_text) {
		oled_write_ln_P(PSTR("  Santoku Keyboard"), false);
		oled_write_ln_P(PSTR("       by Tye"), false);
		oled_write_ln_P(PSTR(""), false);
		oled_write_ln_P(PSTR("    Hello, world."), false);
		if (timer_read() > 7500) {
			show_vanity_text = false;
		}
	} else {
	#ifdef WPM_ENABLE
			uint8_t n = get_current_wpm();
			char    wpm_counter[4];
			wpm_counter[3] = '\0';
			wpm_counter[2] = '0' + n % 10;
			wpm_counter[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
			wpm_counter[0] = n / 10 ? '0' + n / 10 : ' ';
			oled_write_P(PSTR("WPM:"), false);
			oled_write(wpm_counter, false);
	#endif

	}

	// Host Keyboard Layer Status
	switch (get_highest_layer(layer_state)) {
		case 0:
			oled_write_P(PSTR("QWERTY\n"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR("TB  qwert | yuiop\\"), false);
			oled_write_ln_P(PSTR("ES  asdfg | hjkl;'"), false);
			oled_write_ln_P(PSTR("SH  zxcvb | nm,./"), false);
			break;
		case 1:
			oled_write_P(PSTR("   Symbol   \n"), true);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(" `  !@#$% | ^&*()-"), false);
			oled_write_ln_P(PSTR("ES  12345 | 67890="), false);
			oled_write_ln_P(PSTR("SH  \\_+{} | [],./"), false);
			break;
		case 2:
			oled_write_P(PSTR(" Navigation \n"), true);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR("   | HM PD PU EN NT"), false);
			oled_write_ln_P(PSTR("   | << vv ^^ >>"), false);
			oled_write_ln_P(PSTR("ov | D[ D] D+ D-"), false);
			break;
		case 3:
			oled_write_P(PSTR("  Function  \n"), true);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR("          |"), false);
			oled_write_ln_P(PSTR("ES F12345 | 67890"), false);
			oled_write_ln_P(PSTR("CP F      | ab"), false);
			break;
		default:
			oled_write_ln_P(PSTR("Undefined"), false);
	}
}
#endif
