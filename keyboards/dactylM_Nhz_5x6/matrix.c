// Collected/written/tweaked by NeohertzParts (2020)
//
// Based strongly on ergodox_ez code and existing code for dactyl_manuform
// this keyboard drives the columns and reads the rows as opposed to vice-versa


/*
 *
 *
 *  The I2C device is still on rows 5-9.
 */


/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
//#include "wait.h"
//#include "action_layer.h"
#include "print.h"
//#include "debug.h"
//#include "util.h"
#include "matrix.h"
#include "debounce.h"

#include QMK_KEYBOARD_H

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
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static matrix_row_t read_cols(uint8_t row);
static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;
// static uint16_t mcp23018_reset_loop;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_init(void) {
  // initialize row and col

  mcp23018_status = init_mcp23018();

  //PORTB = PORTB | 0x01; // Turn on case LED

  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i]     = 0;
    raw_matrix[i] = 0;
  }

  debounce_init(MATRIX_ROWS);
  matrix_init_quantum();
}

void matrix_power_up(void) {
		mcp23018_status = init_mcp23018();

		//PORTB = PORTB | 0x01; // Turn on case LED

		unselect_rows();
		init_cols();

		// initialize matrix state: all keys off
		for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
				matrix[i] = 0;
		}
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
  matrix_row_t temp = read_cols(index);
  if (raw_matrix[index] != temp) {
    raw_matrix[index] = temp;
    return true;
  }
  return false;
}

uint8_t matrix_scan(void) {
  if (mcp23018_status) {  // if there was an error
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

  bool changed = false;
  for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) { // 0 -> 4
    // select rows from left and right hands
    uint8_t right_index = i + MATRIX_ROWS_PER_SIDE; // 5 -> 9
    uint8_t left_index  = i;// + MATRIX_ROWS_PER_SIDE; // 5 -> 9
    select_row(left_index);
    select_row(right_index);

    // we don't need a 30us delay anymore, because selecting a
    // left-hand row requires more than 30us for i2c.

    changed |= store_raw_matrix_row(left_index);
    changed |= store_raw_matrix_row(right_index);

    unselect_rows();
	  //_delay_ms(10);
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
  matrix_scan_quantum();

		// Toggle debug LED
		//PORTB = PORTB ^ 0x01;
	//init_mcp23018();
  //print("\n\n\n\n\n\n\n\n");
	//matrix_print();
	//_delay_ms(100);
  return 1;
}

// For indicating the current layer (and other things potentially)
/*
void layer_state_set(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case 0:
      print("layer 0");
      print("\n");
      break;
    case 1:
      print("layer 1");
      print("\n");
      break;
    case 2:
      break;
    case 3:
      break;
    default: //  for any other layers, or the default layer
      break;
  };
}*/

bool matrix_is_modified(void)  // deprecated and evidently not called.
{
  return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //phex(row);
    print(": ");
    //pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += bitpop16(matrix[i]);
  }
  return count;
}

/* Column pin configuration (dactyl's)
 *
 * Teensy
 * col: 6   5   4   3   2   1  0
 * pin: B1  B2  B3  B4  B5  B6 B7
 *
 * MCP23018
 * col: 0   1   2   3   4   5
 * pin: B5  B4  B3  B2  B1  B0
 */
static void init_cols(void) {
		// init on mcp23018
		// not needed, already done as part of init_mcp23018()

		// init on teensy
		// Input with pull-up(DDR:0, PORT:1)
		DDRB &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6);
		PORTB |= (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6);
		//DDRB &= ~(1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7);
		//PORTB |= (1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7);

    // PULLUPS On the I2C pins
		//DDRD &= ~(1 << 2 | 1 << 3);
		PORTD |= (1 << 0 | 1 << 1);

		// Debug LED = OUTPUT, HIGH
		//DDRB = DDRB | 0x01;
		//PORTB |= PORTB | 0x01;
}


static matrix_row_t read_cols(uint8_t row) {
  //pbin(PORTB);
  //print("\n");
  if (row > MATRIX_ROWS_PER_SIDE - 1) { // MCP23017 read
    if (mcp23018_status) {  // if there was an error
      return 0;
    } else {
      uint8_t data    = 0;
      mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);
      if (mcp23018_status) goto out;
      mcp23018_status = i2c_write(GPIOB, DACTYL_I2C_TIMEOUT); // select COLS
      if (mcp23018_status) goto out;
      mcp23018_status = i2c_start(I2C_ADDR_READ, DACTYL_I2C_TIMEOUT);
      if (mcp23018_status) goto out;
      //if (mcp23019_status) goto out;
      //mcp23018_status = i2c_readReg(I2C_ADDR_READ, 0x09, data, 8, DACTYL_I2C_TIMEOUT);  // read register value
      mcp23018_status = i2c_read_nack(DACTYL_I2C_TIMEOUT);
      //if (mcp23018_status < 0) goto out;
      //pbin((int8_t)mcp23018_status);
      //print(" -> ");
      /*data            = (int8_t)(
        (((~mcp23018_status) & 0x08) << 2) | // 1, 0b0000_1000 -> 0b0010_0000
        (((~mcp23018_status) & 0x10)     ) | // 2, 0b0001_0000 -> 0b0001_0000
        (((~mcp23018_status) & 0x04) << 1) | // 3, 0b0000_0100 -> 0b0000_1000
        (((~mcp23018_status) & 0x20) >> 3) | // 4, 0b0010_0000 -> 0b0000_0100
        (((~mcp23018_status) & 0x01) << 1) | // 5, 0b0000_0001 -> 0b0000_0010
        (((~mcp23018_status) & 0x02) >> 1)   // 6, 0b0000_0010 -> 0b0000_0001

      );*/ // column 1
      data = (uint8_t)((~mcp23018_status) & 0x7F);

      mcp23018_status = I2C_STATUS_SUCCESS;
      //pbin(data);
      //print("\n");
      //out:
      i2c_stop();
      // TESTING
      return data;
      //return data;
    out:
      print("Col read i2c error");
      i2c_stop();
      return 0x00;
    }
  } else {
    /* read from teensy
     * bitmask is 0b11110011, but we want those all
     * in the lower six bits.
     * we'll return 1s for the top two, but that's harmless.
     */

     // These are active LOW
     return (~(PINB & 0x7F) & 0x7F);


 /* Teensy
 * col: 0   1   2   3   4   5  6
 * pin: B0  B1  B2  B3  B4  B5 B6

	Port B Bits are: 0b0111_1111
	*/
  //  For testing, only PB0 is used
  //return ~(PINB & 0x01);


    //return ~(((PINB >> 1) & 0x7F)); // 1-6, 0b1111_1110 -> 0b0111_1111
			 //((PINB >> 4) & 0x08) | // 4,   0b1000_0000 -> 0b0000_1000
			 //((PINB << 1) & 0x10) | // 5,   0b0000_1000 -> 0b0001_0000
			 //((PINB << 3) & 0x20)   // 6,   0b0000_0100 -> 0b0010_0000
			 //);
  }
}

/* Row pin configuration
 *
 * Teensy
 * row: 0   1   2   3   4
 * pin: F0  F1  F4  F5  F6
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
  // Hi-Z(DDR:0, PORT:0) to unselect
  DDRF  &= ~(1 << 0 | 1 << 1 | 1 << 4 | 1 << 5 | 1 << 6);
  PORTF &= ~(1 << 0 | 1 << 1 | 1 << 4 | 1 << 5 | 1 << 6);
}
/*
 * Teensy
 * row: 0   1   2   3   4
 * pin: F0  F1  F4  F5  F6
*/

static void select_row(uint8_t row) {
		if (row > (MATRIX_ROWS_PER_SIDE - 1)) {
				//PORTB = PORTB ^ 0x01; // DEBUG LED
				// For selecting row

				// select on mcp23018
				if (mcp23018_status) {  // if there was an error
						// do nothing
						// toggle LED
						//PORTB = 0xFF;
				} else {
						// set active row low  : 0
						// set other rows hi-Z : 1
						mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);
						if (mcp23018_status) goto out;
						mcp23018_status = i2c_write(GPIOA, DACTYL_I2C_TIMEOUT); // writing a row LOW
						if (mcp23018_status) goto out;
            /*
						switch (row) {
							case 5: 	// 1, 0b0000_0100
								row = 0xFF & ~(0x04);
								break;
							case 6:		// 2, 0b0000_0010
								row = 0xFF & ~(0x02);
								break;
							case 7:		// 3, 0b0000_0001
								row = 0xFF & ~(0x01);
								break;
							case 8:		// 4, 0b0000_1000
								row = 0xFF & ~(0x08);
								break;
							case 9:		// 5, 0b0001_0000
								row = 0xFF & ~(0x10);
								break;
							default:
								row = 0xFF;
						}*/
						//pbin(row);
						//print("\n");
            row = 0xFF & ~(0x01 << (row-5));
						mcp23018_status = i2c_write(row, DACTYL_I2C_TIMEOUT);
						if (mcp23018_status) goto out;
						i2c_stop();
            return;
out:
						i2c_stop();
            print("Error'd I2C - Row scan");
				}
		} else {
				// select on teensy
				// Output low(DDR:1, PORT:0) to select
				switch (row) {
						case 0:
								DDRF |= (1 << 0);
								PORTF &= ~(1 << 0);
								break;
						case 1:
								DDRF |= (1 << 1);
								PORTF &= ~(1 << 1);
								break;
						case 2:
								DDRF |= (1 << 4);
								PORTF &= ~(1 << 4);
								break;
						case 3:
								DDRF |= (1 << 5);
								PORTF &= ~(1 << 5);
								break;
						case 4:
								DDRF |= (1 << 6);
								PORTF &= ~(1 << 6);
								break;
				}
		}
}
