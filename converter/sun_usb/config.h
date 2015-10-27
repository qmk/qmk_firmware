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
#define PRODUCT_ID      0x3333
#define DEVICE_VER      0x0100
#define MANUFACTURER    t.m.k.
#define PRODUCT         Sun keyboard converter
#define DESCRIPTION     converts Sun keyboard protocol into USB

/* matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS 8

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)) || \
    keyboard_report->mods == (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* legacy keymap support */
#define USE_LEGACY_KEYMAP


/* Serial(USART) configuration
 *     asynchronous, negative logic, 1200baud, no flow control
 *     1-start bit, 8-data bit, non parity, 1-stop bit
 */
#define SERIAL_SOFT_BAUD            1200
#define SERIAL_SOFT_PARITY_NONE
#define SERIAL_SOFT_BIT_ORDER_LSB
#define SERIAL_SOFT_LOGIC_NEGATIVE
/* RXD Port */
#define SERIAL_SOFT_RXD_ENABLE
#define SERIAL_SOFT_RXD_DDR         DDRD
#define SERIAL_SOFT_RXD_PORT        PORTD
#define SERIAL_SOFT_RXD_PIN         PIND
#define SERIAL_SOFT_RXD_BIT         2
#define SERIAL_SOFT_RXD_VECT        INT2_vect
/* RXD Interupt */
#ifdef SERIAL_SOFT_LOGIC_NEGATIVE
/* enable interrupt: INT2(rising edge) */
#define INTR_TRIG_EDGE   ((1<<ISC21)|(1<<ISC20))
#else
/* enable interrupt: INT2(falling edge) */
#define INTR_TRIG_EDGE   ((1<<ISC21)|(0<<ISC20))
#endif
#define SERIAL_SOFT_RXD_INIT()      do { \
    /* pin configuration: input with pull-up */ \
    SERIAL_SOFT_RXD_DDR &= ~(1<<SERIAL_SOFT_RXD_BIT); \
    SERIAL_SOFT_RXD_PORT |= (1<<SERIAL_SOFT_RXD_BIT); \
    EICRA |= INTR_TRIG_EDGE; \
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
#define SERIAL_SOFT_TXD_ENABLE
#define SERIAL_SOFT_TXD_DDR         DDRD
#define SERIAL_SOFT_TXD_PORT        PORTD
#define SERIAL_SOFT_TXD_PIN         PIND
#define SERIAL_SOFT_TXD_BIT         3
#define SERIAL_SOFT_TXD_HI()        do { SERIAL_SOFT_TXD_PORT |=  (1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_LO()        do { SERIAL_SOFT_TXD_PORT &= ~(1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_INIT()      do { \
    /* pin configuration: output */ \
    SERIAL_SOFT_TXD_DDR |= (1<<SERIAL_SOFT_TXD_BIT); \
    /* idle */ \
    SERIAL_SOFT_TXD_ON(); \
} while (0)

#endif
