/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "split_util.h"
#include "config.h"
#include "timer.h"

// Copy this code to split_common/matrix.c,
// and call it instead of the unoptimized col_reader. Scan-rate jumps from 1200->1920
// Also remove the sleep_us(30), not necessary for this keyboard.
// In usb_descriptor.c, set .PollingIntervalMS      = 0x01
#define ROW_SHIFTER ((uint8_t)1)
inline static matrix_row_t optimized_col_reader(void) {
    //MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }
    return (PINB & (1 << 6) ? 0 : (ROW_SHIFTER << 0)) |
          (PINB & (1 << 2) ? 0 : (ROW_SHIFTER << 1)) |
          (PINB & (1 << 3) ? 0 : (ROW_SHIFTER << 2)) |
          (PINB & (1 << 1) ? 0 : (ROW_SHIFTER << 3)) |
          (PINF & (1 << 7) ? 0 : (ROW_SHIFTER << 4)) |
          (PINF & (1 << 6) ? 0 : (ROW_SHIFTER << 5)) |
          (PINF & (1 << 5) ? 0 : (ROW_SHIFTER << 6)) |
          (PINF & (1 << 4) ? 0 : (ROW_SHIFTER << 7));
}


