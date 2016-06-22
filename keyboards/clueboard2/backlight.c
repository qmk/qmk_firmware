
#include <avr/io.h>
#include "backlight.h"
#include "print.h"

/* Clueboard 2.0 LED locations:
 *
 * Capslock: B4, pull high to turn on
 * LCtrl: Shared with Capslock, DO NOT INSTALL LED'S IN BOTH
 * Page Up: B7, pull high to turn on
 * Escape: D6, pull high to turn on
 * Arrows: D4, pull high to turn on
 */

void init_backlight_pin(void) {
    print("init_backlight_pin()\n");
    // Set our LED pins as output
    DDRD |= (1<<6); // Esc
    DDRB |= (1<<7); // Page Up
    DDRD |= (1<<4); // Arrows

    // Set our LED pins low
    PORTD &= ~(1<<6); // Esc
    PORTB &= ~(1<<7); // Page Up
    PORTD &= ~(1<<4); // Arrows
}

void backlight_set(uint8_t level) {
    if ( level == 0 ) {
        // Turn off light
        PORTD |= (1<<6); // Esc
        PORTB |= (1<<7); // Page Up
        PORTD |= (1<<4); // Arrows
    } else {
        // Turn on light
        PORTD &= ~(1<<6); // Esc
        PORTB &= ~(1<<7); // Page Up
        PORTD &= ~(1<<4); // Arrows
    }
}

