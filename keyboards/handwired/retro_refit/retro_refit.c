#include "quantum.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // Disable status LED on KB, enable status LED on Teensy (KB_STATUS = !TEENSY_STATUS)
    gpio_set_pin_output(D6);
    gpio_write_pin_high(D6);

    matrix_init_user();
};
