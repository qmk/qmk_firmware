#include "stapelberg.h"

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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

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
