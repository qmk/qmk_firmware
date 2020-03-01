#include "rev4.h"
//#include "backlight.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    led_init_ports();
}

void backlight_init_ports(void) {
    print("init_backlight_pin()\n");
    // Set our LED pins as output
    //DDRD |= (1<<6); // Esc
    //DDRB |= (1<<7); // Page Up
    //DDRD |= (1<<4); // Arrows

    // Set our LED pins low
    //PORTD &= ~(1<<6); // Esc
    //PORTB &= ~(1<<7); // Page Up
    //PORTD &= ~(1<<4); // Arrows
}

void backlight_set(uint8_t level) {
/*
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
*/
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
