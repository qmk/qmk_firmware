#include "ixora.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    setPinOutput(A8);
    setPinOutput(A9);
    setPinOutput(A10);
    writePinLow(A8);
    writePinLow(A9);
    writePinLow(A10);

    matrix_init_user();
}

void matrix_scan_kb(void) {

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(A10);
    } else {
        writePinLow(A10);
    }
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(A9);
    } else {
        writePinLow(A9);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(A8);
    } else {
        writePinLow(A8);
    }
    led_set_user(usb_led);
}
