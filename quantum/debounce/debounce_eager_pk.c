/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Basic per-key algorithm. Uses an 8-bit counter per key.
After pressing a key, it immediately changes state, and sets a counter.
No further inputs are accepted until DEBOUNCE milliseconds have occurred.
*/

#include "debounce.h"
#include "matrix.h"
#include "timer.h"

#ifndef DEBOUNCE
  #define DEBOUNCE 5
#endif


#if (MATRIX_COLS <= 8)
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define ROW_SHIFTER  ((uint32_t)1)
#endif



#define debounce_counter_t uint8_t

static matrix_row_t matrix_debounced[MATRIX_ROWS];
static debounce_counter_t debounce_counters[MATRIX_ROWS*MATRIX_COLS];

#define DEBOUNCE_ELAPSED 251
#define MAX_DEBOUNCE (DEBOUNCE_ELAPSED - 1)

void update_debounce_counters(uint8_t current_time);
void transfer_matrix_values(uint8_t current_time);

void matrix_debounce_init(void)
{
  for (uint8_t r = 0; r < MATRIX_ROWS; r++)
  {
    matrix_debounced[r] = 0;
  }

  int i = 0;
  for (uint8_t r = 0; r < MATRIX_ROWS; r++)
  {
    for (uint8_t c = 0; c < MATRIX_COLS; c++)
    {
      debounce_counters[i++] = DEBOUNCE_ELAPSED;
    }
  }
}

void matrix_debounce(void)
{
  uint8_t current_time = timer_read() % MAX_DEBOUNCE;
  update_debounce_counters(current_time);
  transfer_matrix_values(current_time);
}

//If the current time is > debounce counter, set the counter to enable input.
void update_debounce_counters(uint8_t current_time)
{
  debounce_counter_t *debounce_pointer = debounce_counters;
  for (uint8_t row = 0; row < MATRIX_ROWS; row++)
  {
    for (uint8_t col = 0; col < MATRIX_COLS; col++)
    {
      if (*debounce_pointer != DEBOUNCE_ELAPSED)
      {
        if (TIMER_DIFF(current_time, *debounce_pointer, MAX_DEBOUNCE) >=
            DEBOUNCING_DELAY) {
          *debounce_pointer = DEBOUNCE_ELAPSED;
        }
      }
      debounce_pointer++;
    }
  }
}

// upload from raw_matrix to final matrix;
void transfer_matrix_values(uint8_t current_time)
{
  debounce_counter_t *debounce_pointer = debounce_counters;
  for (uint8_t row = 0; row < MATRIX_ROWS; row++)
  {
    matrix_row_t existing_row = matrix_debounced[row]; 
    matrix_row_t raw_row = matrix_get_row(row);

    for (uint8_t col = 0; col < MATRIX_COLS; col++)
    {
      matrix_row_t col_mask = (ROW_SHIFTER << col);
      bool final_value = raw_row & col_mask;
      bool existing_value = existing_row & col_mask;
      if (*debounce_pointer == DEBOUNCE_ELAPSED &&
          (existing_value != final_value))
      {
        *debounce_pointer = current_time;
        existing_row ^= col_mask; //flip the bit.
      }
      debounce_pointer++;
    }
    matrix_debounced[row] = existing_row;
  }  
}



//Implementation of no debounce.
