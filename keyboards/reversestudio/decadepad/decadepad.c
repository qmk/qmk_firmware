#include "decadepad.h"
void matrix_init_kb(void) {
  led_init_ports();
  matrix_init_user(); 
};

void led_init_ports(void) {
  setPinOutput(D4);
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)){
        writePin(D4, !led_state.num_lock);
    }
    return true;
}