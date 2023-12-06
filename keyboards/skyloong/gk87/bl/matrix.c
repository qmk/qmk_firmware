// Copyright 2023 NaturaZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
//Matrix read cols set row
//Matrix logic ADAPTS to PTIR

#include "quantum.h"
#include "debounce.h"

#define ALL_KEY_COL_PULL A15
#define ReadDelayTime 120
#define ClockTime 3
#define MATRIX_INPUT_PRESSED_STATE 0

#define HC165_SELECT_PIN A4
#define HC165_PL_PIN A3
#define HC165_CP_PIN A5
#define HC165_MISO_PIN A6

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// user-defined overridable functions
__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);

static inline void select_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    };
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static inline void setPinInput_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInput(pin);
    }
}

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeHigh(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
    }
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        unselect_row(x);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

// matrix code

__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;
    // Select row
    if (!select_row(current_row)) { // select row
        return;                     // skip NO_PIN row
    }
    writePinHigh(HC165_CP_PIN);  //HC165 clock high
    writePinLow(HC165_PL_PIN);//PL pull low
    select_delay(ReadDelayTime);
    writePinHigh(HC165_PL_PIN);  //PL pull high


    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {

        select_delay(ClockTime);  //The clocktime > 2
        uint8_t pin_state = readMatrixPin(HC165_MISO_PIN);
        writePinLow(HC165_CP_PIN);//HC165 clock low
        select_delay(ClockTime);
        writePinHigh(HC165_CP_PIN);  //HC165 clock high

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;

    }

    unselect_row(current_row);
    writePinLow(ALL_KEY_COL_PULL); //close cols
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH
    current_matrix[current_row] = current_row_value;
}

void matrix_init_custom(void) {
    unselect_rows();
    setPinOutput_writeHigh(ALL_KEY_COL_PULL);

    //initialize HC165 Hold "do nothing"
    setPinOutput_writeHigh(HC165_PL_PIN);  //HC165 PL High
    setPinOutput_writeHigh(HC165_SELECT_PIN);  //HC165 CE High
    setPinOutput_writeLow(HC165_CP_PIN);  //HC165 clock low

    // initialize key data input pin
    setPinInput_atomic(HC165_MISO_PIN);

    // initialize matrix state: all keys off
    memset(matrix, 0, sizeof(matrix));
    memset(raw_matrix, 0, sizeof(raw_matrix));

    debounce_init(MATRIX_ROWS);

    matrix_init_kb();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    writePinLow(HC165_SELECT_PIN);   //select HC165
    writePinHigh(ALL_KEY_COL_PULL);  //open cols

    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_read_cols_on_row(curr_matrix, current_row);
        writePinHigh(ALL_KEY_COL_PULL);  //open cols
    }

    matrix_has_changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (matrix_has_changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));
    matrix_has_changed = debounce(raw_matrix, matrix, MATRIX_ROWS, matrix_has_changed);
    matrix_scan_kb();
    return (uint8_t)matrix_has_changed;
}
