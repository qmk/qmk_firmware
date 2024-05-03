#include "quantum.h"

void matrix_init_board(void){
    gpio_set_pin_output(A8);
    gpio_set_pin_output(A9);
    gpio_set_pin_output(A10);
}

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      gpio_write_pin(A8, !led_state.num_lock);
      gpio_write_pin(A9, !led_state.caps_lock);
      gpio_write_pin(A10, !led_state.scroll_lock);
    }
    return runDefault;
}
