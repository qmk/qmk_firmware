#include "knight.h"
void matrix_init_kb(void) {
    setPinOutput(D1);
    setPinOutput(E2);
    matrix_init_user();
};
void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(D1);
    } else {
        writePinHigh(D1);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(E2);
    } else {
        writePinHigh(E2);
    }
    led_set_user(usb_led);
}
