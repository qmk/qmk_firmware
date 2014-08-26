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
#define PRODUCT_ID      0x2222
#define DEVICE_VER      0x0001
#define MANUFACTURER    t.m.k.
#define PRODUCT         serial mouse converter
#define DESCRIPTION     convert serial mouse into USB


/* matrix size */
#define MATRIX_ROWS 0
#define MATRIX_COLS 0


/* key combination for command */
#define IS_COMMAND()    false



#ifdef SERIAL_MOUSE_MICROSOFT
    /*
     * Serial(USART) configuration (for Microsoft serial mice)
     *     asynchronous, positive logic, 1200baud, bit order: LSB first
     *     1-start bit, 7-data bit, no parity, 1-stop bit
     */
    #define SERIAL_UART_BAUD       1200
    #define SERIAL_UART_DATA       UDR1
    #define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
    #define SERIAL_UART_RXD_VECT   USART1_RX_vect
    #define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()     do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); /* RX interrupt, RX: enable */ \
        UCSR1C = (1<<UCSZ11) | (0<<UCSZ10);  /* no parity, 1 stop bit, 7-bit characters */ \
        sei(); \
    } while(0)

    // for Microsoft mouse protocol
    /* Serial(USART) configuration
     *     asynchronous, negative logic, 1200baud, no flow control
     *     1-start bit, 7-data bit, non parity, 1-stop bit
     */
    #define SERIAL_SOFT_BAUD            1200
    #define SERIAL_SOFT_DATA_7BIT
    #define SERIAL_SOFT_PARITY_NONE
    #define SERIAL_SOFT_BIT_ORDER_LSB
    #define SERIAL_SOFT_LOGIC_NEGATIVE
    /* RXD Port */
    #define SERIAL_SOFT_RXD_DDR         DDRD
    #define SERIAL_SOFT_RXD_PORT        PORTD
    #define SERIAL_SOFT_RXD_PIN         PIND
    #define SERIAL_SOFT_RXD_BIT         2
    #define SERIAL_SOFT_RXD_VECT        INT2_vect
    /* RXD Interupt */
    #define SERIAL_SOFT_RXD_INIT()      do { \
        /* pin configuration: input with pull-up */ \
        SERIAL_SOFT_RXD_DDR &= ~(1<<SERIAL_SOFT_RXD_BIT); \
        SERIAL_SOFT_RXD_PORT |= (1<<SERIAL_SOFT_RXD_BIT); \
        /* enable interrupt: INT2(rising edge) */ \
        EICRA |= ((1<<ISC21)|(1<<ISC20)); \
        EIMSK |= (1<<INT2); \
        sei(); \
    } while (0)
    #define SERIAL_SOFT_RXD_INT_ENTER()
    #define SERIAL_SOFT_RXD_INT_EXIT()  do { \
        /* clear interrupt  flag */ \
        EIFR = (1<<INTF2); \
    } while (0)
    #define SERIAL_SOFT_RXD_READ()      (SERIAL_SOFT_RXD_PIN&(1<<SERIAL_SOFT_RXD_BIT))
    /* TXD Port */
    #define SERIAL_SOFT_TXD_HI()
    #define SERIAL_SOFT_TXD_LO()
    #define SERIAL_SOFT_TXD_INIT()
#elif defined(SERIAL_MOUSE_MOUSESYSTEMS)
    /*
     * Serial(USART) configuration (for Mousesystems serial mice)
     *     asynchronous, positive logic, 1200baud, bit order: LSB first
     *     1-start bit, 8-data bit, no parity, 1-stop bit
     */
    #define SERIAL_UART_BAUD       1200
    #define SERIAL_UART_DATA       UDR1
    #define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
    #define SERIAL_UART_RXD_VECT   USART1_RX_vect
    #define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()     do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); /* RX interrupt, RX: enable */ \
        UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);  /* no parity, 1 stop bit, 8-bit characters */ \
        sei(); \
    } while(0)
#endif




#endif
