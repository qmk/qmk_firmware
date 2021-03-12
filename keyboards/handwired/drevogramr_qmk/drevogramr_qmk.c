/* Copyright 2021 wwwMADwww <4d4144h@gmail.com>
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

#include "config.h"

#include <stdint.h>
#include <stdbool.h>

#include "quantum.h"
#include "led.h"

/*==========================================================================
============================================================================
==========================================================================*/

int matrixArraySize = MATRIX_ROWS * sizeof(matrix_row_t);
matrix_row_t oldMatrix[MATRIX_ROWS];

uint8_t keyMatrixRowPins[MATRIX_ROWS] = MATRIX_PIN_ROWS;


/*==========================================================================
============================================================================
==========================================================================*/


/* initial matrix state, no columns is active */
void keyMatrixClear(void) {

    for(int i = 0; i < MATRIX_COLS; i++) {
        writePinHigh(MATRIX_PIN_REG_SHIFT);
        writePinLow(MATRIX_PIN_REG_SHIFT);
    }

    writePinHigh(MATRIX_PIN_REG_STORE);
    writePinLow(MATRIX_PIN_REG_STORE);

}



void keyMatrixInit(void) {

    for (int i = 0; i < MATRIX_ROWS ; i++) {
        setPinInputHigh(keyMatrixRowPins[i]);
    }

    setPinOutput(MATRIX_PIN_REG_DATA);
    writePinLow(MATRIX_PIN_REG_DATA);

    setPinOutput(MATRIX_PIN_REG_STORE);
    writePinLow(MATRIX_PIN_REG_STORE);

    setPinOutput(MATRIX_PIN_REG_SHIFT);
    writePinLow(MATRIX_PIN_REG_SHIFT);

    keyMatrixClear();

}



/*
    setting first column active.
    assuming that keyMatrixClear was called right before this or keyMatrixShift was called at least MATRIX_COLS times
*/
void keyMatrixReset(void) {

    writePinLow(MATRIX_PIN_REG_DATA);
    
    writePinHigh(MATRIX_PIN_REG_SHIFT);
    writePinLow(MATRIX_PIN_REG_SHIFT);

    writePinHigh(MATRIX_PIN_REG_DATA);

    writePinHigh(MATRIX_PIN_REG_STORE);
    writePinLow(MATRIX_PIN_REG_STORE);

}



/* setting next column active */
void keyMatrixShift(void) {
    
    writePinHigh(MATRIX_PIN_REG_SHIFT);
    writePinLow(MATRIX_PIN_REG_SHIFT);
    
    writePinHigh(MATRIX_PIN_REG_STORE);
    writePinLow(MATRIX_PIN_REG_STORE);
}



/* read rows states and return bits in right order */
uint8_t keyMatrixGetColRowValues(void) {

    uint8_t res = 0;

    for (int r = 0; r < MATRIX_ROWS; r++) {
        res |= ((readPin(keyMatrixRowPins[r]) & 1) ? 0 : 1) << ((MATRIX_ROWS - 1) - r);
    }

    return res;
}


/*==========================================================================
============================================================================
==========================================================================*/



void matrix_init_custom(void) {  

    memset(oldMatrix, 0, matrixArraySize);
    keyMatrixInit();

}



bool matrix_scan_custom(matrix_row_t current_matrix[]) {

    bool changed = false;
    memset(current_matrix, 0, matrixArraySize);

    keyMatrixReset();
    
    for (int c = 0; c < MATRIX_COLS; c++) {

        uint8_t rowValues = keyMatrixGetColRowValues();

        for (int r = 0; r < MATRIX_ROWS; r++) {
            current_matrix[r] |= ((rowValues & (1 << r)) ? 1 : 0) << c;
        }
    
        keyMatrixShift();
    }

    changed = memcmp(current_matrix, oldMatrix, matrixArraySize) != 0;
    memcpy(oldMatrix, current_matrix, matrixArraySize);

    return changed;

}



/*==========================================================================
============================================================================
==========================================================================*/
