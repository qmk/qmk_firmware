/* Copyright 2021 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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

[0] = LAYOUT_RH_ANY(

KC_ESC,KC_F1 ,KC_F2 ,KC_F3 ,KC_F4 ,KC_F5 ,KC_F6 ,              KC_F7 ,KC_F8 ,KC_F9 ,KC_F10,KC_F11,KC_F12, K0700, K0701, K0000, K0001, K0800, K0801, K0900, K0901,    
       K0004, K0102, K0103, K0202, K0203, K0302,               K0402, K0403, K0502, K0503, K0602, K0603, K0702, K0703, K0002,        K0802, K0803, K0902, K0903,    
       K0006, K0104, K0105, K0204, K0205, K0304,               K0404, K0405, K0504, K0505, K0604, K0605, K0704, K0705,               K0804, K0805, K0904, K0905,    
       K0107, K0106, K0207, K0206, K0307, K0306,               K0406, K0407, K0506, K0507, K0606, K0607, K0706, K0707,               K0806, K0807, K0906, K0907,    
K0008, K0009, K0108, K0109, K0208, K0209, K0308, K0309, K0410, K0408, K0409, K0508, K0509, K0608, K0609, K0708, K0709,               K0808, K0809, K0908, K0909,    
       K0010, K0110,        K0210, K0310, K0311,               K0411,        K0510,        K0511, K0610, K0611, K0710, K0711,        K0810, K0811, K0910, K0911),   
    
    

};


void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRB |= (1 << 0); PORTB &= ~(1 << 0);
	} else {
		DDRB &= ~(1 << 0); PORTB &= ~(1 << 0);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRF |= (1 << 4); PORTF &= ~(1 << 4);
	} else {
		DDRF &= ~(1 << 4); PORTF &= ~(1 << 4);
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