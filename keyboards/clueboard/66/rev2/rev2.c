#include "quantum.h"
#include "print.h"

void backlight_init_ports(void) {
    print("init_backlight_pin()\n");
    // Set our LED pins as output
    gpio_set_pin_output(D6); // Esc
    gpio_set_pin_output(B7); // Page Up
    gpio_set_pin_output(D4); // Arrows

    // Set our LED pins low
    gpio_write_pin_low(D6); // Esc
    gpio_write_pin_low(B7); // Page Up
    gpio_write_pin_low(D4); // Arrows
}

void backlight_set(uint8_t level) {
    if ( level == 0 ) {
        // Turn off light
        gpio_write_pin_high(D6); // Esc
        gpio_write_pin_high(B7); // Page Up
        gpio_write_pin_high(D4); // Arrows
    } else {
        // Turn on light
        gpio_write_pin_low(D6); // Esc
        gpio_write_pin_low(B7); // Page Up
        gpio_write_pin_low(D4); // Arrows
    }
}
