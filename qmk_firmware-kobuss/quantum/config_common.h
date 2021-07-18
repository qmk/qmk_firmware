/* Copyright 2015-2018 Jack Humbert
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

/* diode directions */
#define COL2ROW 0
#define ROW2COL 1

// useful for direct pin mapping
#define NO_PIN (pin_t)(~0)

#ifdef __AVR__
#    ifndef __ASSEMBLER__
#        include <avr/io.h>
#    endif
#    define PORT_SHIFTER 4  // this may be 4 for all AVR chips

// If you want to add more to this list, reference the PINx definitions in these header
// files: https://github.com/vancegroup-mirrors/avr-libc/tree/master/avr-libc/include/avr

#    if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
#        define ADDRESS_BASE 0x00
#        define PINB_ADDRESS 0x3
#        define PINC_ADDRESS 0x6
#        define PIND_ADDRESS 0x9
#        define PINE_ADDRESS 0xC
#        define PINF_ADDRESS 0xF
#    elif defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#        define ADDRESS_BASE 0x00
#        define PINB_ADDRESS 0x3
#        define PINC_ADDRESS 0x6
#        define PIND_ADDRESS 0x9
#    elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#        define ADDRESS_BASE 0x00
#        define PINA_ADDRESS 0x0
#        define PINB_ADDRESS 0x3
#        define PINC_ADDRESS 0x6
#        define PIND_ADDRESS 0x9
#        define PINE_ADDRESS 0xC
#        define PINF_ADDRESS 0xF
#    elif defined(__AVR_ATmega32A__)
#        define ADDRESS_BASE 0x10
#        define PIND_ADDRESS 0x0
#        define PINC_ADDRESS 0x3
#        define PINB_ADDRESS 0x6
#        define PINA_ADDRESS 0x9
#    elif defined(__AVR_ATtiny85__)
#        define ADDRESS_BASE 0x10
#        define PINB_ADDRESS 0x6
#    else
#        error "Pins are not defined"
#    endif

/* I/O pins */
#    define PINDEF(port, pin) ((PIN##port##_ADDRESS << PORT_SHIFTER) | pin)

#    ifdef PORTA
#        define A0 PINDEF(A, 0)
#        define A1 PINDEF(A, 1)
#        define A2 PINDEF(A, 2)
#        define A3 PINDEF(A, 3)
#        define A4 PINDEF(A, 4)
#        define A5 PINDEF(A, 5)
#        define A6 PINDEF(A, 6)
#        define A7 PINDEF(A, 7)
#    endif
#    ifdef PORTB
#        define B0 PINDEF(B, 0)
#        define B1 PINDEF(B, 1)
#        define B2 PINDEF(B, 2)
#        define B3 PINDEF(B, 3)
#        define B4 PINDEF(B, 4)
#        define B5 PINDEF(B, 5)
#        define B6 PINDEF(B, 6)
#        define B7 PINDEF(B, 7)
#    endif
#    ifdef PORTC
#        define C0 PINDEF(C, 0)
#        define C1 PINDEF(C, 1)
#        define C2 PINDEF(C, 2)
#        define C3 PINDEF(C, 3)
#        define C4 PINDEF(C, 4)
#        define C5 PINDEF(C, 5)
#        define C6 PINDEF(C, 6)
#        define C7 PINDEF(C, 7)
#    endif
#    ifdef PORTD
#        define D0 PINDEF(D, 0)
#        define D1 PINDEF(D, 1)
#        define D2 PINDEF(D, 2)
#        define D3 PINDEF(D, 3)
#        define D4 PINDEF(D, 4)
#        define D5 PINDEF(D, 5)
#        define D6 PINDEF(D, 6)
#        define D7 PINDEF(D, 7)
#    endif
#    ifdef PORTE
#        define E0 PINDEF(E, 0)
#        define E1 PINDEF(E, 1)
#        define E2 PINDEF(E, 2)
#        define E3 PINDEF(E, 3)
#        define E4 PINDEF(E, 4)
#        define E5 PINDEF(E, 5)
#        define E6 PINDEF(E, 6)
#        define E7 PINDEF(E, 7)
#    endif
#    ifdef PORTF
#        define F0 PINDEF(F, 0)
#        define F1 PINDEF(F, 1)
#        define F2 PINDEF(F, 2)
#        define F3 PINDEF(F, 3)
#        define F4 PINDEF(F, 4)
#        define F5 PINDEF(F, 5)
#        define F6 PINDEF(F, 6)
#        define F7 PINDEF(F, 7)
#    endif

#    ifndef __ASSEMBLER__
#        define _PIN_ADDRESS(p, offset) _SFR_IO8(ADDRESS_BASE + ((p) >> PORT_SHIFTER) + (offset))
// Port X Input Pins Address
#        define PINx_ADDRESS(p) _PIN_ADDRESS(p, 0)
// Port X Data Direction Register,  0:input 1:output
#        define DDRx_ADDRESS(p) _PIN_ADDRESS(p, 1)
// Port X Data Register
#        define PORTx_ADDRESS(p) _PIN_ADDRESS(p, 2)
#    endif

#elif defined(PROTOCOL_CHIBIOS)
// Defines mapping for Proton C replacement
#    ifdef CONVERT_TO_PROTON_C
// Left side (front)
#        define D3 PAL_LINE(GPIOA, 9)
#        define D2 PAL_LINE(GPIOA, 10)
//      GND
//      GND
#        define D1 PAL_LINE(GPIOB, 7)
#        define D0 PAL_LINE(GPIOB, 6)
#        define D4 PAL_LINE(GPIOB, 5)
#        define C6 PAL_LINE(GPIOB, 4)
#        define D7 PAL_LINE(GPIOB, 3)
#        define E6 PAL_LINE(GPIOB, 2)
#        define B4 PAL_LINE(GPIOB, 1)
#        define B5 PAL_LINE(GPIOB, 0)

// Right side (front)
//      RAW
//      GND
//      RESET
//      VCC
#        define F4 PAL_LINE(GPIOA, 2)
#        define F5 PAL_LINE(GPIOA, 1)
#        define F6 PAL_LINE(GPIOA, 0)
#        define F7 PAL_LINE(GPIOB, 8)
#        define B1 PAL_LINE(GPIOB, 13)
#        define B3 PAL_LINE(GPIOB, 14)
#        define B2 PAL_LINE(GPIOB, 15)
#        define B6 PAL_LINE(GPIOB, 9)

// LEDs (only D5/C13 uses an actual LED)
#        ifdef CONVERT_TO_PROTON_C_RXLED
#            define D5 PAL_LINE(GPIOC, 14)
#            define B0 PAL_LINE(GPIOC, 13)
#        else
#            define D5 PAL_LINE(GPIOC, 13)
#            define B0 PAL_LINE(GPIOC, 14)
#        endif
#    else
#        define A0 PAL_LINE(GPIOA, 0)
#        define A1 PAL_LINE(GPIOA, 1)
#        define A2 PAL_LINE(GPIOA, 2)
#        define A3 PAL_LINE(GPIOA, 3)
#        define A4 PAL_LINE(GPIOA, 4)
#        define A5 PAL_LINE(GPIOA, 5)
#        define A6 PAL_LINE(GPIOA, 6)
#        define A7 PAL_LINE(GPIOA, 7)
#        define A8 PAL_LINE(GPIOA, 8)
#        define A9 PAL_LINE(GPIOA, 9)
#        define A10 PAL_LINE(GPIOA, 10)
#        define A11 PAL_LINE(GPIOA, 11)
#        define A12 PAL_LINE(GPIOA, 12)
#        define A13 PAL_LINE(GPIOA, 13)
#        define A14 PAL_LINE(GPIOA, 14)
#        define A15 PAL_LINE(GPIOA, 15)
#        define B0 PAL_LINE(GPIOB, 0)
#        define B1 PAL_LINE(GPIOB, 1)
#        define B2 PAL_LINE(GPIOB, 2)
#        define B3 PAL_LINE(GPIOB, 3)
#        define B4 PAL_LINE(GPIOB, 4)
#        define B5 PAL_LINE(GPIOB, 5)
#        define B6 PAL_LINE(GPIOB, 6)
#        define B7 PAL_LINE(GPIOB, 7)
#        define B8 PAL_LINE(GPIOB, 8)
#        define B9 PAL_LINE(GPIOB, 9)
#        define B10 PAL_LINE(GPIOB, 10)
#        define B11 PAL_LINE(GPIOB, 11)
#        define B12 PAL_LINE(GPIOB, 12)
#        define B13 PAL_LINE(GPIOB, 13)
#        define B14 PAL_LINE(GPIOB, 14)
#        define B15 PAL_LINE(GPIOB, 15)
#        define B16 PAL_LINE(GPIOB, 16)
#        define B17 PAL_LINE(GPIOB, 17)
#        define B18 PAL_LINE(GPIOB, 18)
#        define B19 PAL_LINE(GPIOB, 19)
#        define C0 PAL_LINE(GPIOC, 0)
#        define C1 PAL_LINE(GPIOC, 1)
#        define C2 PAL_LINE(GPIOC, 2)
#        define C3 PAL_LINE(GPIOC, 3)
#        define C4 PAL_LINE(GPIOC, 4)
#        define C5 PAL_LINE(GPIOC, 5)
#        define C6 PAL_LINE(GPIOC, 6)
#        define C7 PAL_LINE(GPIOC, 7)
#        define C8 PAL_LINE(GPIOC, 8)
#        define C9 PAL_LINE(GPIOC, 9)
#        define C10 PAL_LINE(GPIOC, 10)
#        define C11 PAL_LINE(GPIOC, 11)
#        define C12 PAL_LINE(GPIOC, 12)
#        define C13 PAL_LINE(GPIOC, 13)
#        define C14 PAL_LINE(GPIOC, 14)
#        define C15 PAL_LINE(GPIOC, 15)
#        define D0 PAL_LINE(GPIOD, 0)
#        define D1 PAL_LINE(GPIOD, 1)
#        define D2 PAL_LINE(GPIOD, 2)
#        define D3 PAL_LINE(GPIOD, 3)
#        define D4 PAL_LINE(GPIOD, 4)
#        define D5 PAL_LINE(GPIOD, 5)
#        define D6 PAL_LINE(GPIOD, 6)
#        define D7 PAL_LINE(GPIOD, 7)
#        define D8 PAL_LINE(GPIOD, 8)
#        define D9 PAL_LINE(GPIOD, 9)
#        define D10 PAL_LINE(GPIOD, 10)
#        define D11 PAL_LINE(GPIOD, 11)
#        define D12 PAL_LINE(GPIOD, 12)
#        define D13 PAL_LINE(GPIOD, 13)
#        define D14 PAL_LINE(GPIOD, 14)
#        define D15 PAL_LINE(GPIOD, 15)
#        define E0 PAL_LINE(GPIOE, 0)
#        define E1 PAL_LINE(GPIOE, 1)
#        define E2 PAL_LINE(GPIOE, 2)
#        define E3 PAL_LINE(GPIOE, 3)
#        define E4 PAL_LINE(GPIOE, 4)
#        define E5 PAL_LINE(GPIOE, 5)
#        define E6 PAL_LINE(GPIOE, 6)
#        define E7 PAL_LINE(GPIOE, 7)
#        define E8 PAL_LINE(GPIOE, 8)
#        define E9 PAL_LINE(GPIOE, 9)
#        define E10 PAL_LINE(GPIOE, 10)
#        define E11 PAL_LINE(GPIOE, 11)
#        define E12 PAL_LINE(GPIOE, 12)
#        define E13 PAL_LINE(GPIOE, 13)
#        define E14 PAL_LINE(GPIOE, 14)
#        define E15 PAL_LINE(GPIOE, 15)
#        define F0 PAL_LINE(GPIOF, 0)
#        define F1 PAL_LINE(GPIOF, 1)
#        define F2 PAL_LINE(GPIOF, 2)
#        define F3 PAL_LINE(GPIOF, 3)
#        define F4 PAL_LINE(GPIOF, 4)
#        define F5 PAL_LINE(GPIOF, 5)
#        define F6 PAL_LINE(GPIOF, 6)
#        define F7 PAL_LINE(GPIOF, 7)
#        define F8 PAL_LINE(GPIOF, 8)
#        define F9 PAL_LINE(GPIOF, 9)
#        define F10 PAL_LINE(GPIOF, 10)
#        define F11 PAL_LINE(GPIOF, 11)
#        define F12 PAL_LINE(GPIOF, 12)
#        define F13 PAL_LINE(GPIOF, 13)
#        define F14 PAL_LINE(GPIOF, 14)
#        define F15 PAL_LINE(GPIOF, 15)
#        define G0 PAL_LINE(GPIOG, 0)
#        define G1 PAL_LINE(GPIOG, 1)
#        define G2 PAL_LINE(GPIOG, 2)
#        define G3 PAL_LINE(GPIOG, 3)
#        define G4 PAL_LINE(GPIOG, 4)
#        define G5 PAL_LINE(GPIOG, 5)
#        define G6 PAL_LINE(GPIOG, 6)
#        define G7 PAL_LINE(GPIOG, 7)
#        define G8 PAL_LINE(GPIOG, 8)
#        define G9 PAL_LINE(GPIOG, 9)
#        define G10 PAL_LINE(GPIOG, 10)
#        define G11 PAL_LINE(GPIOG, 11)
#        define G12 PAL_LINE(GPIOG, 12)
#        define G13 PAL_LINE(GPIOG, 13)
#        define G14 PAL_LINE(GPIOG, 14)
#        define G15 PAL_LINE(GPIOG, 15)
#        define H0 PAL_LINE(GPIOH, 0)
#        define H1 PAL_LINE(GPIOH, 1)
#        define H2 PAL_LINE(GPIOH, 2)
#        define H3 PAL_LINE(GPIOH, 3)
#        define H4 PAL_LINE(GPIOH, 4)
#        define H5 PAL_LINE(GPIOH, 5)
#        define H6 PAL_LINE(GPIOH, 6)
#        define H7 PAL_LINE(GPIOH, 7)
#        define H8 PAL_LINE(GPIOH, 8)
#        define H9 PAL_LINE(GPIOH, 9)
#        define H10 PAL_LINE(GPIOH, 10)
#        define H11 PAL_LINE(GPIOH, 11)
#        define H12 PAL_LINE(GPIOH, 12)
#        define H13 PAL_LINE(GPIOH, 13)
#        define H14 PAL_LINE(GPIOH, 14)
#        define H15 PAL_LINE(GPIOH, 15)
#        define I0 PAL_LINE(GPIOI, 0)
#        define I1 PAL_LINE(GPIOI, 1)
#        define I2 PAL_LINE(GPIOI, 2)
#        define I3 PAL_LINE(GPIOI, 3)
#        define I4 PAL_LINE(GPIOI, 4)
#        define I5 PAL_LINE(GPIOI, 5)
#        define I6 PAL_LINE(GPIOI, 6)
#        define I7 PAL_LINE(GPIOI, 7)
#        define I8 PAL_LINE(GPIOI, 8)
#        define I9 PAL_LINE(GPIOI, 9)
#        define I10 PAL_LINE(GPIOI, 10)
#        define I11 PAL_LINE(GPIOI, 11)
#        define I12 PAL_LINE(GPIOI, 12)
#        define I13 PAL_LINE(GPIOI, 13)
#        define I14 PAL_LINE(GPIOI, 14)
#        define I15 PAL_LINE(GPIOI, 15)
#        define J0 PAL_LINE(GPIOJ, 0)
#        define J1 PAL_LINE(GPIOJ, 1)
#        define J2 PAL_LINE(GPIOJ, 2)
#        define J3 PAL_LINE(GPIOJ, 3)
#        define J4 PAL_LINE(GPIOJ, 4)
#        define J5 PAL_LINE(GPIOJ, 5)
#        define J6 PAL_LINE(GPIOJ, 6)
#        define J7 PAL_LINE(GPIOJ, 7)
#        define J8 PAL_LINE(GPIOJ, 8)
#        define J9 PAL_LINE(GPIOJ, 9)
#        define J10 PAL_LINE(GPIOJ, 10)
#        define J11 PAL_LINE(GPIOJ, 11)
#        define J12 PAL_LINE(GPIOJ, 12)
#        define J13 PAL_LINE(GPIOJ, 13)
#        define J14 PAL_LINE(GPIOJ, 14)
#        define J15 PAL_LINE(GPIOJ, 15)
// Keyboards can `#define KEYBOARD_REQUIRES_GPIOK` if they need to access GPIO-K pins. These conflict with a whole
// bunch of layout definitions, so it's intentionally left out unless absolutely required -- in that case, the
// keyboard designer should use a different symbol when defining their layout macros.
#        ifdef KEYBOARD_REQUIRES_GPIOK
#            define K0 PAL_LINE(GPIOK, 0)
#            define K1 PAL_LINE(GPIOK, 1)
#            define K2 PAL_LINE(GPIOK, 2)
#            define K3 PAL_LINE(GPIOK, 3)
#            define K4 PAL_LINE(GPIOK, 4)
#            define K5 PAL_LINE(GPIOK, 5)
#            define K6 PAL_LINE(GPIOK, 6)
#            define K7 PAL_LINE(GPIOK, 7)
#            define K8 PAL_LINE(GPIOK, 8)
#            define K9 PAL_LINE(GPIOK, 9)
#            define K10 PAL_LINE(GPIOK, 10)
#            define K11 PAL_LINE(GPIOK, 11)
#            define K12 PAL_LINE(GPIOK, 12)
#            define K13 PAL_LINE(GPIOK, 13)
#            define K14 PAL_LINE(GPIOK, 14)
#            define K15 PAL_LINE(GPIOK, 15)
#        endif
#    endif
#endif

/* USART configuration */
#ifdef BLUETOOTH_ENABLE
#    ifdef __AVR_ATmega32U4__
#        define SERIAL_UART_BAUD 9600
#        define SERIAL_UART_DATA UDR1
#        define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#        define SERIAL_UART_RXD_VECT USART1_RX_vect
#        define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#        define SERIAL_UART_INIT()                  \
            do {                                    \
                /* baud rate */                     \
                UBRR1L = SERIAL_UART_UBRR;          \
                /* baud rate */                     \
                UBRR1H = SERIAL_UART_UBRR >> 8;     \
                /* enable TX */                     \
                UCSR1B = _BV(TXEN1);                \
                /* 8-bit data */                    \
                UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
                sei();                              \
            } while (0)
#    elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#        define SERIAL_UART_BAUD 115200
#        define SERIAL_UART_DATA UDR1
/* UBRR should result in ~16 and set UCSR1A = _BV(U2X1) as per rn42 documentation. HC05 needs baudrate configured accordingly */
#        define SERIAL_UART_UBRR (F_CPU / (8UL * SERIAL_UART_BAUD) - 1)
#        define SERIAL_UART_RXD_VECT USART1_RX_vect
#        define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#        define SERIAL_UART_INIT()                  \
            do {                                    \
                UCSR1A = _BV(U2X1);                 \
                /* baud rate */                     \
                UBRR1L = SERIAL_UART_UBRR;          \
                /* baud rate */                     \
                UBRR1H = SERIAL_UART_UBRR >> 8;     \
                /* enable TX */                     \
                UCSR1B = _BV(TXEN1);                \
                /* 8-bit data */                    \
                UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
                sei();                              \
            } while (0)
#    else
#        error "USART configuration is needed."
#    endif
#endif

#define API_SYSEX_MAX_SIZE 32

#include "song_list.h"
