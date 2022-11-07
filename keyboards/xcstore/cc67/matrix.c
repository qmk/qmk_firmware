/* Copyright 2022 XCStore
 * Copyright 2022 Yulei (Astro) <https://github.com/yulei>
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <hal.h>
#include "quantum.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"

/**
 *
 * Row pins are input with internal pull-down.
 * Column pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

// user-defined overridable functions

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

// helper functions
void matrix_init(void)
{
    //debug_enable = true;
    palSetLineMode(LINE_PB12,         PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PB13,         PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PB14,         PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PB15,         PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PA8,          PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_VBUS_FS,      PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OTG_FS_ID,    PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PC13,         PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OSC32_IN,     PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OSC32_OUT,    PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_BUTTON,       PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PA1,          PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PA2,          PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PA3,          PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_CS43L22_LRCK, PAL_MODE_OUTPUT_PUSHPULL);

    palSetLineMode(LINE_PA15, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_SWO,  PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_PB4,  PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_PB5,  PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_PB7,  PAL_MODE_INPUT_PULLDOWN);

    palClearLine(LINE_PB12);
    palClearLine(LINE_PB13);
    palClearLine(LINE_PB14);
    palClearLine(LINE_PB15);
    palClearLine(LINE_PA8);
    palClearLine(LINE_VBUS_FS);
    palClearLine(LINE_OTG_FS_ID);
    palClearLine(LINE_PC13);
    palClearLine(LINE_OSC32_IN);
    palClearLine(LINE_OSC32_OUT);
    palClearLine(LINE_BUTTON);
    palClearLine(LINE_PA1);
    palClearLine(LINE_PA2);
    palClearLine(LINE_PA3);
    palClearLine(LINE_CS43L22_LRCK);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
        switch (col) {
            case 0:  palSetLine(LINE_PB12);         break;
            case 1:  palSetLine(LINE_PB13);         break;
            case 2:  palSetLine(LINE_PB14);         break;
            case 3:  palSetLine(LINE_PB15);         break;
            case 4:  palSetLine(LINE_PA8);          break;
            case 5:  palSetLine(LINE_VBUS_FS);      break;
            case 6:  palSetLine(LINE_OTG_FS_ID);    break;
            case 7:  palSetLine(LINE_PC13);         break;
            case 8:  palSetLine(LINE_OSC32_IN);     break;
            case 9:  palSetLine(LINE_OSC32_OUT);    break;
            case 10: palSetLine(LINE_BUTTON);       break;
            case 11: palSetLine(LINE_PA1);          break;
            case 12: palSetLine(LINE_PA2);          break;
            case 13: palSetLine(LINE_PA3);          break;
            case 14: palSetLine(LINE_CS43L22_LRCK); break;
        }

        // need wait to settle pin state
        wait_us(20);

        data = (
            (palReadLine(LINE_PA15) << 0 ) |
            (palReadLine(LINE_SWO)  << 1 ) |
            (palReadLine(LINE_PB4)  << 2 ) |
            (palReadLine(LINE_PB5)  << 3 ) |
            (palReadLine(LINE_PB7)  << 4 )
        );

        switch (col) {
            case 0:  palClearLine(LINE_PB12);         break;
            case 1:  palClearLine(LINE_PB13);         break;
            case 2:  palClearLine(LINE_PB14);         break;
            case 3:  palClearLine(LINE_PB15);         break;
            case 4:  palClearLine(LINE_PA8);          break;
            case 5:  palClearLine(LINE_VBUS_FS);      break;
            case 6:  palClearLine(LINE_OTG_FS_ID);    break;
            case 7:  palClearLine(LINE_PC13);         break;
            case 8:  palClearLine(LINE_OSC32_IN);     break;
            case 9:  palClearLine(LINE_OSC32_OUT);    break;
            case 10: palClearLine(LINE_BUTTON);       break;
            case 11: palClearLine(LINE_PA1);          break;
            case 12: palClearLine(LINE_PA2);          break;
            case 13: palClearLine(LINE_PA3);          break;
            case 14: palClearLine(LINE_CS43L22_LRCK); break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[row] |= ((matrix_debouncing[col] & (1 << row) ? 1 : 0) << col);
            }
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void)
{
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
