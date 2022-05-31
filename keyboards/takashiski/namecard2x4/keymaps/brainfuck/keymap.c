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
#include "keymap_japanese.h"

enum Layer
{
	JP,
	EN,
	CONFIG
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[JP] = LAYOUT(
		JP_LABK,JP_RABK,JP_PLUS,JP_MINS,\
		LT(CONFIG,JP_DOT),JP_COMM,JP_LBRC,LT(CONFIG,JP_RBRC)\
		),
[EN] = LAYOUT(
		KC_LT,KC_GT,KC_PLUS,KC_MINS,\
		LT(CONFIG,KC_DOT),KC_COMM,KC_LBRC,LT(CONFIG,KC_RBRC)\
		),
[CONFIG]= LAYOUT(
		KC_NO,DF(JP),DF(JP),KC_NO,\
		KC_TRNS,DF(EN),DF(JP),KC_TRNS\
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
