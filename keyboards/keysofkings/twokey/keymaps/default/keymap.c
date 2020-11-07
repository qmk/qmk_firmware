 /* Copyright 2020 Keys of Kings
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(
		LT(1, KC_MUTE), 
		LT(4, KC_MPLY), LT(7, KC_MNXT)),		

	LAYOUT(
		KC_TRNS, 
		TO(2), TO(3)),

	LAYOUT(
		TO(0), 
		RGB_TOG, RGB_MOD),

	LAYOUT(
		TO(0), 
		RGB_VAI, RGB_VAD),
    
    LAYOUT(
		TO(0), 
		RGB_HUI, RGB_HUD),

	LAYOUT(
		TO(5), 
		KC_TRNS, TO(6)),

	LAYOUT(
		TO(0), 
		RGB_SAI, RGB_SAD),

	LAYOUT(
		TO(8), 
		TO(9), KC_TRNS),

	LAYOUT(
		TO(0), 
		CK_TOGG, MU_TOG),

	LAYOUT(
		TO(0), 
		RESET, EEPROM_RESET),
};

void matrix_init_user(void) {
  debug_config.matrix = 1;
  debug_config.keyboard = 1;
  debug_config.enable = 1;
}

void encoder_update_user(int8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_VOLD);
    } else {
      tap_code(KC_VOLU);
    }
    #    ifdef AUDIO_CLICKY
            clockwise ? clicky_freq_up() : clicky_freq_down();
#    endif
  }
}

