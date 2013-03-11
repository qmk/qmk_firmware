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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x9898
#define DEVICE_VER      0x0100
#define MANUFACTURER    t.m.k.
#define PRODUCT         PC98 keyboard converter
#define DESCRIPTION     converts PC98 keyboard protocol into USB


/* matrix size */
#define MATRIX_ROWS     16
#define MATRIX_COLS     8

/* key combination for command */
#define IS_COMMAND()    ( \
    host_get_first_key() == KC_CANCEL \
)


/* PC98 Reset Port shared with TXD */
#define PC98_RST_DDR    DDRD
#define PC98_RST_PORT   PORTD
#define PC98_RST_BIT    3
/* PC98 Ready Port */
#define PC98_RDY_DDR    DDRD
#define PC98_RDY_PORT   PORTD
#define PC98_RDY_BIT    4
/* PC98 Retry Port */
#define PC98_RTY_DDR    DDRD
#define PC98_RTY_PORT   PORTD
#define PC98_RTY_BIT    5

/*
 * PC98 Serial(USART) configuration
 *     asynchronous, positive logic, 19200baud, bit order: LSB first
 *     1-start bit, 8-data bit, odd parity, 1-stop bit
 */
/*
 * Software Serial
 */
#define SERIAL_SOFT_BAUD                19200
#define SERIAL_SOFT_PARITY_ODD
#define SERIAL_SOFT_BIT_ORDER_LSB
#define SERIAL_SOFT_LOGIC_POSITIVE
/* RXD Port */
#define SERIAL_SOFT_RXD_DDR             DDRD
#define SERIAL_SOFT_RXD_PORT            PORTD
#define SERIAL_SOFT_RXD_PIN             PIND
#define SERIAL_SOFT_RXD_BIT             2
#define SERIAL_SOFT_RXD_READ()          (SERIAL_SOFT_RXD_PIN&(1<<SERIAL_SOFT_RXD_BIT))
/* RXD Interupt */
#define SERIAL_SOFT_RXD_VECT            INT2_vect
#define SERIAL_SOFT_RXD_INIT()          do { \
    /* pin configuration: input with pull-up */ \
    SERIAL_SOFT_RXD_DDR &= ~(1<<SERIAL_SOFT_RXD_BIT); \
    SERIAL_SOFT_RXD_PORT |= (1<<SERIAL_SOFT_RXD_BIT); \
    /* enable interrupt: INT2(falling edge) */ \
    EICRA |= ((1<<ISC21)|(0<<ISC20)); \
    EIMSK |= (1<<INT2); \
    sei(); \
} while (0)
#define SERIAL_SOFT_RXD_INT_ENTER()
#define SERIAL_SOFT_RXD_INT_EXIT()      do { \
    /* clear interrupt  flag */ \
    EIFR = (1<<INTF2); \
} while (0)
/* TXD Port */
#define SERIAL_SOFT_TXD_DDR             DDRD
#define SERIAL_SOFT_TXD_PORT            PORTD
#define SERIAL_SOFT_TXD_PIN             PIND
#define SERIAL_SOFT_TXD_BIT             3
#define SERIAL_SOFT_TXD_HI()            do { SERIAL_SOFT_TXD_PORT |=  (1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_LO()            do { SERIAL_SOFT_TXD_PORT &= ~(1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_INIT()          do { \
    /* pin configuration: output */ \
    SERIAL_SOFT_TXD_DDR |= (1<<SERIAL_SOFT_TXD_BIT); \
    /* idle */ \
    SERIAL_SOFT_TXD_ON(); \
} while (0)


/*
 * Hardware Serial(UART)
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


#endif
