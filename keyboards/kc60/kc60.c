#include "quantum.h"

void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        gpio_set_pin_output(B2);
    } else {
        gpio_set_pin_input(B2);
    }
}
