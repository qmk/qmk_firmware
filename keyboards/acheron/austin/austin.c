#include "austin.h"

void matrix_init_board(void){
    setPinOutput(A0);
    setPinOutput(A1);
    setPinOutput(A2);
}


void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(A2);
    } else {
        writePinLow(A2);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(A0);
    } else {
        writePinLow(A0);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(A1);
    } else {
        writePinLow(A1);
    }
    led_set_user(usb_led);
}
