#include "rev4.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    led_init_ports();
}

void led_init_ports() {
    // Set our LED pins as output
    setPinOutput(B13); // LED1
    writePinLow(B13);

    setPinOutput(B14); // LED2
    writePinLow(B14);

    setPinOutput(B8); // LED3
    writePinLow(B8);

    setPinOutput(B0); // Capslock LED
    writePinLow(B0);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        palSetPad(GPIOB, 13);    // LED1
    } else {
        palClearPad(GPIOB, 13);  // LED1
    }

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        palSetPad(GPIOA, 0);     // Capslock LED
        palSetPad(GPIOB, 14);    // LED2
    } else {
        palClearPad(GPIOA, 0);   // Capslock LED
        palClearPad(GPIOB, 14);  // LED2
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        palSetPad(GPIOA, 8);     // LED3
    } else {
        palClearPad(GPIOA, 8);   // LED3
    }
}
