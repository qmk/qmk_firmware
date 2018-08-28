/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "split_util.h"
#include "pro_micro.h"
#include "config.h"
#include "timer.h"
#ifdef DEBUG_MATRIX_SCAN_RATE
    #include "matrix_scanrate.h"
#endif



#ifdef USE_I2C
#  include "i2c.h"
#else // USE_SERIAL
#  error "only i2c supported"
#endif

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif


#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#else
#    error "Currently only supports 8 COLS"
#endif

#define ERROR_DISCONNECT_COUNT 5

#define ROWS_PER_HAND (MATRIX_ROWS/2)

static uint8_t error_count = 0;

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static matrix_row_t* debouncing_matrix_hand_offsetted; //pointer to matrix_debouncing for our hand
static matrix_row_t* matrix_hand_offsetted; // pointer to matrix for our hand

//Debouncing counters
typedef uint8_t debounce_counter_t;
#define DEBOUNCE_COUNTER_MODULO 250
#define DEBOUNCE_COUNTER_INACTIVE 251
static debounce_counter_t debounce_counters[MATRIX_ROWS * MATRIX_COLS];
static debounce_counter_t *debounce_counters_hand_offsetted;


#if (DIODE_DIRECTION == ROW2COL)
    error "Only Col2Row supported";
#endif
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);
static void unselect_row(uint8_t row);
static matrix_row_t optimized_col_reader(void);

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

__attribute__ ((weak))
void matrix_slave_scan_user(void) {
}

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
#ifdef DISABLE_JTAG
  // JTAG disable for PORT F. write JTD bit twice within four cycles.
  MCUCR |= (1<<JTD);
  MCUCR |= (1<<JTD);
#endif

    debug_enable = true;
    debug_matrix = false;
    debug_mouse = false;
    // initialize row and col
    unselect_rows();
    init_cols();

    TX_RX_LED_INIT;

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
    int my_hand_offset = isLeftHand ? 0 : (ROWS_PER_HAND);
    debouncing_matrix_hand_offsetted = matrix_debouncing + my_hand_offset;
    matrix_hand_offsetted = matrix + my_hand_offset;
    debounce_counters_hand_offsetted = debounce_counters + my_hand_offset;

    for (uint8_t i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
        debounce_counters[i] = DEBOUNCE_COUNTER_INACTIVE;
    }
    
    matrix_init_quantum();

}

//#define TIMER_DIFF(a, b, max)   ((a) >= (b) ?  (a) - (b) : (max) - (b) + (a))
void update_debounce_counters(uint8_t current_time)
{
    debounce_counter_t *debounce_pointer = debounce_counters_hand_offsetted;
    for (uint8_t row = 0; row < ROWS_PER_HAND; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            if (*debounce_pointer != DEBOUNCE_COUNTER_INACTIVE)
            {
                if (TIMER_DIFF(current_time, *debounce_pointer, DEBOUNCE_COUNTER_MODULO) >=
                    DEBOUNCING_DELAY) {
                        *debounce_pointer = DEBOUNCE_COUNTER_INACTIVE;
                    }
            }
            debounce_pointer++;
        }
    }
}

void transfer_matrix_values(uint8_t current_time)
{
    //upload from debounce_matrix to final matrix;
    debounce_counter_t *debounce_pointer = debounce_counters_hand_offsetted;
    for (uint8_t row = 0; row < ROWS_PER_HAND; row++)
    {
        matrix_row_t row_value = matrix_hand_offsetted[row];
        matrix_row_t debounce_value = debouncing_matrix_hand_offsetted[row];

        for (uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            bool final_value = debounce_value & (1 << col);
            bool current_value = row_value & (1 << col);
            if (*debounce_pointer == DEBOUNCE_COUNTER_INACTIVE
                && (current_value != final_value))
            {
                *debounce_pointer = current_time;
                row_value ^= (1 << col);
            }
            debounce_pointer++;
        }
        matrix_hand_offsetted[row] = row_value;
    }
}

uint8_t _matrix_scan(void)
{
    uint8_t current_time = timer_read() % DEBOUNCE_COUNTER_MODULO;
    
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
        select_row(current_row);
        asm volatile ("nop"); asm volatile("nop");

        debouncing_matrix_hand_offsetted[current_row] = optimized_col_reader();
        // Unselect row
        unselect_row(current_row);
    }

    update_debounce_counters(current_time);
    transfer_matrix_values(current_time);

    return 1;
}


// Get rows from other half over i2c
int i2c_transaction(void) {
    int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;

    int err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_WRITE);
    if (err) goto i2c_error;

    // start of matrix stored at 0x00
    err = i2c_master_write(I2C_KEYMAP_START);
    if (err) goto i2c_error;

    // Start read
    err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_READ);
    if (err) goto i2c_error;

    if (!err) {
        int i;
        for (i = 0; i < ROWS_PER_HAND-1; ++i) {
            matrix[slaveOffset+i] = i2c_master_read(I2C_ACK);
        }
        matrix[slaveOffset+i] = i2c_master_read(I2C_NACK);
        i2c_master_stop();
    } else {
i2c_error: // the cable is disconnceted, or something else went wrong
        i2c_reset_state();
        return err;
    }

    return 0;
}

uint8_t matrix_scan(void)
{    
#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_check_scan_rate();
    matrix_time_between_scans();
#endif        
    uint8_t ret = _matrix_scan();
   
    if( i2c_transaction() ) {
        // turn on the indicator led when halves are disconnected
        TXLED1;

        error_count++;

        if (error_count > ERROR_DISCONNECT_COUNT) {
            // reset other half if disconnected
            int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;
            for (int i = 0; i < ROWS_PER_HAND; ++i) {
                matrix[slaveOffset+i] = 0;
            }
        }
    } else {
        // turn off the indicator led on no error
        TXLED0;
        error_count = 0;
    }
    matrix_scan_quantum();
    return ret;
}

void matrix_slave_scan(void) {
    _matrix_scan();

    int offset = (isLeftHand) ? 0 : ROWS_PER_HAND;

    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        i2c_slave_buffer[I2C_KEYMAP_START+i] = matrix[offset+i];
    }

    matrix_slave_scan_user();
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}


inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

static void init_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        uint8_t pin = col_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

inline 
static matrix_row_t optimized_col_reader(void) {
    //MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }
    return (PINB & (1 << 6) ? 0 : (ROW_SHIFTER << 0)) |
          (PINB & (1 << 2) ? 0 : (ROW_SHIFTER << 1)) |
          (PINB & (1 << 3) ? 0 : (ROW_SHIFTER << 2)) |
          (PINB & (1 << 1) ? 0 : (ROW_SHIFTER << 3)) |
          (PINF & (1 << 7) ? 0 : (ROW_SHIFTER << 4)) |
          (PINF & (1 << 6) ? 0 : (ROW_SHIFTER << 5)) |
          (PINF & (1 << 5) ? 0 : (ROW_SHIFTER << 6)) |
          (PINF & (1 << 4) ? 0 : (ROW_SHIFTER << 7));
}


static void select_row(uint8_t row)
{
    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF); // OUT
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
}

static void unselect_row(uint8_t row)
{
    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
}

static void unselect_rows(void)
{
    for(uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        uint8_t pin = row_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

