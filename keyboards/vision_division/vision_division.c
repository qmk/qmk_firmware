#include "vision_division.h"

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  if (usb_led & (1 << USB_LED_CAPS_LOCK))
  {
    // HI
    DDRD  |= (1<<4);
    PORTD |= (1<<4);
  }
  else
  {
    // Hi-Z
    DDRD  &= ~(1<<4);
    PORTD &= ~(1<<4);
  }

  if (usb_led & (1 << USB_LED_NUM_LOCK))
  {
    // HI
    DDRD  |= (1<<5);
    PORTD |= (1<<5);
  }
  else
  {
    // Hi-Z
    DDRD  &= ~(1<<5);
    PORTD &= ~(1<<5);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK))
  {
    // HI
    DDRD  |= (1<<6);
    PORTD |= (1<<6);
  }
  else
  {
    // Hi-Z
    DDRD  &= ~(1<<6);
    PORTD &= ~(1<<6);
  }

	led_set_user(usb_led);
}

