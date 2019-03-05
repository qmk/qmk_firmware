/*
Copyright 2012 Jun Wako
Copyright 2014 Jack Humbert

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
#include "dichotomy.h"
#include "pointing_device.h"
#include "report.h"

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop32(matrix[i])
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

#define MAIN_ROWMASK 0xFFF0;
#define LOWER_ROWMASK 0x3FC0;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

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

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {
    DDRF |= (1<<6);
    DDRF |= (1<<5);
    DDRD |= (1<<1);
    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    SERIAL_UART_INIT();
    //xprintf("\r\nTRYING TO SCAN");

    uint32_t timeout = 0;

    //the s character requests the RF slave to send the matrix
    SERIAL_UART_DATA = 's';

    //trust the external keystates entirely, erase the last data
    uint8_t uart_data[11] = {0};

    //there are 10 bytes corresponding to 10 columns, and an end byte
    for (uint8_t i = 0; i < 11; i++) {
        //wait for the serial data, timeout if it's been too long
        //this only happened in testing with a loose wire, but does no
        //harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
		xprintf("\r\nTime out in keyboard.");
                break;
            }
        }
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, the key state bytes use the LSBs, so 0xE0
    //will only show up here if the correct bytes were recieved
            uint8_t checksum = 0x00;
            for (uint8_t z=0; z<10; z++){
                checksum = checksum^uart_data[z];
            }
            checksum = checksum ^ (uart_data[10] & 0xF0);
            // Smash the checksum from 1 byte into 4 bits
            checksum = (checksum ^ ((checksum & 0xF0)>>4)) & 0x0F;
//xprintf("\r\nGOT RAW PACKET: \r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d",uart_data[0],uart_data[1],uart_data[2],uart_data[3],uart_data[4],uart_data[5],uart_data[6],uart_data[7],uart_data[8],uart_data[9],uart_data[10],checksum);
    if ((uart_data[10] & 0x0F) == checksum) { //this is an arbitrary binary checksum (1001) (that would be 0x9.)
	//xprintf("\r\nGOT PACKET: \r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d",uart_data[0],uart_data[1],uart_data[2],uart_data[3],uart_data[4],uart_data[5]);
        //shifting and transferring the keystates to the QMK matrix variable
		//bits 1-12 are row 1, 13-24 are row 2, 25-36 are row 3,
		//bits 37-42 are row 4 (only 6 wide, 1-3 are 0, and 10-12 are 0)
		//bits 43-48 are row 5 (same as row 4)
		/* ASSUMING MSB FIRST */
		matrix[0] = (((uint16_t) uart_data[0] << 8) | ((uint16_t) uart_data[1])) & MAIN_ROWMASK;
		matrix[1] = ((uint16_t) uart_data[1] << 12) | ((uint16_t) uart_data[2] << 4);
		matrix[2] = (((uint16_t) uart_data[3] << 8) | ((uint16_t) uart_data[4])) & MAIN_ROWMASK;
		matrix[3] = (((uint16_t) uart_data[4] << 9) | ((uint16_t) uart_data[5] << 1)) & LOWER_ROWMASK;
		matrix[4] = (((uint16_t) uart_data[5] << 7) | ((uart_data[10] & 1<<7) ? 1:0) << 13 | ((uart_data[10] & 1<<6) ? 1:0) << 6) & LOWER_ROWMASK;
		/* OK, TURNS OUT THAT WAS A BAD ASSUMPTION */
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
			//I've unpacked these into the mirror image of what QMK expects them to be, so...
			/*uint8_t halfOne = (matrix[i]>>8);
			uint8_t halfTwo = (matrix[i] & 0xFF);
			halfOne = ((halfOne * 0x0802LU & 0x22110LU) | (halfOne * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			halfTwo = ((halfTwo * 0x0802LU & 0x22110LU) | (halfTwo * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			matrix[i] = ((halfTwo<<8) & halfOne);*/
			//matrix[i] = ((matrix[i] * 0x0802LU & 0x22110LU) | (matrix[i] * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			matrix[i] = bitrev16(matrix[i]);
			//bithack mirror!  Doesn't make any sense, but works - and efficiently.
        }
	//if (uart_data[6]!=0 || uart_data[7]!=0){
	//if (maxCount<101){
	//	xprintf("\r\nMouse data: x=%d, y=%d",(int8_t)uart_data[6],(int8_t)uart_data[7]);
	//}
	report_mouse_t currentReport = {};
        //check for the end packet, bytes 1-4 are movement and scroll
        //but byte 5 has bits 0-3 for the scroll button state
	//(1000 if pressed, 0000 if not) and bits 4-7 are always 1
	//We can use this to verify the report sent properly.

	currentReport = pointing_device_get_report();
        //shifting and transferring the info to the mouse report varaible
        //mouseReport.x = 127 max -127 min
	currentReport.x = (int8_t) uart_data[6];
        //mouseReport.y = 127 max -127 min
	currentReport.y = (int8_t) uart_data[7];
        //mouseReport.v = 127 max -127 min (scroll vertical)
	currentReport.v = (int8_t) uart_data[8];
        //mouseReport.h = 127 max -127 min (scroll horizontal)
	currentReport.h = (int8_t) uart_data[9];
	/*
	currentReport.x = 0;
	currentReport.y = 0;
	currentReport.v = 0;
	currentReport.h = 0;*/
	pointing_device_set_report(currentReport);
    } else {
	//xprintf("\r\nRequested packet, data 10 was %d but checksum was %d",(uart_data[10] & 0x0F), (checksum & 0x0F));
    }
    //matrix_print();

    matrix_scan_quantum();
    return 1;
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
