#include "alice.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(INDICATOR_PIN_0);
    setPinOutput(INDICATOR_PIN_1);
    setPinOutput(INDICATOR_PIN_2);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      writePin(INDICATOR_PIN_0, !led_state.num_lock);
      writePin(INDICATOR_PIN_1, !led_state.caps_lock);
      writePin(INDICATOR_PIN_2, !led_state.scroll_lock);
    }
    return runDefault;
}
