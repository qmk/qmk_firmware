#include "kitten_paw.h"

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

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    CONFIG_LED_IO;
    CONFIG_LED_IO;
    print_dec(usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        USB_LED_CAPS_LOCK_ON;
    else
        USB_LED_CAPS_LOCK_OFF;

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        USB_LED_NUM_LOCK_ON;
    else
        USB_LED_NUM_LOCK_OFF;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        USB_LED_SCROLL_LOCK_ON;
    else
        USB_LED_SCROLL_LOCK_OFF;
	led_set_user(usb_led);
}
