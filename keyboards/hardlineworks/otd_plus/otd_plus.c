#include "otd_plus.h"

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(CAPS_LOCK_LED_PIN, led_state.caps_lock);
        writePin(SCROLL_LOCK_LED_PIN, led_state.scroll_lock);
    }
    return true;
}


