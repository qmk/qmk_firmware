#include "stapelberg.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
    // * Set our LED pins as output
    DDRF |= (1<<0); // Keypad LED
    DDRF |= (1<<1); // ScrLock LED
    DDRF |= (1<<2); // NumLock LED
    DDRF |= (1<<3); // CapsLock LED

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_init_ports() {
    // * Set our LED pins as output
    DDRF |= (1<<0); // Keypad LED
    DDRF |= (1<<1); // ScrLock LED
    DDRF |= (1<<2); // NumLock LED
    DDRF |= (1<<3); // CapsLock LED
}

void led_set_kb(uint8_t usb_led) {
    DDRF |= (1<<0); // Keypad LED
    if (usb_led & (1<<USB_LED_COMPOSE)) {
        PORTF |= (1<<0);
    } else {
        PORTF &= ~(1<<0);
    }

    DDRF |= (1<<1); // ScrLock LED
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        PORTF |= (1<<1);
    } else {
        PORTF &= ~(1<<1);
    }

    DDRF |= (1<<2); // NumLock LED
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTF |= (1<<2);
    } else {
        PORTF &= ~(1<<2);
    }

    DDRF |= (1<<3); // CapsLock LED
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        PORTF |= (1<<3);
    } else {
        PORTF &= ~(1<<3);
    }

	led_set_user(usb_led);

inline void kinesis_keypad_led_on(void)    { DDRF |=  (1<<0); PORTF |=  (1<<0); }
inline void kinesis_scroll_led_on(void)    { DDRF |=  (1<<1); PORTF |=  (1<<1); }
inline void kinesis_num_led_on(void)    { DDRF |=  (1<<2); PORTF |=  (1<<2); }
inline void kinesis_caps_led_on(void)    { DDRF |=  (1<<3); PORTF |=  (1<<3); }

inline void kinesis_keypad_led_off(void)   { DDRF &= ~(1<<0); PORTF &= ~(1<<0); }
inline void kinesis_scroll_led_off(void)   { DDRF &= ~(1<<1); PORTF &= ~(1<<1); }
inline void kinesis_num_led_off(void)   { DDRF &= ~(1<<2); PORTF &= ~(1<<2); }
inline void kinesis_caps_led_off(void)   { DDRF &= ~(1<<3); PORTF &= ~(1<<3); }


}

/* This is the old code that has the port information in it.
inline void kinesis_keypad_led_on(void)    { DDRF |=  (1<<0); PORTF |=  (1<<0); }
inline void kinesis_scroll_led_on(void)    { DDRF |=  (1<<1); PORTF |=  (1<<1); }
inline void kinesis_num_led_on(void)    { DDRF |=  (1<<2); PORTF |=  (1<<2); }
inline void kinesis_caps_led_on(void)    { DDRF |=  (1<<3); PORTF |=  (1<<3); }

inline void kinesis_keypad_led_off(void)   { DDRF &= ~(1<<0); PORTF &= ~(1<<0); }
inline void kinesis_scroll_led_off(void)   { DDRF &= ~(1<<1); PORTF &= ~(1<<1); }
inline void kinesis_num_led_off(void)   { DDRF &= ~(1<<2); PORTF &= ~(1<<2); }
inline void kinesis_caps_led_off(void)   { DDRF &= ~(1<<3); PORTF &= ~(1<<3); }
*/
