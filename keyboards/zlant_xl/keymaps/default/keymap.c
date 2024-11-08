/* Copyright 2021 Christian C. Berclaz
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

#include "kb.h"

#define BASE 0
#define FN   1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(KC_ESC, KC_2, KC_4, KC_6, KC_8, KC_0,
		KC_1, KC_3, KC_5, KC_7, KC_9, KC_DEL,
		KC_TAB, KC_W, KC_R, KC_Y, KC_I, KC_P,
		KC_Q, KC_E, KC_T, KC_U, KC_O, KC_BSPC,
		KC_CAPS, KC_S, KC_F, KC_H, KC_K, KC_SCLN,
		KC_A, KC_D, KC_G, KC_J, KC_L, KC_QUOT,
		KC_LSFT, KC_X, KC_V, KC_N, KC_COMM, KC_SLSH,
		KC_Z, KC_C, KC_B, KC_M, KC_DOT, KC_ENT,
		KC_NO, KC_LALT, MO(2), KC_SPC, KC_LEFT, KC_UP,
		KC_LCTL, KC_LGUI, KC_SPC, MO(1), KC_DOWN, KC_RGHT),

	[FN] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_F2, KC_F4, KC_F6, KC_PLUS, KC_RCBR,
		KC_F1, KC_F3, KC_F5, KC_UNDS, KC_LCBR, KC_PIPE,
		KC_TRNS, KC_F8, KC_F10, KC_F12, KC_TRNS, KC_END,
		KC_F7, KC_F9, KC_F11, KC_TRNS, KC_HOME, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLU,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_MPLY),
};

/*const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {*/
	/*keyevent_t event = record->event;*/

	/*switch (id) {*/

	/*}*/
	/*return MACRO_NONE;*/
/*}*/

/*void matrix_init_user(void) {*/
/*}*/

/*void matrix_scan_user(void) {*/
/*}*/

/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {*/
	/*return true;*/
/*}*/

/*void led_set_user(uint8_t usb_led) {*/

	/*if (usb_led & (1 << USB_LED_NUM_LOCK)) {*/

	/*} else {*/

	/*}*/

	/*if (usb_led & (1 << USB_LED_CAPS_LOCK)) {*/

	/*} else {*/

	/*}*/

	/*if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {*/

	/*} else {*/

	/*}*/

	/*if (usb_led & (1 << USB_LED_COMPOSE)) {*/

	/*} else {*/

	/*}*/

	/*if (usb_led & (1 << USB_LED_KANA)) {*/

	/*} else {*/

	/*}*/

/*}*/
