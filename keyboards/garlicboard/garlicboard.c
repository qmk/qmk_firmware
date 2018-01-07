#include "garlicboard.h"
#include "led.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	led_init_ports();
};

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
};

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRE |= (1<<6);
    DDRD |= (1<<3);
    DDRC |= (1<<6);
    DDRC |= (1<<7);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        PORTE |= (1<<6);
    } else {
        PORTE &= ~(1<<6);
    }

    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTD |= (1<<3);
    } else {
        PORTD &= ~(1<<3);
    }
}

uint32_t layer_state_set_kb(uint32_t state) {
    if (state & (1<<4)) {
        PORTC |= (1<<6);
    } else {
        PORTC &= ~(1<<6);
    }

    if (state & (1<<2)) {
        PORTC |= (1<<7);
    } else {
        PORTC &= ~(1<<7);
    }

    if (state & (1<<5)) {
        PORTE |= (1<<6);
        PORTD |= (1<<3);
        PORTC |= (1<<6);
        PORTC |= (1<<7);
    } else {
        PORTE &= ~(1<<6);
        PORTD &= ~(1<<3);
        PORTC &= ~(1<<6);
        PORTC &= ~(1<<7);
    }

    return state;
}