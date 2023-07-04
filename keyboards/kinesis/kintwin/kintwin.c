/* Copyright 2023 Alex Stepanov
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

#include "quantum.h"

void matrix_init_kb(void) {

  uint8_t led_delay_ms = 80;

  /* LED pins setup */
  setPinOutput(LED_CAPS_PIN);
  writePinLow(LED_CAPS_PIN);

  wait_ms(led_delay_ms);
  setPinOutput(LED_NUM_PIN);   
  writePinLow(LED_NUM_PIN);
  wait_ms(led_delay_ms);

  setPinOutput(LED_SCRL_PIN);   
  writePinLow(LED_SCRL_PIN);
  wait_ms(led_delay_ms);

  setPinOutput(LED_KPD_PIN);   
  writePinLow(LED_KPD_PIN);
  wait_ms(led_delay_ms);
  writePinHigh(LED_KPD_PIN);

	matrix_init_user();
}
