#include "quantum.h"

void led_init_ports(void) {
    gpio_set_pin_output(B2);
    gpio_set_pin_output(B6);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(B2, !led_state.caps_lock);
        gpio_write_pin(B6, led_state.raw == 0);
    }
    return res;
}
