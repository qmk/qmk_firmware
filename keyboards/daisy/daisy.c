#include "daisy.h"

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRC  |=  (1<<PC6);
        PORTC &= ~(1<<PC6);
    } else {
        // Hi-Z
        DDRC  &= ~(1<<PC6);
        PORTC &= ~(1<<PC6);
  }
	led_set_user(usb_led);
}