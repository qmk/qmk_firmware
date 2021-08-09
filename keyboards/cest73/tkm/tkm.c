#include "tkm.h"

/* the LEDs: 
 *  PF5 - CAPS
 *  PF6 - NUM
 *  PF7 - SCLK
 *  PE6 - Backlight */

void keyboard_pre_init_kb(void) {
  // Set our LED pins as output
  setPinOutput(F5);
  setPinOutput(F6);
  setPinOutput(F7);
  // Set backlight pin as output
  setPinOutput(E6);
  
  keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(F5, !led_state.caps_lock);
        writePin(F6, !led_state.num_lock);
        writePin(F7, !led_state.scroll_lock);
    }
    return res;
}
