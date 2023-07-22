#include "quantum.h"

void matrix_init_board(void){
    setPinOutput(A8);
    setPinOutput(A9);
    setPinOutput(A10);
}

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      writePin(A8, !led_state.num_lock);
      writePin(A9, !led_state.caps_lock);
      writePin(A10, !led_state.scroll_lock);
    }
    return runDefault;
}
