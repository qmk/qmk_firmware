#include "erdnuss65.h"

//Initialize all RGB indicators to 'off'
__attribute__((weak))
void keyboard_post_init_user(void) {
    rgblight_setrgb_at(0, 0, 0, 0); 
}

//Indicator light function
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
 //       writePin(A15, !led_state.caps_lock);  //Un-comment this line to enable in-switch capslock indicator
    if (led_state.caps_lock) {
        rgblight_setrgb_at(255, 255, 255, 0); //white
    } else {
        rgblight_setrgb_at(0, 0, 0, 0);
    }
}
    return res;
}