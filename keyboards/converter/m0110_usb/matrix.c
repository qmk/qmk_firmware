/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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

--------------

Ported to QMK by Techsock <info@techsock.com>
*/

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "debug.h"
#include "host.h"
#include "m0110.h"
#include "matrix.h"
#include "report.h"
#include "timer.h"


#define CAPS        0x39
#define CAPS_BREAK  (CAPS | 0x80)
#define ROW(key)    ((key)>>3&0x0F)
#define COL(key)    ((key)&0x07)


static bool is_modified = false;

// matrix state buffer(1:on, 0:off)
static uint8_t *matrix;
static uint8_t _matrix0[MATRIX_ROWS];

static void register_key(uint8_t key);


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

void matrix_init(void)
{
    m0110_init();
    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    matrix = _matrix0;

	matrix_init_quantum();
    return;
}

uint8_t matrix_scan(void)
{
    uint8_t key;

    is_modified = false;
    key = m0110_recv_key();

    if (key == M0110_NULL) {
        return 0;
    } else if (key == M0110_ERROR) {
        return 0;
    } else {
        is_modified = true;
        register_key(key);
    }

    if (debug_enable) {
        print("["); phex(key); print("]\n");
    }
    
    matrix_scan_quantum();
    return 1;
}

void matrix_print(void){

}

inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

inline
static void register_key(uint8_t key)
{
    if (key&0x80) {
        matrix[ROW(key)] &= ~(1<<COL(key));
    } else {
        matrix[ROW(key)] |=  (1<<COL(key));
    }
}
