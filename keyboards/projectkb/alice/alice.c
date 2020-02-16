#include "alice.h"

void matrix_init_board(void){
    setPinOutput(A0);
    setPinOutput(A1);
    setPinOutput(A2);
}

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      writePin(A0, !led_state.num_lock);
      writePin(A1, !led_state.caps_lock);
      writePin(A2, !led_state.scroll_lock);
    }
    return runDefault;
}
