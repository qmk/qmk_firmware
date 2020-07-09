#include "stapelberg.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
    // * Set our LED pins as output
    DDRC |= (1<<3); // Keypad LED: C3
    DDRC |= (1<<4); // ScrLock LED: C4
    DDRC |= (1<<5); // NumLock LED: C5
    DDRC |= (1<<1); // CapsLock LED: C1

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
  DDRC |= (1<<3); // Keypad LED: C3
  DDRC |= (1<<4); // ScrLock LED: C4
  DDRC |= (1<<5); // NumLock LED: C5
  DDRC |= (1<<1); // CapsLock LED: C1
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_COMPOSE)) {
      PORTC &= ~(1<<3);
  } else {
      PORTC |= (1<<3);
  }

  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
      PORTC &= ~(1<<4);
  } else {
      PORTC |= (1<<4);
  }

  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
      PORTC &= ~(1<<5);
  } else {
      PORTC |= (1<<5);
  }

  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      PORTC &= ~(1<<1);
  } else {
      PORTC |= (1<<1);
  }
}
