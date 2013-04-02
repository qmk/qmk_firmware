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
#include "matrix.h"
#include "debug.h"
#include "protocol/serial.h"


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

static void pc98_inhibit_repeat(void)
{
    uint8_t code;

    while (serial_recv()) ;
RETRY:
    PC98_RDY_PORT |= (1<<PC98_RDY_BIT);
    _delay_ms(500);
    serial_send(0x9C);

    PC98_RDY_PORT &= ~(1<<PC98_RDY_BIT);
    _delay_ms(100);
    while (!(code = serial_recv())) ;
    print("PC98: send 9C: "); print_hex8(code); print("\n");
    if (code != 0xFA) goto RETRY;



    PC98_RDY_PORT |= (1<<PC98_RDY_BIT);
    _delay_ms(100);
    serial_send(0x70);

    PC98_RDY_PORT &= ~(1<<PC98_RDY_BIT);
    _delay_ms(100);
    //code = serial_recv();
    while (!(code = serial_recv())) ;
    print("PC98: send 70: "); print_hex8(code); print("\n");
    if (code != 0xFA) goto RETRY;
}

void matrix_init(void)
{
    PC98_RST_DDR |= (1<<PC98_RST_BIT);
    PC98_RDY_DDR |= (1<<PC98_RDY_BIT);
    PC98_RTY_DDR |= (1<<PC98_RTY_BIT);
    PC98_RST_PORT |= (1<<PC98_RST_BIT);
    PC98_RDY_PORT |= (1<<PC98_RDY_BIT);
    PC98_RTY_PORT |= (1<<PC98_RTY_BIT);


    serial_init();

    // PC98 reset
/*
    PC98_RST_PORT &= ~(1<<PC98_RST_BIT);
    _delay_us(15);
    PC98_RST_PORT |= (1<<PC98_RST_BIT);
    _delay_us(13);
    PC98_RDY_PORT &= ~(1<<PC98_RDY_BIT);
*/

    _delay_ms(500);
    pc98_inhibit_repeat();


    // PC98 ready
    PC98_RDY_PORT &= ~(1<<PC98_RDY_BIT);

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    debug("init\n");
    return;
}

uint8_t matrix_scan(void)
{
    is_modified = false;

    uint16_t code;
    PC98_RDY_PORT |= (1<<PC98_RDY_BIT);
    _delay_us(30);
    code = serial_recv2();
    PC98_RDY_PORT &= ~(1<<PC98_RDY_BIT);
    if (code == -1) return 0;

if (code == 0x60) {
    pc98_inhibit_repeat();

/*
    PC98_RDY_PORT |= (1<<PC98_RDY_BIT);
    _delay_ms(100);
    serial_send(0x96);
    PC98_RDY_PORT &= ~(1<<PC98_RDY_BIT);
*/

    return 0;
}

    print_hex8(code); print(" ");

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
