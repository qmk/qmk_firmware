#include "quantum.h"

void led_init_ports(void) {
    // Set our LED pins as output
    setPinOutput(B13); // LED1
    gpio_write_pin_low(B13);
    setPinOutput(B14); // LED2
    gpio_write_pin_low(B14);
    setPinOutput(A8); // LED3
    gpio_write_pin_low(A8);
    setPinOutput(A0); // Capslock LED
    gpio_write_pin_low(A0);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B13, led_state.num_lock);
        writePin(A0, led_state.caps_lock);
        writePin(B14, led_state.caps_lock);
        writePin(A8, led_state.scroll_lock);
    }
    return res;
}
