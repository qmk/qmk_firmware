#include "sixkeyboard.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    DDRC |= (1<<4);
    PORTC &= ~(1<<4);


    DDRC |= (1<<6);
    PORTC &= ~(1<<6);

    DDRB |= (1<<6);
    PORTB &= ~(1<<6);

    DDRB |= (1<<4);
    PORTB &= ~(1<<4);

    DDRD |= (1<<5);
    PORTD &= ~(1<<5);

    DDRD |= (1<<2);
    PORTD &= ~(1<<2);

    DDRD |= (1<<3);
    PORTD &= ~(1<<3);

    matrix_init_user();
};