
/* Copyright 2020 Purdea Andrei
 * Copyright 2021 Matthew J Wolf
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

#include "capsense_matrix.h"
#include "beamspring-rev-4.h"

static inline uint8_t read_rows(void)
{
   uint8_t dest_row_1, dest_row_2;
   asm volatile ( "in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]"
                  : [dest_row_1] "=&r" ( dest_row_1 ), [dest_row_2] "=&r" ( dest_row_2 )
                  : [ioreg_row_1] "I" ( CAPSENSE_READ_ROWS_PIN_1 ), [ioreg_row_2] "I" ( CAPSENSE_READ_ROWS_PIN_2 )
                  );
   return ( dest_row_1 & 0xf );
}


// Timing:
// IN instructions (1 * CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE)
// Store to array instructions (2 * number of bytes)
// adiw: 1 cycle
// cp: 1 cycle
// cpc: 1 cycle
// brlo: 2 cycles (when jumping)
// --- Total loop length:
// 3 * CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE + 5 cycles
// first sample elements will be taken after [1..CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE-1] cycles
// second sample elements will be taken after
//       [3 * CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE + 5 + 1..
//        3 * CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE + 5 + CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE-1] cycles

// the following function requires storage for CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE * (time + 1) bytes
// but returns valid data only in the first (time + 1) bytes
void test_multiple(uint8_t col, uint16_t time, uint8_t *array)
{
    shift_select_col_no_strobe(col);
    uint16_t index;
    // CAPSENSE_READ_ROWS_LOCAL_VARS;
    uint8_t dest_row_1, dest_row_2;
    uint8_t *arrayp = array;
    asm volatile (
             "ldi %A[index], 0"                 "\n\t"
             "ldi %B[index], 0"                 "\n\t"
             "cli"                              "\n\t"
             "sbi %[stcp_regaddr], %[stcp_bit]" "\n\t"
//        "1:" CAPSENSE_READ_ROWS_ASM_INSTRUCTIONS            "\n\t"
             "1: in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]\n\t"
             CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS "\n\t"
             "adiw %A[index], 0x01"             "\n\t"
             "cp %A[index], %A[time]"           "\n\t"
             "cpc %B[index], %B[time]"          "\n\t"
             "brlo 1b"                          "\n\t"
             "sei"                              "\n\t"
             "cbi %[stcp_regaddr], %[stcp_bit]" "\n\t"
      : [arr] "=e" (arrayp),
        [index] "=&w" (index),
//        CAPSENSE_READ_ROWS_OUTPUT_CONSTRAINTS
        [dest_row_1] "=&r" (dest_row_1), [dest_row_2] "=&r" (dest_row_2)
      : [time] "r" (time + 1),
        [stcp_regaddr] "I" (CAPSENSE_SHIFT_STCP_IO),
        [stcp_bit] "I" (CAPSENSE_SHIFT_STCP_BIT),
        //CAPSENSE_READ_ROWS_INPUT_CONSTRAINTS,
        [ioreg_row_1] "I" (CAPSENSE_READ_ROWS_PIN_1), [ioreg_row_2] "I" (CAPSENSE_READ_ROWS_PIN_2),
        "0" (arrayp)
      : "memory" );
    uint16_t i, p0, p1;
    p0 = p1 = 0;
    for (i=0; i<=time; i++)
    {
        CAPSENSE_READ_ROWS_EXTRACT_FROM_ARRAY;
        // array[p1++] = CAPSENSE_READ_ROWS_VALUE;
        array[p1++] =  dest_row_1 & 0xf;
    }
    shift_select_nothing();
    wait_us(CAPSENSE_KEYBOARD_SETTLE_TIME_US);
}

uint8_t test_single(uint8_t col, uint16_t time, uint8_t *interference_ptr)
{
    shift_select_col_no_strobe(col);
    uint16_t index;
    // CAPSENSE_READ_ROWS_LOCAL_VARS;
    uint8_t dest_row_1, dest_row_2;
    uint8_t array[CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE + 1]; // one sample before triggering, and one dummy byte
    uint8_t *arrayp = array;
    asm volatile (
             "ldi %A[index], 0"                 "\n\t"
             "ldi %B[index], 0"                 "\n\t"
             "cli"                              "\n\t"
  //           CAPSENSE_READ_ROWS_ASM_INSTRUCTIONS                 "\n\t"
             "in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]\n\t"
             CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS      "\n\t"
             "sbi %[stcp_regaddr], %[stcp_bit]" "\n\t"
             "1:in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]\n\t"
  //      "1:" CAPSENSE_READ_ROWS_ASM_INSTRUCTIONS                 "\n\t"
             CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS_FAKE "\n\t"
             "adiw %A[index], 0x01"             "\n\t"
             "cp %A[index], %A[time]"           "\n\t"
             "cpc %B[index], %B[time]"          "\n\t"
             "brlo 1b"                          "\n\t"
             "sei"                              "\n\t"
             "cbi %[stcp_regaddr], %[stcp_bit]" "\n\t"
      : [arr] "=e" (arrayp),
        [index] "=&w" (index),
        // CAPSENSE_READ_ROWS_OUTPUT_CONSTRAINTS
        [dest_row_1] "=&r" (dest_row_1), [dest_row_2] "=&r" (dest_row_2)
      : [time] "r" (time + 1),
        [stcp_regaddr] "I" (CAPSENSE_SHIFT_STCP_IO),
        [stcp_bit] "I" (CAPSENSE_SHIFT_STCP_BIT),
        //CAPSENSE_READ_ROWS_INPUT_CONSTRAINTS,
        [ioreg_row_1] "I" (CAPSENSE_READ_ROWS_PIN_1), [ioreg_row_2] "I" (CAPSENSE_READ_ROWS_PIN_2),
        "0" (arrayp)
      : "memory" );
    shift_select_nothing();
    wait_us(CAPSENSE_KEYBOARD_SETTLE_TIME_US);
    // uint8_t value_at_time = CAPSENSE_READ_ROWS_VALUE;
    uint8_t value_at_time = dest_row_1 & 0xf;
    if (interference_ptr)
    {
        uint16_t p0 = 0;
        CAPSENSE_READ_ROWS_EXTRACT_FROM_ARRAY;
        // uint8_t interference = CAPSENSE_READ_ROWS_VALUE;
        uint8_t interference = dest_row_1 & 0xf;
        *interference_ptr = interference;
    }
    return value_at_time;
}
