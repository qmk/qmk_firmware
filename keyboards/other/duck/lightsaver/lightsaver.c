/* Copyright 2017 Rasmus Schults <rasmusx@gmail.com>
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
#include "lightsaver.h"
#include "indicator_leds.h"

enum BACKLIGHT_AREAS {
  BACKLIGHT_ALPHAS = 0b00000010, // Alpha keys
  BACKLIGHT_FKEYS =  0b00000100, // Function row keys
  BACKLIGHT_MODNUM = 0b00001000, // Modifiers and number row
  BACKLIGHT_NUMPAD = 0b01000000  // Numpad area
};

void backlight_set(uint8_t level) {
  if (level > 0) {
    // Turn on leds
    PORTB &= ~BACKLIGHT_ALPHAS;
    PORTB &= ~BACKLIGHT_FKEYS;
    PORTB &= ~BACKLIGHT_MODNUM;
    PORTE &= ~BACKLIGHT_NUMPAD;
  } else {
    // Turn off leds
    PORTB |= BACKLIGHT_ALPHAS;
    PORTB |= BACKLIGHT_FKEYS;
    PORTB |= BACKLIGHT_MODNUM;
    PORTE |= BACKLIGHT_NUMPAD;
  }
}

void led_set_kb(uint8_t usb_led) {
  bool leds[8] = {
    usb_led & (1<<USB_LED_CAPS_LOCK),
    usb_led & (1<<USB_LED_SCROLL_LOCK),
    usb_led & (1<<USB_LED_NUM_LOCK),
    layer_state & (1<<1),
    layer_state & (1<<2),
    layer_state & (1<<3),
    layer_state & (1<<4),
    layer_state & (1<<5)
  };
  indicator_leds_set(leds);

  led_set_user(usb_led);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
