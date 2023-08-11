#include "quantum.h"
#include "print.h"

void backlight_init_ports(void) {
    print("init_backlight_pin()\n");
    // Set our LED pins as output
    DDRD |= (1<<0); // Esc
    DDRD |= (1<<4); // Page Up
    DDRD |= (1<<1); // Arrows

    // Set our LED pins low
    PORTD &= ~(1<<0); // Esc
    PORTD &= ~(1<<4); // Page Up
    PORTD &= ~(1<<1); // Arrows
}

void backlight_set(uint8_t level) {
    if ( level == 0 ) {
        // Turn off light
        PORTD |= (1<<0); // Esc
        PORTD |= (1<<4); // Page Up
        PORTD |= (1<<1); // Arrows
    } else {
        // Turn on light
        PORTD &= ~(1<<0); // Esc
        PORTD &= ~(1<<4); // Page Up
        PORTD &= ~(1<<1); // Arrows
    }
}
