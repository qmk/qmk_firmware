/* Copyright 2022 Johannes Schneider (@JohSchneider) */
// SPDX-License-Identifier: GPL-2.0-or-later

/*
ported from old 2017 project code, while adopting some portions of
zvecr's mcp23018 based keyboards/viktus/sp111/matrix.c
*/

#include "quantum.h"
#include "debounce.h"
#include "matrix.h"
#include "mcp23018.h"

#include "yamsek.h"

#include <debug.h>

// Optimize scanning code for speed as a slight mitigation for the port expander
#pragma GCC push_options
#pragma GCC optimize("-O3")

// RP2040 with yamsek MCP23017-breakout
//#define I2C_ADDR 0x32
// arduino leanardo breadboard
//#define I2C_ADDR 0b0100000
#define I2C_ADDR 0x20


//#if (MATRIX_ROWS <= 8)
typedef uint8_t matrix_col_t;
//#elif (MATRIX_ROWS <= 16)
//typedef uint16_t matrix_col_t;
//#endif

/* matrix state(1:on, 0:off) */
static matrix_col_t matrix[MATRIX_COLS];
static matrix_col_t raw_matrix[MATRIX_COLS];
/* matrix is column-major, since the wiring looks like this:

   rows

   R0 ─────│─┬─────│─┬──── ...
           │ └o o┐ │ └o o┐           -o o- = switch
           ├───|<┘ ├───|<┘
           │       │                  -|<- = diode
   R1 ─────│─┬─────│─┬──── ...
           │ └o o┐ │ └o o┐
           ├───|<┘ ├───|<┘
           │       │
   .       .       .
   .       .       .
           │       │
           C0      C1      ... columns

  hence the code "selects" column pins by pulling them low,
  and continues to read all row-pins into a 'matrix_col_t'
*/

/* Column pin configuration
 *
 * Main-MCU
 * col: 0   1   2   3   4   5
 * pin: PB5 PB4 PE6 PD7 PC6 PD4 (atmega32u4)
 *
 * MCP23017
 * col: 0   1   2   3   4   5
 * pin: A0  A1  A2  A3  A4  A5
 */
/* Row pin configuration
 *
 * Main-MCU
 * row: 0   1   2   3
 * pin: PB6 PB7 PD6 PD2 (atmega32u4)
 *
 * MCP23017
 * row: 4   5   6   7
 * pin: B0  B1  B2  B3
 */

// Main-MCU side of the keyboard ______________________________________________

static void select_col_MCU(uint8_t x) {
    setPinOutput(col_pins_MCU[x]);
    writePinLow(col_pins_MCU[x]);
}

static void unselect_col_MCU(uint8_t x) {
    setPinInputHigh(col_pins_MCU[x]);
}

static void init_pins_MCU(void) {

    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        unselect_col_MCU(x);
    }

    for (uint8_t x = 0; x < MATRIX_ROWS/2; x++) {
        setPinInputHigh(row_pins_MCU[x]);
    }
}

/**
   while one column is selected (output, set low -all other set high)
   read the whole PortB, to see which pins are pulled low
   (remember: internal pullup are ON, so all switches open ==  read all 1 on PortB)
*/
static matrix_col_t read_rows_on_col_MCU(uint8_t index) {
    matrix_col_t current_value = 0;

    // Select col and wait the value to stabilize
    select_col_MCU(index);
    wait_us(5);

    for (uint8_t row_index = 0; row_index < MATRIX_ROWS/2; row_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(row_pins_MCU[row_index]);

        // Populate the matrix row with the state of the col pin
        current_value |= pin_state ? 0 : (1 << row_index);
    }

    // Unselect row
    unselect_col_MCU(index);

    return (current_value & 0x0F);
}

// IO-Expander ________________________________________________________________
/** MCP23017
    Note: was at hand, and is command-compatible to mcp23018.{ch}

Left-Hand wiring:
                ┌─────┐
    Row 4   B0 ─┤1    ├─ A7
     "  5   B1 ─┤     ├─ A6
     "  6   B2 ─┤     ├─ A5 Column 5
     "  7   B3 ─┤     ├─ A4    "   4
            B4 ─┤     ├─ A3    "   3
            B5 ─┤     ├─ A2    "   2
            B6 ─┤     ├─ A1    "   1
            B7 ─┤     ├─ A0    "   0
           Vdd ─┤     ├─
       Gnd/Vss ─┤     ├─
               ─┤     ├─!Reset──Vdd
           SCL ─┤     ├─Addr2─┐
           SDA ─┤     ├─Addr1─┤
               ─┤     ├─Addr0─┤
                └─────┘       └─Vss/Gnd
*/

static uint16_t mcp23018_reset_loop = 0;
static uint8_t mcp23018_errors = 0;

static void init_pins_MCP23018(void) {
    // set pin direction
    // - output : 0
    // - input  : 1
    // and pull-up
    // - no-pullup : 0
    // - enable pullup : 1
    mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, 0b00000000);
    mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, 0b11111111);

    if (!mcp23018_errors)
        dprint("MCP23018 setup OK\n");
}

static void select_col_MCP23018(uint8_t x) {
    mcp23018_errors += !mcp23018_set_output(I2C_ADDR, mcp23018_PORTA, ~(1<<x));
}

static uint8_t read_rows_MCP23018(void) {
    uint8_t tmp = 0xFF;
    mcp23018_errors += !mcp23018_readPins(I2C_ADDR, mcp23018_PORTB, &tmp);
    return (~tmp & 0x0F);
}

static matrix_col_t read_rows_on_col_MCP23018(uint8_t index) {
    select_col_MCP23018(index);
    return read_rows_MCP23018() << MATRIX_ROWS/2;
}

// custom_matrix = yes (full) __________________________________________________

/**
 * matrix_get_row is used by tmk_core for further keycode processing.
 * since the matrix is an array of columns, we have to reassemble the single rowValues
 */
matrix_row_t matrix_get_row(uint8_t row_index) {
    uint8_t row_values = 0x00;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++){
        if ( matrix[col_index] & (1<<row_index))
            row_values |= 1 << col_index;
    }
    return row_values;
}

void matrix_print(void) {
    print("\nr/c 012345__\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

void matrix_init(void) {

    mcp23018_init(I2C_ADDR);
    init_pins_MCU();
    init_pins_MCP23018();

    // Unless hardware debouncing - Init the configured debounce routine
    debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
    matrix_init_kb();

#ifdef RGBLIGHT_ENABLE
    if (mcp23018_errors) {
        rgblight_sethsv_at(0, 255,20 ,0); // red
    } else  {
        rgblight_sethsv_at(85, 255,20 ,0); // green
    }
#endif
}

uint8_t matrix_scan(void) {
    bool changed = false;

    if (mcp23018_errors) {
        if (mcp23018_reset_loop  == 1) {
          dprintf("reset_loop startet, mcp23018_erros = %d ...\n", mcp23018_errors);
        }
        if (++mcp23018_reset_loop > 0x4FF) {
            dprint("trying to reset mcp23018\n");
            mcp23018_reset_loop = 0;
            mcp23018_errors     = 0;
            init_pins_MCP23018();
        }
    }

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_col_t previous = raw_matrix[current_col];
        raw_matrix[current_col] = 0;
        raw_matrix[current_col] |= read_rows_on_col_MCU(current_col);
        raw_matrix[current_col] |= read_rows_on_col_MCP23018(current_col);
        changed |= previous != raw_matrix[current_col];
    }

    // Unless hardware debouncing - use the configured debounce routine
    debounce(raw_matrix, matrix, MATRIX_COLS, changed);

    // This *must* be called for correct keyboard behavior
    matrix_scan_kb();

    return changed;
}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}


/* whether a switch is on/pressed */
inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[col] & ((matrix_col_t)1<<row));
}

#pragma GCC pop_options
