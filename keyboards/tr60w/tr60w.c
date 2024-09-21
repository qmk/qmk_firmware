#include "quantum.h"

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      gpio_write_pin(B1, !led_state.num_lock);
      gpio_write_pin(B2, !led_state.caps_lock);
      gpio_write_pin(B3, !led_state.scroll_lock);
    }
    return runDefault;
}
