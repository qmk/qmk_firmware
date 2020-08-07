#include "kabedon980.h"

void keyboard_pre_init_user(void) {
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(E6);
}
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
void led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(E6, !led_state.caps_lock);
    }
    return true;
}



