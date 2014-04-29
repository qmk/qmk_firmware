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

#ifndef CONFIG_H
#define CONFIG_H

#include <avr/interrupt.h>

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6512
#define DEVICE_VER      0x0001
#define MANUFACTURER    t.m.k.
#define PRODUCT         PS/2 keyboard converter
#define DESCRIPTION     convert PS/2 keyboard to USB


/* matrix size */
#define MATRIX_ROWS 32  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) || \
    keyboard_report->mods == (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RSHIFT)) \
)


//#define NO_SUSPEND_POWER_DOWN


/*
 * PS/2 Busywait
 */
#ifdef PS2_USE_BUSYWAIT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2
#endif

/*
 * PS/2 USART
 */
#ifdef PS2_USE_USART
#if defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
/* XCK for clock line and RXD for data line */
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2
/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
/* XCK for clock line and RXD for data line */
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   4
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0
/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR0C = ((1 << UMSEL00) |  \
              (3 << UPM00)   |  \
              (0 << USBS0)   |  \
              (3 << UCSZ00)  |  \
              (0 << UCPOL0));   \
    UCSR0A = 0;                 \
    UBRR0H = 0;                 \
    UBRR0L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR0B = ((1 << RXCIE0) |       \
              (1 << RXEN0));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR0B = (1 << RXEN0);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR0C = 0;                 \
    UCSR0B &= ~((1 << RXEN0) |  \
                (1 << TXEN0));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR0A & (1<<RXC0))
#define PS2_USART_RX_DATA       UDR0
#define PS2_USART_ERROR         (UCSR0A & ((1<<FE0) | (1<<DOR0) | (1<<UPE0)))
#define PS2_USART_RX_VECT       USART_RX_vect
#endif
#endif

#endif
