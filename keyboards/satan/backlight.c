
#include <avr/io.h>
#include "backlight.h"
#include "print.h"

void init_backlight_pin(void) {
    print("init_backlight_pin()\n");
    // Set our LED pins as output
    DDRB |= (1<<6);

    // Set our LED pins low
    PORTB &= ~(1<<6);
}

void backlight_set(uint8_t level) {
    if ( level == 0 ) {
        // Turn off light
        PORTB |= (1<<6);
    } else {
        // Turn on light
        PORTB &= ~(1<<6);
    }
}

