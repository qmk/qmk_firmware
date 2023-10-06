/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "quantum.h"

void matrix_init_user(void) {
  setPinOutput(GP9); //init gpio
  writePinLow(GP9);
  setPinOutput(GP11); //init and turn off inverted power led
  writePinHigh(GP11);
}

//layer, capslock and numlock
layer_state_t layer_state_set_user(layer_state_t state) {
	writePin(GP9, layer_state_cmp(state, 1));
    return state;
}

bool led_update_user(led_t led_state) {
    led_state.num_lock = !led_state.num_lock;
    led_update_ports(led_state);
    return false;
}

