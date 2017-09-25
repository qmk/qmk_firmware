#include "2key.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up


    DDRB |= (1<<5);
    PORTB &= ~(1<<5);

    DDRB |= (1<<6);
    PORTB &= ~(1<<6);

    matrix_init_user();
};
