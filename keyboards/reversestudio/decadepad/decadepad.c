#include "decadepad.h"
bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)){
        writePin(D4, led_state.num_lock);
    }
    return true;
}