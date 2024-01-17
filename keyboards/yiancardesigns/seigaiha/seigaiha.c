/* Copyright 2021 Yiancar-Designs
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
#include "i2c_master.h"

// There is no need to initialize the I/O it is done in matrix.c

uint8_t send_data = 0x00;

void led_update_ports(led_t led_state) {
    if (led_state.caps_lock){
        send_data |= 1 << 5;
    } else {
        send_data &= ~(1 << 5);
    }
    i2c_write_register((PORT_EXPANDER_ADDRESS << 1), 0x0A, &send_data, 1, 20);
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, 1)) {
        send_data |= 1 << 6;
    }
    if (IS_LAYER_OFF_STATE(state, 1)) {
        send_data &= ~(1 << 6);
    }
    // Data is send to the port expander during led_update_kb as it runs continuously.
  return state;
}
