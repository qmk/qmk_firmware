/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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

#include "matrix.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"

#ifndef DEBOUNCE
# define DEBOUNCE	5
#endif

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

// Debouncing: store for each key the number of scans until it's eligible to
// change.  When scanning the matrix, ignore any changes in keys that have
// already changed in the last DEBOUNCE scans.
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static void matrix_select_row(uint8_t row);

#ifdef RIGHT_HALF
# include <stdint.h>
# include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md")
# define I2C_ADDR        0b0100000
# define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
# define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
# define IODIRA          0x00            // i/o direction register
# define IODIRB          0x01
# define GPPUA           0x0C            // GPIO pull-up resistor register
# define GPPUB           0x0D
# define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
# define GPIOB           0x13
# define OLATA           0x14            // output latch register
# define OLATB           0x15

# define MCP23018_I2C_TIMEOUT 100

static i2c_status_t mcp23018_status = I2C_STATUS_ERROR;
static uint8_t mcp23018_reset_loop = 0;
static bool i2c_initialized = 0;

static uint8_t init_mcp23018(void)
{
  uint8_t data[3];
  mcp23018_status = I2C_STATUS_ERROR;

  // I2C subsystem
  if (i2c_initialized == 0) {
    i2c_init();  // on pins D(1,0)
    i2c_initialized = true;
    _delay_ms(1000);
  }

  // set pin direction
  // - unused  : input  : 1
  // - input   : input  : 1
  // - driving : output : 
  data[0] = IODIRA;
  data[1] = 0b00000000;
  data[2] = 0b11111111;
  mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, (uint8_t *)data, 3, MCP23018_I2C_TIMEOUT);
  if (mcp23018_status != I2C_STATUS_SUCCESS)
    goto out;

  // set pull-up
  // - unused  : on  : 1
  // - input   : on  : 1
  // - driving : off : 0
  data[0] = GPPUA;
  data[1] = 0b00000000;
  data[2] = 0b11111111;
  mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, (uint8_t *)data, 3, MCP23018_I2C_TIMEOUT);
  if (mcp23018_status != I2C_STATUS_SUCCESS)
    goto out;

  //  set logical value (doesn't matter on inputs)
  // - unused  : hi-Z : 1
  // - input   : hi-Z : 1
  // - driving : hi-Z : 1
  data[0] = OLATA;
  data[1] = 0b11111111;
  data[2] = 0b11111111;
  mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, (uint8_t *)data, 3, MCP23018_I2C_TIMEOUT);

out:
  return (mcp23018_status);
}
#endif

void matrix_init(void)
{
  // all outputs for rows high
  DDRB = 0xFF;
  PORTB = 0xFF;
  // all inputs for columns
  DDRA = 0x00;
  DDRC &= ~(0x111111<<2);
  DDRD &= ~(1<<PIND7);
  // all columns are pulled-up
  PORTA = 0xFF;
  PORTC |= (0b111111<<2);
  PORTD |= (1<<PIND7);

#ifdef RIGHT_HALF
  // initialize row and col
  mcp23018_status = init_mcp23018();
#endif

  // initialize matrix state: all keys off
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    matrix[row] = 0;
    matrix_debouncing[row] = 0;
  }

  matrix_init_quantum();
}

/*static uint8_t bit_reverse(uint8_t x) {
  x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
  x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
  x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
  return x;
}*/

uint8_t matrix_scan(void)
{
#ifdef RIGHT_HALF
  // Then the keyboard
  if (mcp23018_status != I2C_STATUS_SUCCESS) {
    if (++mcp23018_reset_loop == 0) {
      // if (++mcp23018_reset_loop >= 1300) {
      // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
      // this will be approx bit more frequent than once per second
      print("trying to reset mcp23018\n");
      mcp23018_status = init_mcp23018();
      if (mcp23018_status) {
        print("left side not responding\n");
      } else {
        print("left side attached\n");
      }
    }
  }
#endif

  for (uint8_t row = 0; row < MATRIX_ROWS; row++)
  {
    matrix_row_t cols;

    matrix_select_row(row);
#ifndef RIGHT_HALF
    _delay_us(5);
#endif

    cols = (
      // cols 0..7, PORTA 0 -> 7
      (~PINA) & 0xFF
    );

#ifdef RIGHT_HALF
    uint8_t data = 0x7F;
    // Receive the columns from right half
    i2c_receive(I2C_ADDR_WRITE, &data, 1, MCP23018_I2C_TIMEOUT);
    cols |= ((~(data) & 0x7F) << 7);
#endif

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

  matrix_scan_quantum();

#ifdef DEBUG_MATRIX
  for (uint8_t c = 0; c < MATRIX_COLS; c++)
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
      if (matrix_is_on(r, c)) xprintf("r:%d c:%d \n", r, c);
#endif

  return 1;
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

static void matrix_select_row(uint8_t row)
{
#ifdef RIGHT_HALF
  uint8_t txdata[3];

  //Set the remote row on port A
  txdata[0] = GPIOA;
  txdata[1] = 0xFF & ~(1<<row);
  mcp23018_status = i2c_transmit(I2C_ADDR_WRITE, (uint8_t *)txdata, 2, MCP23018_I2C_TIMEOUT);
#endif

  // select other half
  DDRB = (1 << row);
  PORTB = ~(1 << row);
}
