#include "60xt.h"

extern inline void _60xt_caps_led_on(void);
extern inline void _60xt_fn_led_on(void);

extern inline void _60xt_caps_led_off(void);
extern inline void _60xt_fn_led_off(void);


void led_set_kb(uint8_t usb_led) {

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		_idb_60_caps_led_on();
		} else {
		_idb_60_caps_led_off();
    }

	led_set_user(usb_led);
}
