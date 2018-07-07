#include "al1.h"

void matrix_init_kb(void) {
	matrix_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    CONFIG_LED_IO;
    print_dec(usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTD &= ~(1<<0);
    else
        PORTD |=  (1<<0);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTD &= ~(1<<1);
    else
        PORTD |=  (1<<1);
	led_set_user(usb_led);
}
