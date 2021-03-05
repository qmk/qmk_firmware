#include "do60.h"

extern inline void setdefaultrgb(void);

void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  setdefaultrgb();
};
