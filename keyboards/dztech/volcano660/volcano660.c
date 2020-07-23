#include "volcano660.h"
void matrix_init_kb(void) {
    setPinOutput(D0);
    setPinOutput(D1);
    setPinOutput(D2); 
    matrix_init_user();
}
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(D0, !led_state.num_lock);
        writePin(D2, !led_state.caps_lock);
        writePin(D1, !led_state.scroll_lock);

    }
    return res;
}
