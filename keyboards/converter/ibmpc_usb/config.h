/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2016 Priyadi Iman Nurcahyo <priyadi@priyadi.net>

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
#define PRODUCT_ID      0x6536
#define DEVICE_VER      0x0100
#define MANUFACTURER    QMK
#define PRODUCT         PS/2 Keyboard
#define DESCRIPTION     convert IBM PC keyboard to USB


/* matrix size */
#define MATRIX_ROWS 16  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4


/* legacy keymap support */
#define USE_LEGACY_KEYMAP


/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_RALT) | MOD_BIT(KC_RCTL)) \
)

/*
 * Pin and interrupt configuration
 */
/* clock line */
#define IBMPC_CLOCK_PORT  PORTD
#define IBMPC_CLOCK_PIN   PIND
#define IBMPC_CLOCK_DDR   DDRD
#define IBMPC_CLOCK_BIT   1
/* data line */
#define IBMPC_DATA_PORT   PORTD
#define IBMPC_DATA_PIN    PIND
#define IBMPC_DATA_DDR    DDRD
#define IBMPC_DATA_BIT    0
/* reset line */
#define IBMPC_RST_PORT    PORTB
#define IBMPC_RST_PIN     PINB
#define IBMPC_RST_DDR     DDRB
#define IBMPC_RST_BIT1    6
#define IBMPC_RST_BIT2    7

/* reset for XT Type-1 keyboard: low pulse for 500ms */
#define IBMPC_RST_HIZ() do { \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_DDR  &= ~(1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT2);  \
    IBMPC_RST_DDR  &= ~(1<<IBMPC_RST_BIT2);  \
} while (0)

#define IBMPC_RST_LO() do { \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_DDR  |=  (1<<IBMPC_RST_BIT1);  \
    IBMPC_RST_PORT &= ~(1<<IBMPC_RST_BIT2);  \
    IBMPC_RST_DDR  |=  (1<<IBMPC_RST_BIT2);  \
} while (0)

/* interrupt for clock line */
#define IBMPC_INT_INIT()  do {  \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)

/* NOTE: clear flag and enabling to ditch unwanted interrupt */
#define IBMPC_INT_ON()  do {    \
    EIFR  |= (1<<INTF1);        \
    EIMSK |= (1<<INT1);         \
} while (0)

#define IBMPC_INT_OFF() do {    \
    EIMSK &= ~(1<<INT1);        \
} while (0)

#define IBMPC_INT_VECT    INT1_vect

#endif
