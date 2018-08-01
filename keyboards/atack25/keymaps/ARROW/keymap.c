/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#include "atack25.h"

#define NUML 0
#define FN1 1

#define BOOTMAGIC_KEY_SALT KC_NLCK
#define BOOTMAGIC_KEY_BOOTLOADER KC_P0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[NUML]	KEYMAP(
		KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_EQUAL, 
		KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PGUP, 
		KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PGDN, 
		KC_P1, KC_P2, KC_P3, KC_UP, F(0), 
		KC_P0, KC_PDOT, KC_LEFT, KC_DOWN, KC_RGHT),
	
	
	
[FN1] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_E, KC_F, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_B, KC_C, KC_D, KC_HOME, KC_TRNS,
		KC_A, KC_TRNS, KC_TRNS, KC_END,  KC_TRNS)

};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP(FN1, KC_ENT)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
   
    return MACRO_NONE;
};


void matrix_init_user(void) {
	led_init_ports();
}

void led_init_ports(void){
	DDRD |= (1 << 7);
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		PORTD |= (1 << 7);
	} else {
		PORTD &= ~(1 << 7);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}