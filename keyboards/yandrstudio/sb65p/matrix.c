/* Copyright 2017 Mattia Dal Ben
 * Modified by: 2021 Jason Ren(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    SERIAL_UART_INIT();

    uint32_t timeout = 0;

    //the s character requests the RF slave to send the matrix
    SERIAL_UART_DATA = 's';

    //trust the external keystates entirely, erase the last data
    // 2倍列+1个终止位
    // #define MATRIX_COLS 9
    uint8_t uart_data[19] = {0};

    //there are 9 bytes corresponding to 9 columns, and an end byte
    // 一列一列的接受数据 分左右 还有停止位
    for (uint8_t i = 0; i < 19; i++) {
        //wait for the serial data, timeout if it's been too long
        //this only happened in testing with a loose wire, but does no
        //harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
                break;
            }
        }
        // 一次接受的数据只能试8位
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, the key state bytes use the LSBs, so 0xE0
    //will only show up here if the correct bytes were recieved
    // 判断最后一个位置是否合法
    if (uart_data[18] == 0xE0)
    {
        //shifting and transferring the keystates to the QMK matrix variable
        // 直接把每一行数据复制给matrix，叠加行方法的方便之处便体现出来了
        // 先处理左边的数据，一行一行的处理
        // 由于发过来的是一列一列的数据所以先处理左边
        for (uint8_t i = 0; i < MATRIX_ROWS/2; i++) {
            matrix[i] = (matrix_row_t)((uart_data[0] & 1<<i) ? 1:0) << 0 |
                        (matrix_row_t)((uart_data[1] & 1<<i) ? 1:0) << 1 |
                        (matrix_row_t)((uart_data[2] & 1<<i) ? 1:0) << 2 |
                        (matrix_row_t)((uart_data[3] & 1<<i) ? 1:0) << 3 |
                        (matrix_row_t)((uart_data[4] & 1<<i) ? 1:0) << 4 |
                        (matrix_row_t)((uart_data[5] & 1<<i) ? 1:0) << 5 |
                        (matrix_row_t)((uart_data[6] & 1<<i) ? 1:0) << 6 |
                        (matrix_row_t)((uart_data[7] & 1<<i) ? 1:0) << 7 |
                        (matrix_row_t)((uart_data[8] & 1<<i) ? 1:0) << 8 ;
        }
        // 处理右边的数据，一行一行的处理
        // 由于发过来的是一列一列的数据所以再处理右边
        uint8_t j = 0;
        for (uint8_t i = MATRIX_ROWS/2; i < MATRIX_ROWS; i++, j++) {
            matrix[i] = (matrix_row_t)((uart_data[9]  & 1<<j) ? 1:0) << 0 |
                        (matrix_row_t)((uart_data[10] & 1<<j) ? 1:0) << 1 |
                        (matrix_row_t)((uart_data[11] & 1<<j) ? 1:0) << 2 |
                        (matrix_row_t)((uart_data[12] & 1<<j) ? 1:0) << 3 |
                        (matrix_row_t)((uart_data[13] & 1<<j) ? 1:0) << 4 |
                        (matrix_row_t)((uart_data[14] & 1<<j) ? 1:0) << 5 |
                        (matrix_row_t)((uart_data[15] & 1<<j) ? 1:0) << 6 |
                        (matrix_row_t)((uart_data[16] & 1<<j) ? 1:0) << 7 |
                        (matrix_row_t)((uart_data[17] & 1<<j) ? 1:0) << 8 ;
        }
    }


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
        // phex(row); print(": ");
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
