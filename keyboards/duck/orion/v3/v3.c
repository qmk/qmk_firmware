/* Copyright 2019 MechMerlin <mechmerlin@gmail.com>
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
#include "v3.h"
#include "indicator_leds.h"

enum BACKLIGHT_AREAS {
  BACKLIGHT_ALPHAS   = 0b00000010,
  BACKLIGHT_MODNUM   = 0b00001000
};

void backlight_set(uint8_t level) {
  switch(level) {
  case 0:
    PORTB |= BACKLIGHT_ALPHAS;
    PORTB |= BACKLIGHT_MODNUM;
  break;
  case 1:
    PORTB &= ~BACKLIGHT_ALPHAS;
    PORTB |= BACKLIGHT_MODNUM;
  break;
  case 2:
    PORTB |= BACKLIGHT_ALPHAS;
    PORTB &= ~BACKLIGHT_MODNUM;
  break;
  case 3:
    PORTB &= ~BACKLIGHT_ALPHAS;
    PORTB &= ~BACKLIGHT_MODNUM;
  break;
  }
}

void led_set_kb(uint8_t usb_led) {

  IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) ? writePinLow(B0) : writePinHigh(B0);
  IS_LED_ON(usb_led, USB_LED_NUM_LOCK) ? writePinLow(B4) | writePinHigh(B4);
  IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK) ? writePinLow(D7) : writePinHigh(D7);
  led_set_user(usb_led);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
