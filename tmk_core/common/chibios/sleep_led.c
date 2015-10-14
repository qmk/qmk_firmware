#include "ch.h"

#include "led.h"
#include "sleep_led.h"

void sleep_led_init(void) {
	// we could go the 'software way' -- just enable *some* timer
	// and go with callbacks
	// or we could go the 'hardware way' -- and use timer output to
	// pins directly
}

void sleep_led_enable(void) {
    led_set(1<<USB_LED_CAPS_LOCK);
}

void sleep_led_disable(void) {
    led_set(0);
}

void sleep_led_toggle(void) {
    // not working yet, state not saved anywhere currently
}
