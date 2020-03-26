#include "DecadePad.h"
bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)){
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(D4, led_state.num_lock);
    }
    return true;
}