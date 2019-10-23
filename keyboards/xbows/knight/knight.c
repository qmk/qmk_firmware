#include "knight.h"
void matrix_init_kb(void) {
    setPinOutput(D1);
    setPinOutput(E2);
    matrix_init_user();
};
void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(D1);
    } else {
        writePinLow(D1);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(E2);
    } else {
        writePinLow(E2);
    }
    led_set_user(usb_led);
}
