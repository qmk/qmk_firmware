#include "amjpad.h"
#include "led.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	led_init_ports();
};

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRD |= (1<<6);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // Turn numlock on
        PORTD &= ~(1<<6);
    } else {
        // Turn numlock off
        PORTD |= (1<<6);
    }
}
