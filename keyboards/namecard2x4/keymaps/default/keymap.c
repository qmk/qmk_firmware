/* Copyright 2018 takashiski
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

enum Layer
{
	DF,
	LW,
	RS
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DF] = LAYOUT(
		KC_1,KC_2,KC_3,LT(LW,KC_4),
		KC_5,KC_6,KC_7,LT(RS,KC_8)
		),
[LW]= LAYOUT(
	
		RGB_VAD,RGB_VAI,RGB_HUI,RGB_HUD,
		KC_TRNS,RGB_MOD,RGB_RMOD,KC_TRNS
		),
[RS]= LAYOUT(
	
		KC_MYCM,KC_MAIL,KC_VOLU,KC_MUTE,
		KC_WSCH,KC_CALC,KC_VOLD,KC_TRNS
		)

};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
