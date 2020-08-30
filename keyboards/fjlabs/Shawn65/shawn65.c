#include "shawn65.h"

extern inline void shawn65_caps_led_on(void);

extern inline void shawn65_caps_led_off(void);

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        shawn65_caps_led_on();
    } else {
        shawn65_caps_led_off();
    }

    led_set_user(usb_led);
}
