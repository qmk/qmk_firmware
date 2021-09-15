/*
Copyright 2021 MajorKoos <github.com/majorkoos>

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

#include <string.h>
#include <stdio.h>
#include "quantum.h"
#include "i2c_master.h"
#include "vea.h"

#define RIGHT_HALF


void matrix_set_row_status(uint8_t row);


#if defined(RIGHT_HALF)
/* ----------------------- hardware I/O abstraction ------------------------ */
#define PORTCOLUMNS PORTB  ///< port on which we read the state of the columns
#define PINCOLUMNS  PINB   ///< port on which we read the state of the columns
#define DDRCOLUMNS  DDRB   ///< port on which we read the state of the columns
#define PORTROWS1   PORTA  ///< first port connected to the matrix rows
#define PINROWS1    PINA   ///< first port connected to the matrix rows
#define DDRROWS1    DDRA   ///< first port connected to the matrix rows
#define PORTROWS2   PORTC  ///< second port connected to the matrix rows
#define PINROWS2    PINC   ///< second port connected to the matrix rows
#define DDRROWS2    DDRC   ///< second port connected to the matrix rows


// register addresses (see "mcp23018.md")
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15

#define TW_READ		1
#define TW_WRITE	0

#define MCP23018_TWI_ADDRESS 0b0100000

// TWI aliases
#define TWI_ADDR_WRITE ( (MCP23018_TWI_ADDRESS<<1) | TW_WRITE )
#define TWI_ADDR_READ  ( (MCP23018_TWI_ADDRESS<<1) | TW_READ  )

#define I2C_TIMEOUT     10
#define MCP_ROWS_START	8

uint8_t mcp23018_init(void) {
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

void matrix_init_custom(void) {
    // initialize matrix ports - cols, rows
	// PB0-PB7 : col0 .. col7
	// PA0-PA7 : row0 .. row7
	// PC7-PC2 : row8 .. row13

	// PD0 : NUM
    // PD1 : CAPS
    // PD2 : D+ / Clock
    // PD3 : D- / Data
    // PD4 : FULL LED
    // PD5 : 3.6V switch TR
	// PD6 : SCRL
    // PD7 : row14


	// signal direction : col -> row

    // pc(PORTROWS1)0, 1 : twi
	DDRCOLUMNS 	= 0xFF;	// all outputs for cols
	PORTCOLUMNS	= 0xFF;	// high

	// all inputs for rows
	DDRROWS1	= 0x00;
	DDRROWS2	&= ~(0x111111<<2); //0x00;
	DDRD        &= ~(1<<PIND7); // row 14

	// all rows pull-up.
	PORTROWS1	= 0xFF;
	PORTROWS2	|= (0b111111<<2); //0x11111100;
	PORTD 		|= (1<<PIND7);// row 14

    i2c_init();

#if defined(RIGHT_HALF)
    // Initialize the chip on the other half
    mcp23018_init();
#endif

}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row];

        matrix_row_t cols = 0;
	    // Select the row to scan
        matrix_set_row_status(row);

        matrix_io_delay();
	    //Set the local row

#if defined(RIGHT_HALF)
		// Initialize to 0x7F in case I2C read fails,
		// as 0x75 would be no keys pressed
		uint8_t data = 0x7F;
		// Receive the columns from right half
		i2c_receive(TWI_ADDR_WRITE, &data, 1, I2C_TIMEOUT);
#endif

        // cols |= ((~(PINA | 0x80)) & 0x7F);
        cols |= ((~(PINA)) & 0xFF);
#if defined(RIGHT_HALF)
		cols |= (((~(data | 0x80)) & 0x7F) << MCP_ROWS_START);
#endif

        current_matrix[row] = cols;
        matrix_has_changed |= (last_row_value != current_matrix[row]);
    }

    return matrix_has_changed;
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
