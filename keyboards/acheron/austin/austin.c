#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(A0);
    gpio_set_pin_output(A1);
    gpio_set_pin_output(A2);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        gpio_write_pin(A2, led_state.num_lock);
        gpio_write_pin(A0, led_state.caps_lock);
        gpio_write_pin(A1, led_state.scroll_lock);
    }
    return true;
}
