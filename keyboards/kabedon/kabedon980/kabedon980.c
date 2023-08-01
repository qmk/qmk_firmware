#include "quantum.h"

 bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(E6, !led_state.caps_lock);
    }
    return true;
}
