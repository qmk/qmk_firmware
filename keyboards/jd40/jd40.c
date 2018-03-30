#include "jd40.h"

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	

  //  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
	//	gh60_caps_led_on();
	//	} else {
	//	gh60_caps_led_off(); 
  //  }
	
    // if (usb_led & (1<<USB_LED_NUM_LOCK)) {
		// gh60_esc_led_on();
		// } else {
		// gh60_esc_led_off(); 
    // }
	
    // if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
		// gh60_fn_led_on();
		// } else {
		// gh60_fn_led_off(); 	
    // }

	led_set_user(usb_led);	
}
