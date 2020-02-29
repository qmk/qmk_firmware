#include "frosty_flake.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {
    DDRB |= (1<<7);
    DDRC |= (1<<5) | (1<<6);

    print_dec(usb_led);

    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTC &= ~(1<<5);
    else
        PORTC |=  (1<<5);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTC &= ~(1<<6);
    else
        PORTC |=  (1<<6);

    led_set_user(usb_led);
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
}
