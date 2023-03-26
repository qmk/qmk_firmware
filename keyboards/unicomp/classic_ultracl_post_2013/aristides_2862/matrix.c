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

#define SHIFTREG_CLK GP6
#define SHIFTREG_SHLD GP5
#define SHIFTREG_DATA GP7

#define SHIFTREG_DELAY_CYCLES 8 /* 64 ns at 125 MHz */

matrix_row_t previous_matrix[MATRIX_ROWS];

static inline void setPinOutput_writeLow(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

pin_t columns[MATRIX_COLS] = {GP11, GP12, GP13, GP14, GP15, GP16, GP17, GP18, GP19, GP20, GP21, GP22, GP1, GP26, GP27, GP28};

void matrix_init_custom_configure_drive_strengths(void);

void matrix_init_custom(void) {
    for (int column=0; column<MATRIX_COLS; column++)
    {
        writePinLow(columns[column]);
        setPinInputHigh(columns[column]);
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
    for (int row=MATRIX_ROWS-1; row>=0; row--) {
        current_matrix[row] = 0;
    }
    for (int column=0; column<MATRIX_COLS; column++) {
        setPinOutput_writeLow(columns[column]);
        matrix_output_select_delay();
        writePinHigh(SHIFTREG_SHLD);
        wait_cpuclock(SHIFTREG_DELAY_CYCLES);
        setPinInputHigh(columns[column]);
        int key_on_col_pressed = 0;
        for (int row=MATRIX_ROWS-1; row>=0; row--) {
            int bit = !(readPin(SHIFTREG_DATA));
            key_on_col_pressed |= bit;
            writePinHigh(SHIFTREG_CLK);
            wait_cpuclock(SHIFTREG_DELAY_CYCLES);
            current_matrix[row] |= bit << column;
            writePinLow(SHIFTREG_CLK);
            wait_cpuclock(SHIFTREG_DELAY_CYCLES);
        }
        writePinLow(SHIFTREG_SHLD);
        matrix_output_unselect_delay(column, key_on_col_pressed);
    }
    return matrix_has_it_changed(current_matrix);
}
