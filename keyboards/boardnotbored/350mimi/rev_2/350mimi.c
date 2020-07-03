#include "350mimi.h"
void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(B4);
void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        // Turn capslock on
		writePinHigh(B4);
    } else {
        // Turn capslock off
		writePinLow(B4);
    }

	led_set_user(usb_led);
}
