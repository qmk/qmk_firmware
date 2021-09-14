/* Copyright 2017 MechMerlin <mechmerlin@gmail.com>
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
#include "v2.h"
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

// Port from backlight_update_state
void led_set_kb(uint8_t usb_led) {
    bool status[8] = {
    host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK), /* LED 3 */
    host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK),   /* LED 2 */
    host_keyboard_leds() & (1<<USB_LED_NUM_LOCK),    /* LED 1 */

    layer_state & (1<<2),                            /* LED 6 */
    layer_state & (1<<1),                            /* LED 5 */
    layer_state & (1<<0) ? 0: 1,                     /* LED 4 */

    layer_state & (1<<5),                            /* LED 8 */
    layer_state & (1<<4)                             /* LED 7 */
  };

  indicator_leds_set(status);
}
