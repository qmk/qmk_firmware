#include "quantum.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    gpio_set_pin_output(C4);
    gpio_write_pin_low(C4);

    gpio_set_pin_output(C6);
    gpio_write_pin_low(C6);

    gpio_set_pin_output(B6);
    gpio_write_pin_low(B6);

    gpio_set_pin_output(B4);
    gpio_write_pin_low(B4);

    gpio_set_pin_output(D5);
    gpio_write_pin_low(D5);

    gpio_set_pin_output(D2);
    gpio_write_pin_low(D2);

    gpio_set_pin_output(D3);
    gpio_write_pin_low(D3);

    matrix_init_user();
};