#include "csc027.h"
#include "usb_led.h"
#include "led.h"

#if defined(RGBLIGHT_ENABLE)
#    include "custom_rgb.h"
#elif defined(AUDIO_ENABLE)
#    include "custom_audio.h"
#endif

#if defined(AUDIO_ENABLE) || defined(RGBLIGHT_ENABLE)

void led_set_user(uint8_t usb_led) {
    static uint8_t old_usb_led = 0;

    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) && !IS_LED_ON(old_usb_led, USB_LED_CAPS_LOCK)) {
        // If CAPS LK LED is turning on...
        on_usb_led_on();
    } else if(!IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) && IS_LED_ON(old_usb_led, USB_LED_CAPS_LOCK)) {
        // If CAPS LK LED is turning off...
        on_usb_led_off();
    } else if(IS_LED_ON(usb_led, USB_LED_NUM_LOCK) && !IS_LED_ON(old_usb_led, USB_LED_NUM_LOCK)) {
        // If NUM LK LED is turning on...
        on_usb_led_on();
    } else if(!IS_LED_ON(usb_led, USB_LED_NUM_LOCK) && IS_LED_ON(old_usb_led, USB_LED_NUM_LOCK)) {
        // If NUM LED is turning off...
        on_usb_led_off();
    } else if(IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK) && !IS_LED_ON(old_usb_led, USB_LED_SCROLL_LOCK)) {
        // If SCROLL LK LED is turning on...
        on_usb_led_on();
    } else if(!IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK) && IS_LED_ON(old_usb_led, USB_LED_SCROLL_LOCK)) {
        // If SCROLL LED is turning off...
        on_usb_led_off();
    }
    old_usb_led = usb_led;
}

#endif
