#include "wm7.h"
#include "led.h"

void matrix_init_kb(void)
{
    matrix_init_user();
    led_init_ports();
}

void matrix_scan_kb(void)
{
    //print("scan...");
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      // Turn capslock on
      PORTE |= (1<<6);
    } else {
      // Turn capslock off
      PORTE &= ~(1<<6);
    }
}

void led_init_ports(void)
{
    // led setting
    // caps lock
    DDRE |= (1<<6);
    PORTE |= (1<<6);

    // ESC 
    DDRB |= (1<<7);
    // INSERT
    DDRB |= (1<<2);
    // DEL
    DDRB |= (1<<3);
}