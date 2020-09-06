#include "xelus87.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  // Set our LED pins as output
  setPinOutput(CAPS_LOCK_LED_PIN);
  setPinOutput(SCROLL_LOCK_LED_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(CAPS_LOCK_LED_PIN, led_state.caps_lock);
        writePin(SCROLL_LOCK_LED_PIN, led_state.scroll_lock);
    }
    return res;
}
