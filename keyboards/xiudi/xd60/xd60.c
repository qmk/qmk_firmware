#include "xd60.h"


extern inline void xd60_caps_led_on(void);
extern inline void xd60_bl_led_on(void);

extern inline void xd60_caps_led_off(void);
extern inline void xd60_bl_led_off(void);


void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        if(!IS_LAYER_ON_STATE(layer_state, 1)){
            setPinOutput(B2);
            writePinLow(B2);
        }
    } else {
        setPinOutput(B2);
        writePinHigh(B2);
    }

    led_set_user(usb_led);
}
