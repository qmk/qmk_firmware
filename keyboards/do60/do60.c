#include "do60.h"
#include "led.h"

//extern inline void do60_caps_led_on(void);
//extern inline void do60_bl_led_on(void);

//extern inline void do60_caps_led_off(void);
//extern inline void do60_bl_led_off(void);

extern inline void setdefaultrgb(void);


void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  led_init_ports();
  setdefaultrgb();
};

void led_init_ports(void) {
  // Set caps lock LED pin as output
  DDRB |= (1 << 2);
  // Default to off
  PORTB |= (1 << 2);
}

void led_set_kb(uint8_t usb_led) {
	//if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
	//	do60_caps_led_on();
	//} else {
	//	do60_caps_led_off();
	//}

	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTB &= ~(1<<2);
    } else {
        // Turn capslock off
        PORTB |= (1<<2);
    }
}
