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

// Alphas PB1
// Navigation Cluster: PB2
// Number Row, Mods: PB3
// Function Row: PE6
enum BACKLIGHT_AREAS {
  BACKLIGHT_ALPHAS   = 0b00000001,
  BACKLIGHT_NAVI     = 0b00000010,
  BACKLIGHT_MODS     = 0b00000100,
  BACKLIGHT_FROW     = 0b00001000,
  BACKLIGHT_ALL      = 0b00001111
};

// Other than using RGB or LED matrix, QMK cannot turn on specific zones
// of backlight LEDs. Unfortunately, Duck PCBs do not follow this design
// and instead use multiple pins connected to each of these zones. QMK is
// only able to control them ALL with the current default mechanisms. 
void backlight_set(uint8_t zone) {
  // switch(zone) {
  // case 0:
  //   PORTB |= BACKLIGHT_ALPHAS;
  //   PORTB |= BACKLIGHT_MODNUM;
  // break;
  // case 1:
  //   PORTB &= ~BACKLIGHT_ALPHAS;
  //   PORTB |= BACKLIGHT_MODNUM;
  // break;
  // case 2:
  //   PORTB |= BACKLIGHT_ALPHAS;
  //   PORTB &= ~BACKLIGHT_MODNUM;
  // break;
  // case 3:
  //   PORTB &= ~BACKLIGHT_ALPHAS;
  //   PORTB &= ~BACKLIGHT_MODNUM;
  // break;
  // }
}

// Locking indicator LEDs
// The Duck Orion V3 has 3 locking indicator LEDs and are located to the right
// of the Escape key. 
void led_set_kb(uint8_t usb_led) {
  IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) ? writePinLow(B0) : writePinHigh(B0);
  IS_LED_ON(usb_led, USB_LED_NUM_LOCK) ? writePinLow(B4) : writePinHigh(B4);
  IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK) ? writePinLow(D7) : writePinHigh(D7);
  led_set_user(usb_led);
}

// Layer number indicator LEDs
// The Duck Orion V3 only has 5 layer indicator LEDs and are located above the 
// arrow cluster. 
uint32_t layer_state_set_kb(uint32_t state) {
    switch (biton32(state)) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default: 
        break;
    }
  return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
