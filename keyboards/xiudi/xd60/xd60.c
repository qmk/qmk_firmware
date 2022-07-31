#include "xd60.h"


extern inline void xd60_caps_led_on(void);
extern inline void xd60_bl_led_on(void);

extern inline void xd60_caps_led_off(void);
extern inline void xd60_bl_led_off(void);


void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		xd60_caps_led_on();
	} else {
		xd60_caps_led_off();
  }

  // if (usb_led & (1<<USB_LED_NUM_LOCK)) {
	// xd60_esc_led_on();
	// } else {
	// xd60_esc_led_off();
  // }

  // if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
	// xd60_fn_led_on();
	// } else {
	// xd60_fn_led_off();
  // }

	led_set_user(usb_led);
}
