#include "350mimi.h"
void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	setPinOutput(B4);
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
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B4, !led_state.caps_lock);
    }
    return true;
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(0, 255, 128);  // Set default HSV - red hue, full saturation, medium brightness
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default

  eeconfig_update_kb(0);
  eeconfig_init_user();
}
