/*
Copyright 2018 Massdrop Inc.

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

#include "ctrl.h"

#include <string.h>

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 1
#endif

uint8_t row_ports[] = { MATRIX_ROW_PORTS };
uint8_t row_pins[] = { MATRIX_ROW_PINS };
uint8_t col_ports[] = { MATRIX_COL_PORTS };
uint8_t col_pins[] = { MATRIX_COL_PINS };
uint32_t row_masks[2]; //NOTE: If more than PA PB used in the future, adjust code to accomodate

__attribute__((weak)) void matrix_io_delay(void) { wait_us(MATRIX_IO_DELAY); }

void matrix_init_custom(void)
{
    row_masks[PA] = 0;
    row_masks[PB] = 0;

    uint8_t row;
    for (row = 0; row < MATRIX_ROWS; row++)
    {
        PORT->Group[row_ports[row]].DIRCLR.reg = 1 << row_pins[row]; //Input
        PORT->Group[row_ports[row]].OUTCLR.reg = 1 << row_pins[row]; //Low
        PORT->Group[row_ports[row]].PINCFG[row_pins[row]].bit.INEN = 1; //Input Enable,
        PORT->Group[row_ports[row]].PINCFG[row_pins[row]].bit.PULLEN = 1; //Pull Enable
        row_masks[row_ports[row]] |= 1 << row_pins[row]; //Add pin to proper row mask
    }

    uint8_t col;
    for (col = 0; col < MATRIX_COLS; col++)
    {
        PORT->Group[col_ports[col]].DIRSET.reg = 1 << col_pins[col]; //Output
        PORT->Group[col_ports[col]].OUTCLR.reg = 1 << col_pins[col]; //Low
    }
}

bool matrix_scan_custom(matrix_row_t mlast[])
{
    uint8_t mchanged;
    uint8_t row;
    uint8_t col;
    uint32_t scans[2]; //PA PB
    matrix_row_t mlatest[MATRIX_ROWS];

    memset(mlatest, 0, MATRIX_ROWS * sizeof(matrix_row_t)); //Zero the result buffer

    for (col = 0; col < MATRIX_COLS; col++)
    {
        PORT->Group[col_ports[col]].OUTSET.reg = 1 << col_pins[col]; //Set col output

        matrix_io_delay(); //Delay for output

        scans[PA] = PORT->Group[PA].IN.reg & row_masks[PA]; //Read PA row pins data
        scans[PB] = PORT->Group[PB].IN.reg & row_masks[PB]; //Read PB row pins data

        PORT->Group[col_ports[col]].OUTCLR.reg = 1 << col_pins[col]; //Clear col output

        for (row = 0; row < MATRIX_ROWS; row++)
        {
            //Move scan bits from scans array into proper row bit locations
            if (scans[row_ports[row]] & (1 << row_pins[row]))
                mlatest[row] |= 1 << col;
        }
    }

    mchanged = 0; //Default to no matrix change since last

    for (row = 0; row < MATRIX_ROWS; row++)
    {
        if (mlast[row] != mlatest[row])
            mchanged = 1;
        mlast[row] = mlatest[row];
    }

    return mchanged;
}
