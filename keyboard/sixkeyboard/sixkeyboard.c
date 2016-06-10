#include "sixkeyboard.h"

__attribute__ ((weak))
void matrix_init_user(void) {
    // leave this function blank - it can be defined in a keymap file
};

__attribute__ ((weak))
void matrix_scan_user(void) {
    // leave this function blank - it can be defined in a keymap file
};

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
    // leave this function blank - it can be defined in a keymap file
};

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

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
};