/* Copyright 2023 Purdea Andrei
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include <hardware/structs/pads_qspi.h>

#define SHIFTREG_CLK GP26
#define SHIFTREG_SHLD GP27
#define SHIFTREG_DATA GP24

#define SHIFTREG_DELAY_CYCLES 8 /* 64 ns at 125 MHz */

matrix_row_t previous_matrix[MATRIX_ROWS];

static inline void setPinOutput_writeLow(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

void matrix_init_custom(void) {
    for (int i=0; i<=7; i++)
    {
        setPinInputHigh(i);
    }
    for (int i=8; i<=19; i++)
    {
        writePinLow(i);
        setPinInputHigh(i);
    }

    setPinInput(SHIFTREG_DATA);
    writePinLow(SHIFTREG_CLK);
    setPinOutput(SHIFTREG_CLK);
    writePinLow(SHIFTREG_SHLD);
    setPinOutput(SHIFTREG_SHLD);
}

bool matrix_has_it_changed(const matrix_row_t current_matrix[]) {
    bool changed = false;
    for (uint8_t row=0; row<MATRIX_ROWS; row++)
    {
        if (previous_matrix[row] != current_matrix[row]) changed = true;
        previous_matrix[row] = current_matrix[row];
    }
    return changed;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    for (int row=0; row<12; row++) {
        setPinOutput_writeLow(8 + row);
        matrix_output_select_delay();
        writePinHigh(SHIFTREG_SHLD);
        uint8_t high_byte = palReadPort(PAL_PORT(GP0)) & 0xff;
        setPinInputHigh(8 + row);
        uint8_t read_result = 0;
        for (int column=7;column>=0;column--) {
            int bit = !!(readPin(SHIFTREG_DATA));
            writePinHigh(SHIFTREG_CLK);
            wait_cpuclock(SHIFTREG_DELAY_CYCLES);
            read_result |= bit << column;
            writePinLow(SHIFTREG_CLK);
            wait_cpuclock(SHIFTREG_DELAY_CYCLES);
        }
        writePinLow(SHIFTREG_SHLD);
        matrix_row_t current_row_value = ~(bitrev(read_result) | (bitrev(high_byte) << 8));
        matrix_output_unselect_delay(row, current_row_value != 0);
        current_matrix[row] = current_row_value;
    }
    return matrix_has_it_changed(current_matrix);
}
