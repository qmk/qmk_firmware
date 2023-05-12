#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static void select_row(uint8_t row) 
{
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }

static void unselect_rows(void) 
{
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static void init_pins(void) 
{
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
    setPinInputHigh(PIN_JU);
    setPinInputHigh(PIN_JD);
    setPinInputHigh(PIN_JL);
    setPinInputHigh(PIN_JR);
    setPinInputHigh(PIN_JC);
    setPinInputHigh(PIN_TC);
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) 
{

    if(current_row > 2)
        return false;

    matrix_row_t last_row_value = current_matrix[current_row];

    current_matrix[current_row] = 0;

    select_row(current_row);
    wait_us(30);

    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) 
    {
        uint8_t pin_state = readPin(col_pins[col_index]);
        current_matrix[current_row] |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

static bool read_encoder_switches(matrix_row_t current_matrix[]) 
{   
    
    matrix_row_t last_fourth_row = current_matrix[3];
    matrix_row_t last_fifth_row = current_matrix[4];
    
    current_matrix[3] = 0;
    current_matrix[4] = 0;

    current_matrix[4] |= !readPin(PIN_TC) ? (1 << 1) : 0;

    if (!readPin(PIN_JC))
    {
        if (!readPin(PIN_JU))
        {
            current_matrix[3] |= (1 << 0);
        }
        else if (!readPin(PIN_JD))
        {
            current_matrix[3] |= (1 << 1);
        }
        else if (!readPin(PIN_JL))
        {
            current_matrix[3] |= (1 << 2);
        }
        else if (!readPin(PIN_JR))
        {
            current_matrix[3] |= (1 << 3);
        }
        else
        {
            current_matrix[4] |= (1 << 0);
        }
    }


    return last_fourth_row != current_matrix[3] || last_fifth_row != current_matrix[4];

}






void matrix_init_custom(void) 
{
    init_pins();
}

bool matrix_scan_custom(void) 
{
    bool changed = false;

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) 
    {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }

    changed |= read_encoder_switches(raw_matrix);

    return changed;
}