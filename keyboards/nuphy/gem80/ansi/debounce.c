// NOTE: this is sym_eager_pk algoritm copy pasted in original state, but adjusted to use DEBOUNCE value from eeprom
// Also if DEBOUNCE header was set to 0 before compilation - debounce won't be enabled at all and also it won't be possible to adjust on the fly

#include "debounce.h"
#include "timer.h"
#include <stdlib.h>
#include "user_kb.h"

#define ROW_SHIFTER ((matrix_row_t)1)

typedef uint8_t debounce_counter_t;

#if DEBOUNCE > 0
static debounce_counter_t *debounce_counters;
static fast_timer_t        last_time;
static bool                counters_need_update;
static bool                matrix_need_update;
static bool                cooked_changed;

#    define DEBOUNCE_ELAPSED 0

static void update_debounce_counters(uint8_t num_rows, uint8_t elapsed_time);
static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows);

// we use num_rows rather than MATRIX_ROWS to support split keyboards
void debounce_init(uint8_t num_rows) {
    debounce_counters = (debounce_counter_t *)malloc(num_rows * MATRIX_COLS * sizeof(debounce_counter_t));
    int i             = 0;
    for (uint8_t r = 0; r < num_rows; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[i++] = DEBOUNCE_ELAPSED;
        }
    }
}

void debounce_free(void) {
    free(debounce_counters);
    debounce_counters = NULL;
}

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    bool updated_last = false;
    cooked_changed    = false;

    if (counters_need_update) {
        fast_timer_t now          = timer_read_fast();
        fast_timer_t elapsed_time = TIMER_DIFF_FAST(now, last_time);

        last_time    = now;
        updated_last = true;
        if (elapsed_time > UINT8_MAX) {
            elapsed_time = UINT8_MAX;
        }

        if (elapsed_time > 0) {
            update_debounce_counters(num_rows, elapsed_time);
        }
    }

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        transfer_matrix_values(raw, cooked, num_rows);
    }

    return cooked_changed;
}

// If the current time is > debounce counter, set the counter to enable input.
static void update_debounce_counters(uint8_t num_rows, uint8_t elapsed_time) {
    counters_need_update                 = false;
    matrix_need_update                   = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (*debounce_pointer != DEBOUNCE_ELAPSED) {
                if (*debounce_pointer <= elapsed_time) {
                    *debounce_pointer  = DEBOUNCE_ELAPSED;
                    matrix_need_update = true;
                } else {
                    *debounce_pointer -= elapsed_time;
                    counters_need_update = true;
                }
            }
            debounce_pointer++;
        }
    }
}

// upload from raw_matrix to final matrix;
static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows) {
    matrix_need_update                   = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta        = raw[row] ^ cooked[row];
        matrix_row_t existing_row = cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);
            if (delta & col_mask) {
                if (*debounce_pointer == DEBOUNCE_ELAPSED) {
                    *debounce_pointer    = user_config.debounce_ms;
                    counters_need_update = true;
                    existing_row ^= col_mask; // flip the bit.
                    cooked_changed = true;
                }
            }
            debounce_pointer++;
        }
        cooked[row] = existing_row;
    }
}

#else
#    include "none.c"
#endif
