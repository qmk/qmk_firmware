/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "hal.h"

#include "led.h"




void led_set(uint8_t usb_led) {
   if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // output high
        palSetPadMode(TEENSY_PIN27_IOPORT, TEENSY_PIN27, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPad(TEENSY_PIN27_IOPORT, TEENSY_PIN27);
    } else {
        // Hi-Z
        //palSetPadMode(TEENSY_PIN27_IOPORT, TEENSY_PIN27, PAL_MODE_INPUT);
        palClearPad(TEENSY_PIN27_IOPORT, TEENSY_PIN27);        
    }

        if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output high
        palSetPadMode(TEENSY_PIN28_IOPORT, TEENSY_PIN28, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPad(TEENSY_PIN28_IOPORT, TEENSY_PIN28);
    } else {
        // Hi-Z
        //palSetPadMode(TEENSY_PIN28_IOPORT, TEENSY_PIN28, PAL_MODE_INPUT);
        palClearPad(TEENSY_PIN28_IOPORT, TEENSY_PIN28);
    }

        if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        // output high
        palSetPadMode(TEENSY_PIN31_IOPORT, TEENSY_PIN31, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPad(TEENSY_PIN31_IOPORT, TEENSY_PIN31);
    } else {
        // Hi-Z
        //palSetPadMode(TEENSY_PIN31_IOPORT, TEENSY_PIN31, PAL_MODE_INPUT);
        palClearPad(TEENSY_PIN31_IOPORT, TEENSY_PIN31);
    }

}

//void led_set_user(uint8_t usb_led) {
//    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
//        writePinLow(C9);
//    } else {
//        writePinHigh(C9);
//   }
//   if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
//        writePinLow(C8);
//    } else {
//        writePinHigh(C8);
//    }
//    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
//        writePinLow(E0);
//    } else {
//        writePinHigh(E0);
//    }
    
//}
