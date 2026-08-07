#include "quantum.h"

void matrix_init_kb(void) {

    // Turn status LED on
    //gpio_set_pin_output(E6);
    gpio_write_pin_high(E6);

	matrix_init_user();
};
