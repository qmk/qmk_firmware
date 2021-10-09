#include "index_tab.h"

void keyboard_pre_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  keyboard_pre_init_user();
};

void matrix_scan_kb(void) {
  // Looping keyboard code goes here
  // This runs every cycle (a lot)
  matrix_scan_user();
};
