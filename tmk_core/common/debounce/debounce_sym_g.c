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
Basic global debounce algorithm. Used in 99% of keyboards at time of implementation
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/
#include "debounce.h"
#include "matrix.h"
#include "timer.h"
#ifndef DEBOUNCE
  #define DEBOUNCE 5
#endif
static matrix_row_t matrix_debounced[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time;

void matrix_debounce_init(void)
{
  for (uint8_t r = 0; r < MATRIX_ROWS; r++)
  {
    matrix_debounced[r] = 0;
  }
}

void matrix_debounce(void)
{
  for (uint8_t r = 0; r < MATRIX_ROWS; r++)
  {
    matrix_row_t raw = matrix_get_row(r);
    if (raw != matrix_debounced[r])
    {
      debouncing = true;
      debouncing_time = timer_read();
    }
  }
  if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
    for (int i = 0; i < MATRIX_ROWS; i++) {
      matrix_debounced[i] = matrix_get_row(i);
    }
    debouncing = false;
  }
}

matrix_row_t matrix_debounce_get_row(uint8_t row)
{
  return matrix_debounced[row];
}
