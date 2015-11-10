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

#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x4242
#define DEVICE_VER      0x0104
#define MANUFACTURER    t.m.k.
#define PRODUCT         HHKB mod
#define DESCRIPTION     t.m.k. keyboard firmware for HHKB mod


/* matrix size */
#ifdef HHKB_JP
#   define MATRIX_ROWS 16
#else
#   define MATRIX_ROWS 8
#endif
#define MATRIX_COLS 8


/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) 


/* period of tapping(ms) */
#define TAPPING_TERM    300
/* tap count needed for toggling a feature */
#define TAPPING_TOGGLE  5
/* Oneshot timeout(ms) */
#define ONESHOT_TIMEOUT 300

/* Boot Magic salt key: Space */
#define BOOTMAGIC_KEY_SALT      KC_SPACE

/* power control of key switch board */
#define HHKB_POWER_SAVING

/*
 * Hardware Serial(UART)
 *     Baud rate are calculated with round off(+0.5).
 */
#ifdef __AVR_ATmega32U4__
    /* iom32u4.h has no definition of UCSR1D. copy from iom32u2.h */
    #define UCSR1D _SFR_MEM8(0xCB)
    #define RTSEN 0
    #define CTSEN 1

    #define SERIAL_UART_BAUD        115200
    #define SERIAL_UART_DATA        UDR1
    #define SERIAL_UART_UBRR        ((F_CPU/(16.0*SERIAL_UART_BAUD)-1+0.5))
    #define SERIAL_UART_RXD_VECT    USART1_RX_vect
    #define SERIAL_UART_TXD_READY   (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()      do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = ((uint16_t)SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); /* RX interrupt, RX: enable */ \
        UCSR1B |= (0<<TXCIE1) | (1<<TXEN1); /* TX interrupt, TX: enable */ \
        UCSR1C |= (0<<UPM11) | (0<<UPM10);  /* parity: none(00), even(01), odd(11) */ \
        UCSR1D |= (0<<RTSEN) | (0<<CTSEN);  /* RTS, CTS(no flow control by hardware) */ \
        DDRD |= (1<<5); PORTD &= ~(1<<5);   /* RTS for flow control by firmware */ \
        sei(); \
    } while(0)
    #define SERIAL_UART_RTS_LO()    do { PORTD &= ~(1<<5); } while (0)
    #define SERIAL_UART_RTS_HI()    do { PORTD |=  (1<<5); } while (0)
#else
    #error "USART configuration is needed."
#endif


/* for debug */
#define SUART_OUT_PORT  PORTD
#define SUART_OUT_BIT   0
#define SUART_IN_PIN    PIND
#define SUART_IN_BIT    1


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
