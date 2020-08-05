#include "selene.h"

void matrix_init_kb(void){
    setPinOutput(A2);
    setPinOutput(A1);
    setPinOutput(A0);
}

void keyboard_post_init_user(void) {
    rgblight_setrgb(0xff, 0xff, 0xff);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(A0, led_state.num_lock);
        writePin(A2, led_state.caps_lock);
        writePin(A1, led_state.scroll_lock);
    }
    return res;
}
