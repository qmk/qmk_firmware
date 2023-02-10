#include QMK_KEYBOARD_H
#include "print.h"

/* CONFIG */
// modify movement rates as a percentage
// use this to reduce mouse sensitivity especially for drag-scrolling
const int SENSITIVITY_X = 40;
const int SENSITIVITY_Y = 40;
const int SENSITIVITY_H = 3;
const int SENSITIVITY_V = 3;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_mouse(KC_BTN1, KC_BTN3, KC_BTN4, KC_BTN2)
};

int move_counters[4]; // array to keep track of "incomplete" moves for low sensitivity settings
const int SENSITIVITY_PERCENTAGES[] = { SENSITIVITY_X, SENSITIVITY_Y, SENSITIVITY_H, SENSITIVITY_V }; // load our sensitivities into array
const char AXIS_NAMES[5] = { 'X', 'Y', 'H', 'V', '\0' }; // for debugging

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
  /* mouse sensitivity fine tuning */
  // put mouse_report into an array so we can interate
  int8_t * reports[] = { &mouse_report->x, &mouse_report->y, &mouse_report->h, &mouse_report->v };
  
  int movement_rounded = 0; // this variable will determine how much to actually move the mouse after processing

  // iterate through all 4 axes (x, y, h and v)
  for (int i = 0; i < 4; i++) {

    if (reports[i] == 0 || SENSITIVITY_PERCENTAGES[i] == 100) continue;  // skip if not moving in this axis or no change required

    // Reset if movement has changed direction
    if (abs(move_counters[i] + *reports[i]) < abs(move_counters[i])) {
      move_counters[i] = *reports[i]; 
    }

    // update movement tally
    move_counters[i] += *reports[i];
    *reports[i] = 0;

    // check if enough movement has taken place to actually move the pointer for real
    if (abs(move_counters[i] * SENSITIVITY_PERCENTAGES[i]) >= 100) { // only do the movement if it's beyond the threshold
      movement_rounded = round(move_counters[i] * SENSITIVITY_PERCENTAGES[i] / 100); // round down the amount of actual movement intended
      move_counters[i] -= movement_rounded * 100 / SENSITIVITY_PERCENTAGES[i]; // subtract this amount of movement to how much we have "stored up"
      *reports[i] = movement_rounded; // actually do the movement
    }

    //xprintf("%c: %d, %d\n", AXIS_NAMES[i], move_counters[i], movement_rounded);

  }


}

