/* Copyright 2023 9R
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

#include "leds.h"

//////////// Status LEDs //////////////
void init_leds(void) {
  setPinOutput(STATUS_LED_A_PIN) ;
  setPinOutput(STATUS_LED_B_PIN) ;
  writePinHigh(STATUS_LED_A_PIN) ; //Led0 off
  writePinHigh(STATUS_LED_B_PIN) ; //Led1 off
}

void set_leds(int active_layer) {
  //display active layer in binary
  switch (active_layer) {
    case 1:
      writePinLow(STATUS_LED_A_PIN);  //Led0 on
      writePinHigh(STATUS_LED_B_PIN); //Led1 off
      break;
    case 2:
      writePinHigh(STATUS_LED_A_PIN);  //Led0 off
      writePinLow(STATUS_LED_B_PIN); //Led1 on
      break;
    case 3:
      writePinLow(STATUS_LED_A_PIN); //Led0 on
      writePinLow(STATUS_LED_B_PIN);  //Led1 on
      break;
    default:
      writePinHigh(STATUS_LED_A_PIN); //Led0 off
      writePinHigh(STATUS_LED_B_PIN); //Led1 off
      break;
  }
}
