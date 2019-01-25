#include <string.h>
#include "config.h"
#include "matrix.h"
#include "timer.h"
#include "quantum.h"

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif

//Debouncing counters
typedef uint8_t debounce_counter_t;
#define DEBOUNCE_COUNTER_MODULO 250
#define DEBOUNCE_COUNTER_INACTIVE 251

static debounce_counter_t *debounce_counters;

void debounce_init(uint8_t num_rows)
{
  debounce_counters = malloc(num_rows*MATRIX_COLS);
  memset(debounce_counters, DEBOUNCE_COUNTER_INACTIVE, num_rows*MATRIX_COLS);
}

void update_debounce_counters(uint8_t num_rows, uint8_t current_time)
{
  for (uint8_t row = 0; row < num_rows; row++)
  {
    for (uint8_t col = 0; col < MATRIX_COLS; col++)
    {
      if (debounce_counters[row*MATRIX_COLS + col] != DEBOUNCE_COUNTER_INACTIVE)
      {
        if (TIMER_DIFF(current_time, debounce_counters[row*MATRIX_COLS + col], DEBOUNCE_COUNTER_MODULO) >= DEBOUNCING_DELAY) {
          debounce_counters[row*MATRIX_COLS + col] = DEBOUNCE_COUNTER_INACTIVE;
        }
      }
    }
  }
}

void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time)
{
    for (uint8_t row = 0; row < num_rows; row++)
    {
      matrix_row_t delta = raw[row] ^ cooked[row];

      for (uint8_t col = 0; col < MATRIX_COLS; col++)
      {
          if (debounce_counters[row*MATRIX_COLS + col] == DEBOUNCE_COUNTER_INACTIVE && (delta & (1<<col)))
          {
              debounce_counters[row*MATRIX_COLS + col] = current_time;
              cooked[row] ^= (1 << col);
          }
      }
    }
}

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed)
{
    uint8_t current_time = timer_read() % DEBOUNCE_COUNTER_MODULO;

    update_debounce_counters(num_rows, current_time);
    transfer_matrix_values(raw, cooked, num_rows, current_time);
}