/* Copyright 2018 MechMerlin
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
#include "al1.h"

void led_set_kb(uint8_t usb_led) {
    CONFIG_LED_IO;
    print_dec(usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTD &= ~(1<<0);
    else
        PORTD |=  (1<<0);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTD &= ~(1<<1);
    else
        PORTD |=  (1<<1);
	led_set_user(usb_led);
}
