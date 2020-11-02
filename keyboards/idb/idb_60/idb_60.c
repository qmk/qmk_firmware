#include "idb_60.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(C4);
    setPinOutput(C5);
}

// Capslock LED indicator

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        _idb_60_caps_led_on();
    } else {
        _idb_60_caps_led_off();
    }
    led_set_user(usb_led);
}

// Layer LED indicator - drive LED when not on base layer

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 0) {
        _idb_60_fn_led_off();
    } else {
        _idb_60_fn_led_on();
    }
    return state;
}

inline void _idb_60_caps_led_on(void) {
    writePinLow(C5);
}

inline void _idb_60_fn_led_on(void) {
    writePinLow(C4);
}

inline void _idb_60_caps_led_off(void) {
    writePinHigh(C5);
}

inline void _idb_60_fn_led_off(void) {
    writePinHigh(C4);
}
