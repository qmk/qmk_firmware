/* Copyright 2021 owlab
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
#include "jelly.h"
#include "rgblight.h"



void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
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
    led_set_user(usb_led);
}
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
        
        
   
        default:
        break;
    }
  }
  return process_record_user(keycode, record);
}
void matrix_init_kb(void) {
    matrix_init_user(); 
    
}
// set the first rgb animation to RGBLIGHT_MODE_STATIC_LIGHT
void keyboard_post_init_kb(void){
   
    if(rgblight_get_mode()==RGBLIGHT_MODE_STATIC_LIGHT){
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    }
}
void matrix_scan_kb(void) {
    matrix_scan_user();
}





