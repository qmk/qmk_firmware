/**
 * rev2.c
 */

#include "quantum.h"

void matrix_init_user(void) {
	gpio_set_pin_output(C6);
	gpio_set_pin_output(B2);
	gpio_set_pin_output(B1);
  
  matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        gpio_write_pin(B1, !led_state.num_lock);
        gpio_write_pin(C6, !led_state.caps_lock);
        gpio_write_pin(B2, !led_state.scroll_lock);
    }
    return res;
}
