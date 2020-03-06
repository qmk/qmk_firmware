#include "rev4.h"
//#include "backlight.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    led_init_ports();
}

void led_init_ports() {
    // Set our LED pins as output
    palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL); // LED1
    palClearPad(GPIOB, 13);
    palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL); // LED2
    palClearPad(GPIOB, 14);
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); // LED3
    palClearPad(GPIOA, 8);
    palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL); // Capslock LED
    palClearPad(GPIOA, 0);
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
