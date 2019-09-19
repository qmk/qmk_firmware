#include "dz60.h"
#include "led.h"

void matrix_init_kb(void) {
    // Keyboard start-up code goes here
    // Runs once when the firmware starts up
    matrix_init_user();
    led_init_ports();
};

void matrix_scan_kb(void) {
    // Looping keyboard code goes here
    // This runs every cycle (a lot)
    matrix_scan_user();
};

void led_init_ports(void) {
    // Set caps lock LED pin as output
    setPinOutput(B2);
    // Default to off
    writePinLow(B2);
}

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B2);
    } else {
        writePinHigh(B2);
    }

    led_set_user(usb_led);
}
