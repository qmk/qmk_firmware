#include "alice.h"

void matrix_init_board(void){
    setPinOutput(A0);
    setPinOutput(A1);
    setPinOutput(A2);
}


void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(A0);
    } else {
        writePinHigh(A0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(A1);
    } else {
        writePinHigh(A1);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinLow(A2);
    } else {
        writePinHigh(A2);
    }
    led_set_user(usb_led);
}
