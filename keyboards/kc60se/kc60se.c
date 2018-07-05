/* Copyright 2017 Blake C. Lewis
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
#include "kc60se.h"

extern inline void kc60se_caps_led_on(void);
extern inline void kc60se_caps_led_off(void);

void led_set_kb(uint8_t usb_led) {
    (usb_led & (1<<USB_LED_CAPS_LOCK))? kc60se_caps_led_on(): kc60se_caps_led_off();
	led_set_user(usb_led);
}