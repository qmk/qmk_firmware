#include "cospad.h"
#include "led.h"

extern inline void cospad_bl_led_on(void);
extern inline void cospad_bl_led_off(void);
extern inline void cospad_bl_led_togg(void);

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
    DDRB |= (1<<2);
    DDRF |= (1<<7);
    // * Setting BL LEDs to init as off
    PORTF |= (1<<7);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // Turn numlock on
        PORTB &= ~(1<<2);
    } else {
        // Turn numlock off
        PORTB |= (1<<2);
    }    
}
