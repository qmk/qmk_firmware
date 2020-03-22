#include "csc027.h"
#include "usb_led.h"
#include "led.h"

#if defined(RGBLIGHT_ENABLE)
#    include "custom_rgb.h"
#elif defined(AUDIO_ENABLE)
#    include "custom_audio.h"
#endif

#if defined(AUDIO_ENABLE) || defined(RGBLIGHT_ENABLE)

bool led_update_user(led_t usb_led) {
    static led_t old_usb_led = {
        .num_lock = false,
        .caps_lock = false,
        .scroll_lock = false
    };

    if(old_usb_led.caps_lock != usb_led.caps_lock) {
        usb_led.caps_lock ? on_usb_led_on() : on_usb_led_off();
    } else if(old_usb_led.num_lock != usb_led.num_lock) {
        usb_led.num_lock ? on_usb_led_on() : on_usb_led_off();
    } else if(old_usb_led.scroll_lock != usb_led.scroll_lock) {
        usb_led.scroll_lock ? on_usb_led_on() : on_usb_led_off();
    }
    old_usb_led = usb_led;

    return true;
}

#endif
