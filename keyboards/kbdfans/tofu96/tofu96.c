#include "tofu96.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
    led_init_ports();
}

void led_init_ports(void) {
    setPinOutput(B2);
    setPinOutput(B0);
	setPinOutput(B1);
}
bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B2, !led_state.caps_lock);
        writePin(B0, !led_state.num_lock);
        writePin(B1, !led_state.scroll_lock);		
    }
    return true;
}