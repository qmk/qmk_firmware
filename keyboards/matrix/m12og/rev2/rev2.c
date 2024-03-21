/**
 * rev2.c
 */

#include "quantum.h"

void matrix_init_user(void) {
	setPinOutput(C6);
	setPinOutput(B2);
	setPinOutput(B1);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(B1, !led_state.num_lock);
        writePin(C6, !led_state.caps_lock);
        writePin(B2, !led_state.scroll_lock);
    }
    return res;
}
