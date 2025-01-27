#include "quantum.h"

void led_init_ports(void) {
    gpio_set_pin_output(F0);
    gpio_set_pin_output(F1);
    gpio_set_pin_output(F4);
}