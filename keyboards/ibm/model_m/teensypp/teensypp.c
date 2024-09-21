/* Copyright 2019 iw0rm3r
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

void led_init_ports(void) {
  /* Setting status LEDs pins to output and +5V (off) */
  gpio_set_pin_output(B4);
  gpio_set_pin_output(B5);
  gpio_set_pin_output(B6);
  gpio_write_pin_high(B4);
  gpio_write_pin_high(B5);
  gpio_write_pin_high(B6);
}

bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if(res) {
    gpio_write_pin(B4, !led_state.num_lock);
    gpio_write_pin(B6, !led_state.caps_lock);
    gpio_write_pin(B5, !led_state.scroll_lock);
  }
  return res;
}
