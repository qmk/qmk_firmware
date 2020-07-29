#include "matrix.h"

#include "quantum.h"

void matrix_init_custom(void) {
    /* Column(sense) */
    palSetPadMode(GPIOD, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 7, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 2, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 3, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 7, PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    palSetPadMode(GPIOB, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 18, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 19, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 8, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 9, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 4, PAL_MODE_OUTPUT_PUSHPULL);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
            case 0:
                palSetPad(GPIOB, 2);
                break;
            case 1:
                palSetPad(GPIOB, 3);
                break;
            case 2:
                palSetPad(GPIOB, 18);
                break;
            case 3:
                palSetPad(GPIOB, 19);
                break;
            case 4:
                palSetPad(GPIOC, 0);
                break;
            case 5:
                palSetPad(GPIOC, 8);
                break;
            case 6:
                palSetPad(GPIOC, 9);
                break;
            case 7:
                palSetPad(GPIOD, 0);
                break;
            case 8:
                palSetPad(GPIOD, 1);
                break;
            case 9:
                palSetPad(GPIOD, 4);
                break;
        }

        matrix_io_delay();

        // read col data: { PTD5, PTD6, PTD7, PTC1, PTC2, PTC3, PTC4, PTC5, PTC6, PTC7 }
        data = ((palReadPort(GPIOC) & 0xFEUL) << 2) |
               ((palReadPort(GPIOD) & 0xE0UL) >> 5);

        // un-strobe row
        switch (row) {
            case 0:
                palClearPad(GPIOB, 2);
                break;
            case 1:
                palClearPad(GPIOB, 3);
                break;
            case 2:
                palClearPad(GPIOB, 18);
                break;
            case 3:
                palClearPad(GPIOB, 19);
                break;
            case 4:
                palClearPad(GPIOC, 0);
                break;
            case 5:
                palClearPad(GPIOC, 8);
                break;
            case 6:
                palClearPad(GPIOC, 9);
                break;
            case 7:
                palClearPad(GPIOD, 0);
                break;
            case 8:
                palClearPad(GPIOD, 1);
                break;
            case 9:
                palClearPad(GPIOD, 4);
                break;
        }

        changed |= current_matrix[row] != data;
    }

    return changed;
}
