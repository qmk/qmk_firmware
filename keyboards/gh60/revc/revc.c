#include "revc.h"


extern inline void gh60_caps_led_on(void);
extern inline void gh60_poker_leds_on(void);
extern inline void gh60_fn_led_on(void);
extern inline void gh60_esc_led_on(void);
extern inline void gh60_wasd_leds_on(void);

extern inline void gh60_caps_led_off(void);
extern inline void gh60_poker_leds_off(void);
extern inline void gh60_fn_led_off(void);
extern inline void gh60_esc_led_off(void);
extern inline void gh60_wasd_leds_off(void);


void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        gh60_caps_led_on();
    } else {
        gh60_caps_led_off();
    }

    led_set_user(usb_led);
}
