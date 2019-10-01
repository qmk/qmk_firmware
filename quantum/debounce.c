
#include "matrix.h"
#include "timer.h"
#include "quantum.h"

#ifndef DEBOUNCING_DELAY
#  define DEBOUNCING_DELAY 5
#endif

void debounce_init(uint8_t num_rows) {
}

#if DEBOUNCING_DELAY > 0

static bool debouncing = false;

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
  static uint16_t debouncing_time;

  if (changed) {
    debouncing = true;
    debouncing_time = timer_read();
  }

  if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
    for (uint8_t i = 0; i < num_rows; i++) {
      cooked[i] = raw[i];
    }
    debouncing = false;
  }
}

bool debounce_active(void) {
  return debouncing;
}

#else

// no debounce
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
  if (changed)
  {
  for (uint8_t i = 0; i < num_rows; i++) {
      cooked[i] = raw[i];
    }
  }
}

bool debounce_active(void) {
  return false;
}
#endif
