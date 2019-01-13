
#include "matrix.h"
#include "config.h"
#include "timer.h"
#include "quantum.h"

#define ROWS_PER_HAND (MATRIX_ROWS/2)

#ifndef DEBOUNCING_DELAY
#  define DEBOUNCING_DELAY 5
#endif

#if DEBOUNCING_DELAY > 0

void debounce(matrix_row_t raw[], matrix_row_t cooked[], bool changed)
{
  static uint16_t debouncing_time;
  static bool debouncing = false;

  if (changed)
  {
    debouncing = true;
    debouncing_time = timer_read();
  }

  if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
    for (uint8_t i = 0; i < ROWS_PER_HAND/2; i++) {
      cooked[i] = raw[i];
    }
    debouncing = false;
  }
}

#else

// no debounce
bool debounce(matrix_row_t raw[], matrix_row_t cooked[], bool changed)
{
  if (changed)
  {
  for (uint8_t i = 0; i < ROWS_PER_HAND/2; i++) {
      cooked[i] = raw[i];
    }
  }
}

#endif
