#include "kc60.h"

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        if (led_state.caps_lock) {
            setPinOutput(B2);
        } else {
            setPinInput(B2);
        }
    }

    return true;
}
