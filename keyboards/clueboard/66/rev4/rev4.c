#include "quantum.h"

void led_init_ports(void) {
    // Set our LED pins as output
    gpio_set_pin_output(B13); // LED1
    gpio_write_pin_low(B13);
    gpio_set_pin_output(B14); // LED2
    gpio_write_pin_low(B14);
    gpio_set_pin_output(A8); // LED3
    gpio_write_pin_low(A8);
    gpio_set_pin_output(A0); // Capslock LED
    gpio_write_pin_low(A0);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(B13, led_state.num_lock);
        gpio_write_pin(A0, led_state.caps_lock);
        gpio_write_pin(B14, led_state.caps_lock);
        gpio_write_pin(A8, led_state.scroll_lock);
    }
    return res;
}
