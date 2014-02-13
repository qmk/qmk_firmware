/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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
#include <avr/io.h>
#include <util/delay.h>
#include "action.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "ibm4704.h"
#include "matrix.h"


static void matrix_make(uint8_t code);
static void matrix_break(uint8_t code);
static void matrix_clear(void);


/*
 * Matrix Array usage:
 * IBM 4704 scan codes are assigned into 128(16x8)-cell matrix.
 *
 *    8bit wide
 *   +---------+
 *  0|         |
 *  :|   XX    | 00-7F
 *  f|         |
 *   +---------+
 *
 * Exceptions:
 */
static uint8_t matrix[MATRIX_ROWS];

// scan code bits  7654 3210
// R:row/C:column  -RRR RCCC
#define ROW(code)      ((code>>3)&0x0f)
#define COL(code)      (code&0x07)


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

static void enable_break(void)
{
    uint8_t ret;
    print("Enable break: ");
    // valid scancode: 00-77h
    for (uint8_t code = 0; code < 0x78; code++) {
        while (ibm4704_send(0x80|code) != 0) {
            print("z");
            _delay_us(500);
        }
        _delay_us(2000);
        ret = ibm4704_recv();
        if (ret != 0xff) {
            xprintf("c%02X:r%02X ", code, ret);
        }
        _delay_us(1000);
    }
    _delay_us(1000);
    while (ibm4704_send(0xFF) != 0) { _delay_us(500); } // End
    print("End\n");
}

void matrix_init(void)
{
    uint8_t ret;
    debug_enable = true;

    ibm4704_init();
    matrix_clear();

    // read keyboard id
    while ((ret = ibm4704_recv()) == 0xFF) {
        ibm4704_send(0xFE);
        _delay_us(100);
    }

    _delay_ms(2000);    // wait for starting up debug console 
    print("IBM 4704 converter\n");
    xprintf("Keyboard ID: %02X\n", ret);
    enable_break();
}

/*
 * IBM 4704 Scan Code
 */
uint8_t matrix_scan(void)
{
    uint8_t code = ibm4704_recv();
    if (code==0xFF) {
        // Not receivd
        return 0;
    } else if ((code&0x78)==0x78) {
        // 0xFF-F8 and 0x7F-78 is not scancode
        xprintf("Error: %0X\n", code);
        matrix_clear();
        return 0;
    } else if (code&0x80) {
        matrix_make(code);
    } else {
        matrix_break(code);
    }
    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        xprintf("%02X: %08b\n", row, bitrev(matrix_get_row(row)));
    }
}



inline
static void matrix_make(uint8_t code)
{
    matrix[ROW(code)] |= 1<<COL(code);
}

inline
static void matrix_break(uint8_t code)
{
    matrix[ROW(code)] &= ~(1<<COL(code));
}

inline
static void matrix_clear(void)
{
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
}
