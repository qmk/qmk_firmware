/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include <avr/io.h>
#include <util/delay.h>
#include <i2c_master.h>
#include "matrix.h"
#include "split75.h"
#include "pincontrol.h"

#include <string.h>
#include <stdio.h>

#ifndef DEBOUNCE
#   define DEBOUNCE    5
#endif

#define RIGHT_HALF

extern uint8_t led0, led1, led2;

#if defined(DEBOUNCE)
static uint8_t debouncing = DEBOUNCE;
#endif

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

void matrix_set_row_status(uint8_t row);
uint8_t bit_reverse(uint8_t x);

static void set_led_val(uint8_t val) {
    led0 = val & 0x1;
    led1 = (val & 0x2) >> 1;
    led2 = (val & 0x4) >> 2;
}

static uint16_t globalval = 0;
static void inc_led_val(void) {
    globalval++;
    set_led_val(globalval / 8192);
}

#if defined(RIGHT_HALF)
#define I2C_TIMEOUT     10
#define MCP23018_TWI_ADDRESS 0b0100000
#define TW_READ        1
#define TW_WRITE    0
#define TWI_ADDR_WRITE ( (MCP23018_TWI_ADDRESS<<1) | TW_WRITE )
#define TWI_ADDR_READ  ( (MCP23018_TWI_ADDRESS<<1) | TW_READ  )
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15
#define MCP_ROWS_START    8

static uint8_t mcp23018_init(void) {
    uint8_t ret;
    uint8_t data[3];
    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    data[0] = IODIRA;
    data[1] = 0b00000000;  // IODIRA
    data[2] = (0b11111111);  // IODIRB

    ret = i2c_transmit(TWI_ADDR_WRITE, (uint8_t *)data, 3, I2C_TIMEOUT);
    if (ret) goto out;  // make sure we got an ACK

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    data[0] = GPPUA;
    data[1] = 0b00000000;  // IODIRA
    data[2] = (0b11111111);  // IODIRB

    ret = i2c_transmit(TWI_ADDR_WRITE, (uint8_t *)data, 3, I2C_TIMEOUT);
    if (ret) goto out;  // make sure we got an ACK

    // set logical value (doesn't matter on inputs)
    // - unused  : hi-Z : 1
    // - input   : hi-Z : 1
    // - driving : hi-Z : 1
    data[0] = OLATA;
    data[1] = 0b11111111;  // IODIRA
    data[2] = (0b11111111);  // IODIRB

    ret = i2c_transmit(TWI_ADDR_WRITE, (uint8_t *)data, 3, I2C_TIMEOUT);

out:
    return ret;
}
#endif

void matrix_init(void) {
    // Init indicator LEDs
    indicator_init();

    // Set rows as output starting high
    DDRB = 0xFF;
    PORTB = 0xFF;

    // Set columns as inputs with pull-up enabled
    DDRA = 0x00;
    PORTA = 0xFF;

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = 0x00;
        matrix_debouncing[row] = 0x00;
    }

    // Initialize i2c communication
    i2c_init();

#if defined(RIGHT_HALF)
    // Initialize the chip on the other half
    mcp23018_init();
#endif

    matrix_init_quantum();
    (void)inc_led_val;
    (void)set_led_val;
}

uint8_t matrix_scan(void) {
#if defined(RIGHT_HALF)
    uint8_t data;
#endif

    matrix_row_t cols;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        cols = 0;
	    // Select the row to scan
        matrix_set_row_status(row);

        _delay_us(5);
	    //Set the local row

#if defined(RIGHT_HALF)
		// Initialize to 0x7F in case I2C read fails, 
		// as 0x75 would be no keys pressed
		data = 0x7F;
		// Receive the columns from right half
		i2c_receive(TWI_ADDR_WRITE, &data, 1, I2C_TIMEOUT);
#endif

        cols |= ((~(PINA | 0x80)) & 0x7F);
#if defined(RIGHT_HALF)
		cols |= (((~(data | 0x80)) & 0x7F) << 7);
#endif

#if defined(DEBOUNCE)
        if (matrix_debouncing[row] != cols) {
            matrix_debouncing[row] = cols;
            debouncing = DEBOUNCE;
        }
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
#else
        matrix[row] = cols;
    }
#endif

    matrix_scan_quantum();

    return 1;
}

void matrix_set_row_status(uint8_t row) {
#if defined(RIGHT_HALF)
    uint8_t txdata[3];

    //Set the remote row on port A
    txdata[0] = (GPIOA);
    txdata[1] = ( 0xFF & ~(1<<row) );
    i2c_transmit(TWI_ADDR_WRITE, (uint8_t *)txdata, 2, I2C_TIMEOUT);
#endif

    //Set the local row on port B
    DDRB = (1 << row);
    PORTB = ~(1 << row);
}

uint8_t bit_reverse(uint8_t x) {
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
    return x;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
}
