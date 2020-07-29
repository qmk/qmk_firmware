#include "do60.h"

extern inline void setdefaultrgb(void);


void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
  setdefaultrgb();
};

void led_init_ports(void) {
  // Set caps lock LED pin as output
  setPinOutput(B2);
  // Default to off
  writePinHigh(B2);
}

bool led_update_kb(led_t led_state) {
  if(led_update_user(led_state)) {
    writePin(B2, !led_state.caps_lock);
  }

  return true;
}
