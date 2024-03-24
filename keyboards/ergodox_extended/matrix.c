#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "ergodox_extended.h"

/*
 * This constant define not debouncing time in msecs, assuming eager_pr.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * However, some switches seem to have higher debouncing requirements, or
 * something else might be wrong. (Also, the scan speed has improved since
 * that comment was written.)
 */

/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values

static matrix_row_t read_cols(uint8_t row);
static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;

keyboard_config_t keyboard_config;

bool         i2c_initialized = 0;

i2c_status_t mcp23018_status = 0x20;


void matrix_init_custom(void) {
    // initialize row and col

    mcp23018_status = init_mcp23018();

    unselect_rows();
    init_cols();
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
    matrix_row_t temp = 0x3F & read_cols(index);
    if (raw_matrix[index] != temp) {
        raw_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23018_status) {  // if there was an error
        if (++mcp23018_reset_loop == 0) {
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
            }
        }
    }

    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
        // select rows from left and right hands
        uint8_t left_index  = i;
        uint8_t right_index = i + MATRIX_ROWS_PER_SIDE;
        select_row(left_index);
        select_row(right_index);

        changed |= store_raw_matrix_row(left_index);
        changed |= store_raw_matrix_row(right_index);

        unselect_rows();
    }

    return changed;
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    // Rows:    GPA{6..0}
    // Columns: GPB{0..6}
    // Init process: Set up connection at 0b0100000<<1
    // Setup:
    // data[] has 2 2 byte values, to set up {GPIOA, GPIOB} pin directions
    // Write to IODIR to set direction
    // Then write the same 16 bits to GPPUX to set pullup
#if DIODE_DIRECTION == COL2ROW
    uint8_t data[] = {0b00000000, 0b01111111};
    mcp23018_status = i2c_writeReg(I2C_ADDR, IODIRA, data, 2, ERGODOX_EXTENDED_I2C_TIMEOUT);
    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_writeReg(I2C_ADDR, GPPUA, data, 2, ERGODOX_EXTENDED_I2C_TIMEOUT);
    }
#else
    /* uint8_t data[] = {0b01111111, 0b00000000}; */
    uint8_t data[] = {0b00000000, 0b01111111};
    mcp23018_status = i2c_writeReg(I2C_ADDR, IODIRA, data, 2, ERGODOX_EXTENDED_I2C_TIMEOUT);
    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_writeReg(I2C_ADDR, GPPUA, data, 2, ERGODOX_EXTENDED_I2C_TIMEOUT);
    }
#endif

    return mcp23018_status;
}

/* Column pin configuration
 *
 * Teensy
 * col: 0   1   2   3   4   5   6
 * pin: F0  F1  F4  F5  F6  F7  D7
 *
 * MCP23018
 * col: 0   1   2   3   4   5   6
 * pin: B6  B5  B4  B3  B2  B1  B0
 */
static void init_cols(void) {
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    // init on teensy
    setPinInputHigh(F0);
    setPinInputHigh(F1);
    setPinInputHigh(F4);
    setPinInputHigh(F5);
    setPinInputHigh(F6);
    setPinInputHigh(F7);
    setPinInputHigh(D7);
}

static matrix_row_t read_cols(uint8_t row) {
    if (row < 7) {
        if (mcp23018_status) {  // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            // reading GPIO{A,B} (column port) since in mcp23018's sequential mode
            // it is addressed directly after writing to GPIO{B,A} in select_row()
            mcp23018_status = i2c_receive(I2C_ADDR, &data, 1, ERGODOX_EXTENDED_I2C_TIMEOUT);
            return ~data;
        }
    } else {
        /* read from atmega32u4
         * bitmask for the F pins is 0b11110011
         * bitmask for the D pin is  0b10000000
         * So I want 7 bits. 0b01111111.
         * Shift PINF 0xF0 2 bits right.
         * Shift PIND 0x80 1 bit right.
         * End up with 0b01111111.
         * 7 bits. 7 rows.
         */

        return ~(((PIND & 0x80) >> 1) | (PINF & 0x03) | ((PINF & 0xF0) >> 2));
    }
}

/* Row pin configuration
 *
 * Teensy
 * row: 7   8   9   10  11  12  13
 * pin: B0  B1  B2  B3  D2  D3  C6
 *
 * MCP23018
 * row: 0   1   2   3   4   5   6
 * pin: A0  A1  A2  A3  A4  A5  A6
 */
static void unselect_rows(void) {
    // no need to unselect on mcp23018, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    // unselect on teensy
    setPinInput(B0);
    setPinInput(B1);
    setPinInput(B2);
    setPinInput(B3);
    setPinInput(D2);
    setPinInput(D3);
    setPinInput(C6);
}

static void select_row(uint8_t row) {
    if (row < 7) {
        // select on mcp23018
        if (!mcp23018_status) {
            // set active row low  : 0
            // set other rows hi-Z : 1
            uint8_t data;
            data = 0xFF & ~(1 << row);
#if (DIODE_DIRECTION == COL2ROW)
            mcp23018_status = i2c_writeReg(I2C_ADDR, GPIOA, &data, 1, ERGODOX_EXTENDED_I2C_TIMEOUT);
#else
            mcp23018_status = i2c_writeReg(I2C_ADDR, GPIOA, &data, 1, ERGODOX_EXTENDED_I2C_TIMEOUT);
#endif
        }
    } else {
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 7:
                setPinOutput(B0);
                writePinLow(B0);
                break;
            case 8:
                setPinOutput(B1);
                writePinLow(B1);
                break;
            case 9:
                setPinOutput(B2);
                writePinLow(B2);
                break;
            case 10:
                setPinOutput(B3);
                writePinLow(B3);
                break;
            case 11:
                setPinOutput(D2);
                writePinLow(D2);
                break;
            case 12:
                setPinOutput(D3);
                writePinLow(D3);
                break;
            case 13:
                setPinOutput(C6);
                writePinLow(C6);
                break;
        }
    }
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    mcp23018_status = init_mcp23018();

    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }

}

void matrix_init_kb(void) {
    // (tied to Vcc for hardware convenience)
    DDRB &= ~(1 << 4);   // set B(4) as input
    PORTB &= ~(1 << 4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, E6
    // set as input with internal pull-up enabled
    DDRC &= ~(1 << 7);
    DDRD &= ~(1 << 5 | 1 << 4);
    DDRE &= ~(1 << 6);
    PORTC |= (1 << 7);
    PORTD |= (1 << 5 | 1 << 4);
    PORTE |= (1 << 6);

    keyboard_config.raw = eeconfig_read_kb();
    matrix_init_user();
}

// clang-format on

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}
