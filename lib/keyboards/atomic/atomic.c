#include "atomic.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // Turn status LED on
    DDRE |= (1<<6);
    PORTE |= (1<<6);

    matrix_init_user();
}