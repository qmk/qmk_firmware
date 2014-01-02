/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x5C01
#define DEVICE_VER      0x0100
#define MANUFACTURER    t.m.k.
#define PRODUCT         ASCII keyboard converter
#define DESCRIPTION     converts Serial Console Terminal into USB keyboard


/* matrix size */
#define MATRIX_ROWS     16
#define MATRIX_COLS     16

/* key combination for command */
#define IS_COMMAND()    ( \
    host_get_first_key() == KC_BRK \
)


/*
 * Serial(USART) configuration
 *     asynchronous, positive logic, 19200baud, bit order: LSB first
 *     1-start bit, 8-data bit, odd parity, 1-stop bit
 */
#ifdef __AVR_ATmega32U4__
    #define SERIAL_UART_BAUD       19200
    #define SERIAL_UART_DATA       UDR1
    #define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
    #define SERIAL_UART_RXD_VECT   USART1_RX_vect
    #define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()     do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); /* RX interrupt, RX: enable */ \
        UCSR1B |= (0<<TXCIE1) | (1<<TXEN1); /* TX interrupt, TX: enable */ \
        UCSR1C |= (1<<UPM11) | (1<<UPM10);  /* parity: none(00), even(01), odd(11) */ \
        sei(); \
    } while(0)
#else
    #error "USART configuration is needed."
#endif

/* disable action features */
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION


#endif
