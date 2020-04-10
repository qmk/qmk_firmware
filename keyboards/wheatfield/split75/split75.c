#include "split75.h"

#include "i2c_master.h"


void keyboard_pre_init_kb(void) {
    led_init_ports();
    keyboard_pre_init_user();
}

void led_init_ports(void) {
    setPinOutput(NUMLOCK_LED_PIN);
    setPinOutput(CAPSLOCK_LED_PIN);
    setPinOutput(SCROLLLOCK_LED_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(NUMLOCK_LED_PIN, led_state.num_lock);
        writePin(CAPSLOCK_LED_PIN, led_state.caps_lock);
        writePin(SCROLLLOCK_LED_PIN, led_state.scroll_lock);
    }
    return res;
}
