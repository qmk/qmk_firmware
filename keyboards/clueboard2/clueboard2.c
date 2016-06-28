#include "clueboard2.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	led_init_ports();

    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
};

void led_init_ports() {
    // * Set our LED pins as output
    DDRB |= (1<<4);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTB |= (1<<4);
    } else {
        // Turn capslock off
        PORTB &= ~(1<<4);
    }
}

/* Clueboard 2.0 LED locations:
 *
 * Capslock: B4, pull high to turn on
 * LCtrl: Shared with Capslock, DO NOT INSTALL LED'S IN BOTH
 * Page Up: B7, pull high to turn on
 * Escape: D6, pull high to turn on
 * Arrows: D4, pull high to turn on
 */

void backlight_init_ports(void) {
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
