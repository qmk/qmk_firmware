#include "350mimi.h"

void matrix_init_board(void){
    setPinOutput(B11);
    setPinOutput(B5);
}


void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B11);
    } else {
        writePinHigh(B11);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinLow(B5);
    } else {
        writePinHigh(B5);
    }
    led_set_user(usb_led);
}
