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
#pragma once

#define CAPSENSE_DAC_SCLK   B1
#define CAPSENSE_DAC_DIN    B2
#define CAPSENSE_DAC_SYNC_N B0
#define CAPSENSE_DAC_MAX    1023

#define CAPSENSE_SHIFT_DIN  C4
#define CAPSENSE_SHIFT_OE   C6
#define CAPSENSE_SHIFT_SHCP C5
#define CAPSENSE_SHIFT_STCP C7
#define CAPSENSE_SHIFT_STCP_IO _SFR_IO_ADDR(PORTC)
#define CAPSENSE_SHIFT_STCP_BIT 7

#define SETUP_ROW_GPIOS() do {} while (0)

#define SETUP_UNUSED_PINS() do {} while (0)
/*
#if 1
#define SETUP_UNUSED_PINS() do {} while (0)
#else
// TODO ENABLE THIS ONCE TESTED
#define SETUP_UNUSED_PINS() \
    do { \
        PORTB |= ~(DDRB | 0x07); \
        PORTC |= ~(DDRC | 0xf3); \
        PORTD |= ~(DDRD | 0x8f); \
    } while (0)
#endif
*/

#define CAPSENSE_READ_ROWS_NUMBER_OF_BYTES_PER_SAMPLE 2
#define CAPSENSE_READ_ROWS_PIN_1 _SFR_IO_ADDR(PIND)
#define CAPSENSE_READ_ROWS_PIN_2 _SFR_IO_ADDR(PIND)
// #    define CAPSENSE_READ_ROWS_ASM_INSTRUCTIONS "in %[dest_row_1], %[ioreg_row_1]\n\tin %[dest_row_2], %[ioreg_row_2]"
#define CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS \
        "st %a[arr]+, %[dest_row_1]"       "\n\t" \
        "st %a[arr]+, %[dest_row_2]"
#define CAPSENSE_READ_ROWS_STORE_TO_ARRAY_INSTRUCTIONS_FAKE \
        "st %a[arr], %[dest_row_1]"       "\n\t" \
        "st %a[arr], %[dest_row_2]"
// #    define CAPSENSE_READ_ROWS_OUTPUT_CONSTRAINTS [dest_row_1] "=&r" (dest_row_1), [dest_row_2] "=&r" (dest_row_2)
// #    define CAPSENSE_READ_ROWS_INPUT_CONSTRAINTS [ioreg_row_1] "I" (CAPSENSE_READ_ROWS_PIN_1), [ioreg_row_2] "I" (CAPSENSE_READ_ROWS_PIN_2)
// #    define CAPSENSE_READ_ROWS_LOCAL_VARS uint8_t dest_row_1, dest_row_2
// #    define CAPSENSE_READ_ROWS_VALUE (dest_row_1 & 0xf)
#define CAPSENSE_READ_ROWS_EXTRACT_FROM_ARRAY do { dest_row_1 = array[p0++]; dest_row_2 = array[p0++]; } while (0)

// Note: for now Beamspring reads PIND twice to match model F timings. We might change that in the future

#define CAPSENSE_KEYMAP_ROW_TO_PHYSICAL_ROW(row) (row)
#define CAPSENSE_PHYSICAL_ROW_TO_KEYMAP_ROW(row) (row)
#ifndef CAPSENSE_KEYMAP_COL_TO_PHYSICAL_COL
  #define CAPSENSE_KEYMAP_COL_TO_PHYSICAL_COL(col) (col)
#endif

#if (!defined(CAPSENSE_CONDUCTIVE_PLASTIC_IS_PUSHED_DOWN_ON_KEYPRESS)) && (!defined(CAPSENSE_CONDUCTIVE_PLASTIC_IS_PULLED_UP_ON_KEYPRESS))
  #define CAPSENSE_CONDUCTIVE_PLASTIC_IS_PULLED_UP_ON_KEYPRESS
#endif

//static inline uint8_t read_rows(void);
