/*
Copyright 2012 Jun Wako
Copyright 2014 Jack Humbert
Copyright 2019 @filoxo

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
#include <stdint.h>
#include <stdbool.h>
#if defined(__AVR__)
#include <avr/io.h>
#endif
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "timer.h"
#include "honeycomb.h"
#include "pointing_device.h"
#include "report.h"

#if (MATRIX_COLS <= 8)
# define print_matrix_header()  print("\nr/c 01234567\n")
# define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
# define matrix_bitpop(i)       bitpop(matrix[i])
# define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
# define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
# define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
# define matrix_bitpop(i)       bitpop16(matrix[i])
# define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
# define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
# define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
# define matrix_bitpop(i)       bitpop32(matrix[i])
# define ROW_SHIFTER  ((uint32_t)1)
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
//extern int8_t encoderValue;
int8_t encoderValue = 0;

__attribute__ ((weak))
void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
    matrix_scan_kb();
}

__attribute__ ((weak))
void matrix_init_kb(void) {
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    SERIAL_UART_INIT();

    uint32_t timeout = 0;

    // The 's' character requests the RF slave to send the matrix
    SERIAL_UART_DATA = 's';

    // Trust the external keystates entirely, erase the last data
    uint8_t uart_data[4] = {0};

    // There are 3 bytes corresponding to the data, and a checksum
    for (uint8_t i = 0; i < 4; i++) {
        // Wait for the serial data, timeout if it's been too long
        // This only happened in testing with a loose wire, but does no
        // harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
                xprintf("\r\nTime out in keyboard.");
                break;
            }
        }
        uart_data[i] = SERIAL_UART_DATA;
    }

    // Check for the end packet, it's our checksum.
    // Will only be a match if the correct bytes were recieved
    if (uart_data[3] == (uart_data[0] ^ uart_data[1] ^ uart_data[2])) { // This is an arbitrary checksum calculated by XORing all the data.
        // Transferring the keystates to the QMK matrix variable
		/* ASSUMING MSB FIRST */
		matrix[0] = ((uint16_t) uart_data[0] << 8) | ((uint16_t) uart_data[1]);
		encoderValue += (int8_t) uart_data[2];
		if ((uart_data[0] | uart_data[1] | uart_data[2])!=0){
			xprintf("\r\n0x%0X%02X%02X",uart_data[0],uart_data[1], uart_data[2]);
		}
		/* OK, TURNS OUT THAT WAS A BAD ASSUMPTION */
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
			// I've unpacked these into the mirror image of what QMK expects them to be, so...
			matrix[i] = bitrev16(matrix[i]);
			// So I'll reverse it, and this should be fine now.
        }

        // A mouse report for scrolling would go here, but I don't plan on doing scrolling with the encoder. So.

    	report_mouse_t currentReport = {};
/*
    	currentReport = pointing_device_get_report();
            //mouseReport.x = 127 max -127 min
    	currentReport.x = (int8_t) uart_data[6];
            //mouseReport.y = 127 max -127 min
    	currentReport.y = (int8_t) uart_data[7];
            //mouseReport.v = 127 max -127 min (scroll vertical)
    	currentReport.v = (int8_t) uart_data[8];
            //mouseReport.h = 127 max -127 min (scroll horizontal)
    	currentReport.h = (int8_t) uart_data[9];
        */
    	/*
    	currentReport.x = 0;
    	currentReport.y = 0;
    	currentReport.v = 0;
        currentReport.h = 0;*/

        pointing_device_set_report(currentReport);
    } else {
        xprintf("\r\nRequested packet, data 3 was %d",uart_data[3]);
    }

    matrix_scan_quantum();
    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}
