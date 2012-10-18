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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "serial.h"
#include "matrix.h"
#include "debug.h"


/*
 * Matrix Array usage:
 *
 * ROW: 16(4bits)
 * COL:  8(3bits)
 *
 *    8bit wide
 *   +---------+
 *  0|00 ... 07|
 *  1|08 ... 0F|
 *  :|   ...   |
 *  :|   ...   |
 *  E|70 ... 77|
 *  F|78 ... 7F|
 *   +---------+
 *
 * Command From System To Keyboard
 * 0x01 Reset
 * 0x02 Bell On
 * 0x03 Bell Off
 * 0x0A Click On
 * 0x0B Click Off
 * 0x0E LED
 * 0x0F Layout
 *
 * Command From Keyboard To System
 * 0x7F Idle
 * 0xFE Layout Response
 * 0xFF Reset Response(followed by 0x04)
 *
 * bit: 3       2       1       0
 * LED: CapsLk  ScrLk   Compose NumLk
 *      
 * Connector
 *   8Pin mini DIN
 *      8  7  6
 *     5    4  3
 *       2   1
 *     receptacle
 *
 * 1: GND
 * 2: GND
 * 3: 5V
 * 4: RX/TX(Mouse)
 * 5: RX
 * 6: TX
 * 7: GND
 * 8: 5V
 */
static uint8_t matrix[MATRIX_ROWS];
#define ROW(code)      ((code>>3)&0xF)
#define COL(code)      (code&0x07)

static bool is_modified = false;


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
    print_enable = true;
    debug_enable = true;

    serial_init();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    return;
}

uint8_t matrix_scan(void)
{
    is_modified = false;

    uint8_t code;
    code = serial_recv();
    if (code == 0) {
        return 0;
    }

    phex(code); print("(");
    code = ~code;
    phex(code); print(")");
return 0;
    if (code&0x80) {
        // break code
        if (matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] &= ~(1<<COL(code));
            is_modified = true;
        }
    } else {
        // make code
        if (!matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] |=  (1<<COL(code));
            is_modified = true;
        }
    }
    return code;
}

bool matrix_is_modified(void)
{
    return is_modified;
}

inline
bool matrix_has_ghost(void)
{
    return false;
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
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop(matrix[i]);
    }
    return count;
}
