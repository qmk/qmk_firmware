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

#define LEDS_COMMON_ANODE GP5
#define DEC_A0 GP0
#define DEC_A1 GP1
#define DEC_A2 GP2
#define DEC_EN_U1 GP3
#define DEC_EN_U2 GP4
#define ROW_MIN_GPIO GP11

matrix_row_t previous_matrix[MATRIX_ROWS];

static inline void setPinOutput_writeLow(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

void matrix_init_custom(void) {
    setPinOutput(LEDS_COMMON_ANODE);
    writePinHigh(LEDS_COMMON_ANODE);
    setPinOutput(DEC_EN_U1);
    writePinHigh(DEC_EN_U1);
    setPinOutput(DEC_EN_U2);
    writePinHigh(DEC_EN_U2);
    setPinOutput(DEC_A0);
    setPinOutput(DEC_A1);
    setPinOutput(DEC_A2);

    for (int i=0; i<=11; i++)
    {
        setPinInputHigh(ROW_MIN_GPIO + i);
    }
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
    for (int col=0; col<16; col++) {
        uint32_t bit = 1 << col;
        writePin(DEC_A0, col & 1);
        writePin(DEC_A1, (col >> 1) & 1);
        writePin(DEC_A2, (col >> 2) & 1);
        if (col & 0b1000) {
            writePinLow(DEC_EN_U2);
        } else {
            writePinLow(DEC_EN_U1);
        }
        matrix_output_select_delay();
        uint32_t keys_pressed = (~palReadPort(PAL_PORT(GP0)) >> (ROW_MIN_GPIO - GP0)) & 0xfff;
        if (col & 0b1000) {
            writePinHigh(DEC_EN_U2);
        } else {
            writePinHigh(DEC_EN_U1);
        }
        matrix_output_unselect_delay(col, !!keys_pressed);
        for (int row = 0; row < 12; row++) {
            if (keys_pressed & (1 << row)) {
                current_matrix[row] |= bit;
            } else {
                current_matrix[row] &= ~bit;
            }
        }
    }
    return matrix_has_it_changed(current_matrix);
}
