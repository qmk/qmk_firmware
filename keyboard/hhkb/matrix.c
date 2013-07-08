/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "matrix.h"


// Timer resolution check
#if (1000000/TIMER_RAW_FREQ > 20)
#   error "Timer resolution(>20us) is not enough for HHKB matrix scan tweak on V-USB."
#endif


// matrix state buffer(1:on, 0:off)
static matrix_row_t *matrix;
static matrix_row_t *matrix_prev;
static matrix_row_t _matrix0[MATRIX_ROWS];
static matrix_row_t _matrix1[MATRIX_ROWS];


// Matrix I/O ports
//
// row:     HC4051[A,B,C]  selects scan row0-7
// col:     LS145[A,B,C,D] selects scan col0-7 and enable(D)
// key:     on: 0/off: 1
// prev:    unknown: output previous key state(negated)?

#if defined(__AVR_AT90USB1286__)
// Ports for Teensy++
// row:     PB0-2
// col:     PB3-5,6
// key:     PE6(pull-uped)
// prev:    PE7
#define KEY_INIT()              do {    \
    DDRB |= 0x7F;                       \
    DDRE |=  (1<<7);                    \
    DDRE &= ~(1<<6);                    \
    PORTE |= (1<<6);                    \
} while (0)
#define KEY_SELECT(ROW, COL)    (PORTB = (PORTB & 0xC0) |       \
                                         (((COL) & 0x07)<<3) |  \
                                         ((ROW) & 0x07))
#define KEY_ENABLE()            (PORTB &= ~(1<<6))
#define KEY_UNABLE()            (PORTB |=  (1<<6))
#define KEY_STATE()             (PINE & (1<<6))
#define KEY_PREV_ON()           (PORTE |=  (1<<7))
#define KEY_PREV_OFF()          (PORTE &= ~(1<<7))
#define KEY_POWER_ON()
#define KEY_POWER_OFF()

#elif defined(__AVR_ATmega32U4__)
// Ports for my designed Alt Controller PCB
// row:     PB0-2
// col:     PB3-5,6
// key:     PD7(pull-uped)
// prev:    PB7
// power:   PD4(L:off/H:on)
#define KEY_INIT()              do {    \
    DDRB  = 0xFF;                       \
    PORTB = 0x00;                       \
    DDRD  &= ~0x80;                     \
    PORTD |= 0x80;                      \
    /* keyswitch board power on */      \
    DDRD  |=  (1<<4);                   \
    PORTD |=  (1<<4);                   \
    KEY_UNABLE();                       \
    KEY_PREV_OFF();                     \
} while (0)
#define KEY_SELECT(ROW, COL)    (PORTB = (PORTB & 0xC0) |       \
                                         (((COL) & 0x07)<<3) |  \
                                         ((ROW) & 0x07))
#define KEY_ENABLE()            (PORTB &= ~(1<<6))
#define KEY_UNABLE()            (PORTB |=  (1<<6))
#define KEY_STATE()             (PIND & (1<<7))
#define KEY_PREV_ON()           (PORTB |=  (1<<7))
#define KEY_PREV_OFF()          (PORTB &= ~(1<<7))
#define KEY_POWER_ON()
#define KEY_POWER_OFF()
/*
#define KEY_POWER_ON()          do {    \
    KEY_INIT();                         \
    PORTD |=  (1<<4);                   \
    _delay_ms(1);                       \
} while (0)
#define KEY_POWER_OFF()         do {    \
    PORTD &= ~(1<<4);                   \
    DDRB  &= ~0xFF;                     \
    PORTB &= ~0xFF;                     \
    DDRB  &= ~0x80;                     \
    PORTB &= ~0x80;                     \
} while (0)
*/


#elif defined(__AVR_ATmega328P__)
// Ports for V-USB
// key:     PB0(pull-uped)
// prev:    PB1
// row:     PB2-4
// col:     PC0-2,3
// power:   PB5(Low:on/Hi-z:off)
#define KEY_INIT()              do {    \
    DDRB  |= 0x3E;                      \
    DDRB  &= ~(1<<0);                   \
    PORTB |= 1<<0;                      \
    DDRC  |= 0x0F;                      \
    KEY_UNABLE();                       \
    KEY_PREV_OFF();                     \
} while (0)
#define KEY_SELECT(ROW, COL)    do {    \
    PORTB = (PORTB & 0xE3) | ((ROW) & 0x07)<<2; \
    PORTC = (PORTC & 0xF8) | ((COL) & 0x07);    \
} while (0)
#define KEY_ENABLE()            (PORTC &= ~(1<<3))
#define KEY_UNABLE()            (PORTC |=  (1<<3))
#define KEY_STATE()             (PINB & (1<<0))
#define KEY_PREV_ON()           (PORTB |=  (1<<1))
#define KEY_PREV_OFF()          (PORTB &= ~(1<<1))
// Power supply switching
#define KEY_POWER_ON()          do {    \
    KEY_INIT();                         \
    PORTB &= ~(1<<5);                   \
    _delay_ms(1);                       \
} while (0)
#define KEY_POWER_OFF()         do {    \
    DDRB  &= ~0x3F;                     \
    PORTB &= ~0x3F;                     \
    DDRC  &= ~0x0F;                     \
    PORTC &= ~0x0F;                     \
} while (0)

#else
#   error "define code for matrix scan"
#endif


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
#ifdef DEBUG
    debug_enable = true;
    debug_keyboard = true;
#endif

    KEY_INIT();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}

uint8_t matrix_scan(void)
{
    uint8_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    KEY_POWER_ON();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            KEY_SELECT(row, col);
            _delay_us(40);

            // Not sure this is needed. This just emulates HHKB controller's behaviour.
            if (matrix_prev[row] & (1<<col)) {
                KEY_PREV_ON();
            }
            _delay_us(7);

            // NOTE: KEY_STATE is valid only in 20us after KEY_ENABLE.
            // If V-USB interrupts in this section we could lose 40us or so
            // and would read invalid value from KEY_STATE.
            uint8_t last = TIMER_RAW;

            KEY_ENABLE();

            // Wait for KEY_STATE outputs its value.
            // 1us was ok on one HHKB, but not worked on another.
            // no   wait doesn't work on Teensy++ with pro(1us works)
            // no   wait does    work on tmk PCB(8MHz) with pro2
            // 1us  wait does    work on both of above
            // 1us  wait doesn't work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz/2)
            // 5us  wait does    work on tmk(8MHz)
            // 10us wait does    work on Teensy++ with pro
            // 10us wait does    work on 328p+iwrap with pro
            // 10us wait doesn't work on tmk PCB(8MHz) with pro2(very lagged scan)
            _delay_us(5);

            if (KEY_STATE()) {
                matrix[row] &= ~(1<<col);
            } else {
                matrix[row] |= (1<<col);
            }

            // Ignore if this code region execution time elapses more than 20us.
            // MEMO: 20[us] * (TIMER_RAW_FREQ / 1000000)[count per us]
            // MEMO: then change above using this rule: a/(b/c) = a*1/(b/c) = a*(c/b)
            if (TIMER_DIFF_RAW(TIMER_RAW, last) > 20/(1000000/TIMER_RAW_FREQ)) {
                matrix[row] = matrix_prev[row];
            }

            KEY_PREV_OFF();
            KEY_UNABLE();
            // NOTE: KEY_STATE keep its state in 20us after KEY_ENABLE.
            // This takes 25us or more to make sure KEY_STATE returns to idle state.
            _delay_us(150);
        }
    }
    KEY_POWER_OFF();
    return 1;
}

bool matrix_is_modified(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i])
            return true;
    }
    return false;
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
matrix_row_t matrix_get_row(uint8_t row)
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
