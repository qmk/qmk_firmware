/* 
 * Copyright 2019 Ethan Durrant (emdarcher)
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
#include "quantum.h"


void keyboard_pre_init_kb(void){
    //init the CAPS LOCK LED pin as an output
    setPinOutput(D1);
    //init the Backlight Pin as an output
    setPinOutput(D4);
    //call any user initialization code
    keyboard_pre_init_user();
}

void led_set_kb(uint8_t usb_led){
    //control the caps lock LED
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
        //set led pin to high
        writePinHigh(D1);
    } else {
        //set to low
        writePinLow(D1);
    }
    //call any user LED functions
    led_set_user(usb_led);
}

