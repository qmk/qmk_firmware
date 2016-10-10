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
// The LCD backlight functionality conflicts with this simple
// red backlight
#if !defined(LCD_BACKLIGHT_ENABLE) && defined(STATUS_LED_ENABLE)
    // PTC1: LCD Backlight Red(0:on/1:off)
    GPIOC->PDDR |= (1<<1);
    PORTC->PCR[1] |= PORTx_PCRn_DSE | PORTx_PCRn_MUX(1);
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        GPIOC->PCOR |= (1<<1);
    } else {
        GPIOC->PSOR |= (1<<1);
    }
#elif !defined(LCD_BACKLIGHT_ENABLE)
    (void)usb_led;
    GPIOC->PDDR |= (1<<1);
    PORTC->PCR[1] |= PORTx_PCRn_DSE | PORTx_PCRn_MUX(1);
    GPIOC->PSOR |= (1<<1);
    GPIOC->PDDR |= (1<<2);
    PORTC->PCR[2] |= PORTx_PCRn_DSE | PORTx_PCRn_MUX(1);
    GPIOC->PSOR |= (1<<2);
    GPIOC->PDDR |= (1<<3);
    PORTC->PCR[3] |= PORTx_PCRn_DSE | PORTx_PCRn_MUX(1);
    GPIOC->PSOR |= (1<<3);
#else
    (void)usb_led;
#endif
}
