#include "sixshooter.h"

extern inline void sixshooter_led_0_on(void);
extern inline void sixshooter_led_1_on(void);
extern inline void sixshooter_led_2_on(void);
extern inline void sixshooter_led_3_on(void);
extern inline void sixshooter_led_4_on(void);
extern inline void sixshooter_led_5_on(void);

extern inline void sixshooter_led_0_off(void);
extern inline void sixshooter_led_1_off(void);
extern inline void sixshooter_led_2_off(void);
extern inline void sixshooter_led_3_off(void);
extern inline void sixshooter_led_4_off(void);
extern inline void sixshooter_led_5_off(void);

extern inline void sixshooter_led_all_on(void);
extern inline void sixshooter_led_all_off(void);

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
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	led_set_user(usb_led);
}
