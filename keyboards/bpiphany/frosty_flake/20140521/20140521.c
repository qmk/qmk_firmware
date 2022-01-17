#include "frosty_flake.h"

void keyboard_pre_init_kb() {
    setPinOutput(B7); // num lock
    writePinHigh(B7);
    setPinOutput(C5); // caps lock
    writePinHigh(C7);
    setPinOutput(C6); // scroll lock
    writePinHigh(C6);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t usb_led) {
    // user requests no further processing
    if (!led_update_user(usb_led))
        return true;

    writePin(B7, !usb_led.caps_lock);
    writePin(C5, !usb_led.num_lock);
    writePin(C6, !usb_led.scroll_lock);

    return true;
}
