#include "350mimi.h"
void matrix_init_board(void){
    setPinOutput(B4);
}

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      writePin(B4, led_state.caps_lock);
    }
    return runDefault;
}
