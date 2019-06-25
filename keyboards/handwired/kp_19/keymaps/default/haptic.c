#include "matrix.h"

int vib_duration = 55;

void haptic_task (void) {
    static int vib_clear_timer = 0;
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    if (vib_clear_timer) {
        if ((int)(vib_duration - timer_elapsed(vib_clear_timer)) < 0) {
            backlight_level(0);
            vib_clear_timer = 0;
        }
    }

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if (matrix_change & ((matrix_row_t)1<<c)) {
                    if (matrix_row & ((matrix_row_t)1<<c)) {
                        backlight_level(15);
                        vib_clear_timer = timer_read();
                    }
                    matrix_prev[r] ^= ((matrix_row_t)1<<c);
                }
            }
        }
    }
}

void haptic_init (void) {
    backlight_level(0);
}
