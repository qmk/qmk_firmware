/* Copyright 2015-2017 Jack Humbert
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

#ifndef CONFIG_DEFINITIONS_H
#define CONFIG_DEFINITIONS_H

/* diode directions */
#define COL2ROW       0
#define ROW2COL       1
#define CUSTOM_MATRIX 2 /* Disables built-in matrix scanning code */

#ifdef __AVR__
    /* I/O pins */
    #ifndef F0
        #define B0 0x30
        #define B1 0x31
        #define B2 0x32
        #define B3 0x33
        #define B4 0x34
        #define B5 0x35
        #define B6 0x36
        #define B7 0x37
        #define C0 0x60
        #define C1 0x61
        #define C2 0x62
        #define C3 0x63
        #define C4 0x64
        #define C5 0x65
        #define C6 0x66
        #define C7 0x67
        #define D0 0x90
        #define D1 0x91
        #define D2 0x92
        #define D3 0x93
        #define D4 0x94
        #define D5 0x95
        #define D6 0x96
        #define D7 0x97
        #define E0 0xC0
        #define E1 0xC1
        #define E2 0xC2
        #define E3 0xC3
        #define E4 0xC4
        #define E5 0xC5
        #define E6 0xC6
        #define E7 0xC7
        #define F0 0xF0
        #define F1 0xF1
        #define F2 0xF2
        #define F3 0xF3
        #define F4 0xF4
        #define F5 0xF5
        #define F6 0xF6
        #define F7 0xF7
        #define A0 0x00
        #define A1 0x01
        #define A2 0x02
        #define A3 0x03
        #define A4 0x04
        #define A5 0x05
        #define A6 0x06
        #define A7 0x07
    #endif
#elif defined(PROTOCOL_CHIBIOS)
    #define A0  PAL_LINE(GPIOA, 0)
    #define A1  PAL_LINE(GPIOA, 1)
    #define A2  PAL_LINE(GPIOA, 2)
    #define A3  PAL_LINE(GPIOA, 3)
    #define A4  PAL_LINE(GPIOA, 4)
    #define A5  PAL_LINE(GPIOA, 5)
    #define A6  PAL_LINE(GPIOA, 6)
    #define A7  PAL_LINE(GPIOA, 7)
    #define A8  PAL_LINE(GPIOA, 8)
    #define A9  PAL_LINE(GPIOA, 9)
    #define A10 PAL_LINE(GPIOA, 10)
    #define A11 PAL_LINE(GPIOA, 11)
    #define A12 PAL_LINE(GPIOA, 12)
    #define A13 PAL_LINE(GPIOA, 13)
    #define A14 PAL_LINE(GPIOA, 14)
    #define A15 PAL_LINE(GPIOA, 15)
    #define B0  PAL_LINE(GPIOB, 0)
    #define B1  PAL_LINE(GPIOB, 1)
    #define B2  PAL_LINE(GPIOB, 2)
    #define B3  PAL_LINE(GPIOB, 3)
    #define B4  PAL_LINE(GPIOB, 4)
    #define B5  PAL_LINE(GPIOB, 5)
    #define B6  PAL_LINE(GPIOB, 6)
    #define B7  PAL_LINE(GPIOB, 7)
    #define B8  PAL_LINE(GPIOB, 8)
    #define B9  PAL_LINE(GPIOB, 9)
    #define B10 PAL_LINE(GPIOB, 10)
    #define B11 PAL_LINE(GPIOB, 11)
    #define B12 PAL_LINE(GPIOB, 12)
    #define B13 PAL_LINE(GPIOB, 13)
    #define B14 PAL_LINE(GPIOB, 14)
    #define B15 PAL_LINE(GPIOB, 15)
    #define C0  PAL_LINE(GPIOC, 0)
    #define C1  PAL_LINE(GPIOC, 1)
    #define C2  PAL_LINE(GPIOC, 2)
    #define C3  PAL_LINE(GPIOC, 3)
    #define C4  PAL_LINE(GPIOC, 4)
    #define C5  PAL_LINE(GPIOC, 5)
    #define C6  PAL_LINE(GPIOC, 6)
    #define C7  PAL_LINE(GPIOC, 7)
    #define C8  PAL_LINE(GPIOC, 8)
    #define C9  PAL_LINE(GPIOC, 9)
    #define C10 PAL_LINE(GPIOC, 10)
    #define C11 PAL_LINE(GPIOC, 11)
    #define C12 PAL_LINE(GPIOC, 12)
    #define C13 PAL_LINE(GPIOC, 13)
    #define C14 PAL_LINE(GPIOC, 14)
    #define C15 PAL_LINE(GPIOC, 15)
    #define D0  PAL_LINE(GPIOD, 0)
    #define D1  PAL_LINE(GPIOD, 1)
    #define D2  PAL_LINE(GPIOD, 2)
    #define D3  PAL_LINE(GPIOD, 3)
    #define D4  PAL_LINE(GPIOD, 4)
    #define D5  PAL_LINE(GPIOD, 5)
    #define D6  PAL_LINE(GPIOD, 6)
    #define D7  PAL_LINE(GPIOD, 7)
    #define D8  PAL_LINE(GPIOD, 8)
    #define D9  PAL_LINE(GPIOD, 9)
    #define D10 PAL_LINE(GPIOD, 10)
    #define D11 PAL_LINE(GPIOD, 11)
    #define D12 PAL_LINE(GPIOD, 12)
    #define D13 PAL_LINE(GPIOD, 13)
    #define D14 PAL_LINE(GPIOD, 14)
    #define D15 PAL_LINE(GPIOD, 15)
    #define E0  PAL_LINE(GPIOE, 0)
    #define E1  PAL_LINE(GPIOE, 1)
    #define E2  PAL_LINE(GPIOE, 2)
    #define E3  PAL_LINE(GPIOE, 3)
    #define E4  PAL_LINE(GPIOE, 4)
    #define E5  PAL_LINE(GPIOE, 5)
    #define E6  PAL_LINE(GPIOE, 6)
    #define E7  PAL_LINE(GPIOE, 7)
    #define E8  PAL_LINE(GPIOE, 8)
    #define E9  PAL_LINE(GPIOE, 9)
    #define E10 PAL_LINE(GPIOE, 10)
    #define E11 PAL_LINE(GPIOE, 11)
    #define E12 PAL_LINE(GPIOE, 12)
    #define E13 PAL_LINE(GPIOE, 13)
    #define E14 PAL_LINE(GPIOE, 14)
    #define E15 PAL_LINE(GPIOE, 15)
    #define F0  PAL_LINE(GPIOF, 0)
    #define F1  PAL_LINE(GPIOF, 1)
    #define F2  PAL_LINE(GPIOF, 2)
    #define F3  PAL_LINE(GPIOF, 3)
    #define F4  PAL_LINE(GPIOF, 4)
    #define F5  PAL_LINE(GPIOF, 5)
    #define F6  PAL_LINE(GPIOF, 6)
    #define F7  PAL_LINE(GPIOF, 7)
    #define F8  PAL_LINE(GPIOF, 8)
    #define F9  PAL_LINE(GPIOF, 9)
    #define F10 PAL_LINE(GPIOF, 10)
    #define F11 PAL_LINE(GPIOF, 11)
    #define F12 PAL_LINE(GPIOF, 12)
    #define F13 PAL_LINE(GPIOF, 13)
    #define F14 PAL_LINE(GPIOF, 14)
    #define F15 PAL_LINE(GPIOF, 15)
#endif

/* USART configuration */
#ifdef BLUETOOTH_ENABLE
#   ifdef __AVR_ATmega32U4__
#      define SERIAL_UART_BAUD 9600
#      define SERIAL_UART_DATA UDR1
#      define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#      define SERIAL_UART_RXD_VECT USART1_RX_vect
#      define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#      define SERIAL_UART_INIT() do { \
            /* baud rate */ \
            UBRR1L = SERIAL_UART_UBRR; \
            /* baud rate */ \
            UBRR1H = SERIAL_UART_UBRR >> 8; \
            /* enable TX */ \
            UCSR1B = _BV(TXEN1); \
            /* 8-bit data */ \
            UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
            sei(); \
        } while(0)
#   else
#       error "USART configuration is needed."
#   endif
#endif

#define API_SYSEX_MAX_SIZE 32

#include "song_list.h"

#endif
