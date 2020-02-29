#include "kitten_paw.h"

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    CONFIG_LED_IO;
    CONFIG_LED_IO;
    print_dec(usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        USB_LED_CAPS_LOCK_ON;
    else
        USB_LED_CAPS_LOCK_OFF;

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        USB_LED_NUM_LOCK_ON;
    else
        USB_LED_NUM_LOCK_OFF;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        USB_LED_SCROLL_LOCK_ON;
    else
        USB_LED_SCROLL_LOCK_OFF;
}
