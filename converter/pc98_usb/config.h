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
#define MATRIX_ROWS 16
#define MATRIX_COLS 8


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)) || \
    keyboard_report->mods == (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


/* PC98 Serial(USART) configuration
 *     asynchronous, positive logic, 19200baud, bit order: LSB first
 *     1-start bit, 8-data bit, odd parity, 1-stop bit
 */
#define SERIAL_BAUD 19200
#define SERIAL_PARITY_ODD
#define SERIAL_BIT_ORDER_LSB

/* PC98 Reset Port */
#define PC98_RST_DDR    DDRD
#define PC98_RST_PORT   PORTD
#define PC98_RST_BIT    1
/* PC98 Ready Port */
#define PC98_RDY_DDR    DDRD
#define PC98_RDY_PORT   PORTD
#define PC98_RDY_BIT    4
/* PC98 Retry Port */
#define PC98_RTY_DDR    DDRD
#define PC98_RTY_PORT   PORTD
#define PC98_RTY_BIT    5

/* RXD Port */
#define SERIAL_RXD_DDR  DDRD
#define SERIAL_RXD_PORT PORTD
#define SERIAL_RXD_PIN  PIND
#define SERIAL_RXD_BIT  2
#define SERIAL_RXD_READ()       (SERIAL_RXD_PIN&(1<<SERIAL_RXD_BIT))
/* RXD Interupt */
#define SERIAL_RXD_VECT INT2_vect
#define SERIAL_RXD_INIT()  do { \
    /* pin configuration: input with pull-up */ \
    SERIAL_RXD_DDR &= ~(1<<SERIAL_RXD_BIT);     \
    SERIAL_RXD_PORT |= (1<<SERIAL_RXD_BIT);     \
    /* enable interrupt: INT2(falling edge) */  \
    EICRA |= ((1<<ISC21)|(0<<ISC20));           \
    EIMSK |= (1<<INT2);                         \
} while (0)
#define SERIAL_RXD_INT_ENTER()
#define SERIAL_RXD_INT_EXIT() do {  \
    /* clear interrupt  flag */     \
    EIFR = (1<<INTF2);              \
} while (0)

/* TXD Port: Not used */
#define SERIAL_TXD_DDR  DDRD
#define SERIAL_TXD_PORT PORTD
#define SERIAL_TXD_PIN  PIND
#define SERIAL_TXD_BIT  3
/* negative logic */
#define SERIAL_TXD_ON()     do { SERIAL_TXD_PORT &= ~(1<<SERIAL_TXD_BIT); } while (0)
#define SERIAL_TXD_OFF()    do { SERIAL_TXD_PORT |=  (1<<SERIAL_TXD_BIT); } while (0)
#define SERIAL_TXD_INIT()   do { \
    /* pin configuration: output */         \
    SERIAL_TXD_DDR |= (1<<SERIAL_TXD_BIT);  \
    /* idle */                              \
    SERIAL_TXD_ON();                        \
} while (0)

#endif
