/* Copyright 2019 Mechlovin
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
#include "hannah910.h"

void matrix_init_kb(void) {
  matrix_init_user();
  led_init_ports();
};
void led_init_ports(void) {
  setPinOutput(B2);
  setPinOutput(D0);
  setPinOutput(D1);
  setPinOutput(D2);

}
void led_set_kb(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(B2);
  } else {
    writePinLow(B2);
  }
      led_set_user(usb_led);
}

uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 1, turn on D2 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinHigh(D2);
    } else {
        writePinLow(D2);
    }
  // if on layer 2, turn on D1 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinHigh(D1);
    } else {
        writePinLow(D1);
    }

  // if on layer 3, turn on D0 LED, otherwise off.
    if (biton32(state) == 3) {
        writePinHigh(D0);
    } else {
        writePinLow(D0);
    }

    return state;
}
