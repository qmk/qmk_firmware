#include "g60.h"
#include "print.h"
#include "../ble.h"
#include "quantum.h"

void led_set_kb(uint8_t usb_led)
{
	if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK))
	{
		writePinLow(F0);
	}
	else
	{
		writePinHigh(F0);
	}
	led_set_user(usb_led);
}

void keyboard_pre_init_kb(void)
{
	setPinOutput(F0);
	writePinHigh(F0);
	keyboard_pre_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
	return process_record_user(keycode, record);
}