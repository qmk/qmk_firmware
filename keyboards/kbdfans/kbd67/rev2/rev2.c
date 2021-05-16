#include "rev2.h"
void matrix_init_kb(void) {
    setPinOutput(D4);
    matrix_init_user();
}
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(D4, !led_state.caps_lock);
    }
    return res;
}
