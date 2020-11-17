#include "rev4.h"
#include "led.h"

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
};

void led_init_ports(void) {
  // * Set our LED pins as output and high
  setPinOutput(D1);
  writePinHigh(D1);
}

bool led_update_kb(led_t led_state) {
  if(led_update_user(led_state)) {
    writePin(D1, !led_state.caps_lock);
  }

  return true;
}
