/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#ifndef __config_H
#define __config_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1818      
#define PRODUCT_ID      0x1233
#define DEVICE_VER      0x0001
#define MANUFACTURER    Fungo
#define PRODUCT         FungoSplit




/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

#define SOFT_SERIAL_PIN D3	// RX8

/* select main board  - usb를 박을 곳 지정*/
//#define SPLIT_HAND_PIN  D0
//#define SPLIT_HAND_PIN_LOW_IS_LEFT
#define MASTER_RIGHT
//#define MASTER_LEFT
// #define EE_HANDS
//#define FLIP_HALF



/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2}
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5}
//#define MATRIX_COL_PINS_LEFT { F4, F5, F6, F7, B1, B3, B2}
//#define MATRIX_ROW_PINS_LEFT { D4, C6, D7, E6, B4, B5}
#define MATRIX_COL_PINS_RIGHT {F7, F6, F5, F4, B5, B4, E6}
#define MATRIX_ROW_PINS_RIGHT { D1, D0, D4, C6, D7, D3}    	// TX   


/* 왼쪽으로 연결하면 이상없음
#ifdef MASTER_RIGHT
   #define MATRIX_COL_PINS { E6, B4, B5, F4, F5, F6, F7}
   #define MATRIX_ROW_PINS { D1, D0, D4, C6, D7, D3}

// split type pin 
   #define MATRIX_COL_PINS_RIGHT { E6, B4, B5, F4, F5, F6, F7}
   #define MATRIX_ROW_PINS_RIGHT { D1, D0, D4, C6, D7, D3}    	// TX   

   //뒤집어줌
   //#define MATRIX_COL_PINS_LEFT { B2, B3, B1, F7, F6, F5, F4}
   #define MATRIX_COL_PINS_LEFT { F4, F5, F6, F7, B1, B3, B2}
   //#define MATRIX_ROW_PINS_LEFT { B5, B4, E6, D7, C6, D4}   
   #define MATRIX_ROW_PINS_LEFT { D4, C6, D7, E6, B4, B5}
#endif

#ifdef MASTER_LEFT
   #define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2}
   #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5}

   // split type pin  -  안뒤집어줌
   #define MATRIX_COL_PINS_LEFT { F4, F5, F6, F7, B1, B3, B2}
   #define MATRIX_ROW_PINS_LEFT { D4, C6, D7, E6, B4, B5}

   #define MATRIX_COL_PINS_RIGHT { E6, B4, B5, F4, F5, F6, F7}
   #define MATRIX_ROW_PINS_RIGHT { D1, D0, D4, C6, D7, D3}

#endif
*/

/* ps2 mouse track point */

/*
#ifdef PS2_USE_INT
#define PS2_CLOCK_PIN   B1
#define PS2_DATA_PIN    B3

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
} while (0)
#define PS2_INT_VECT   INT2_vect
#endif

#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
*/

/*
#ifdef PS2_USE_INT
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    B3

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT1);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT1);        \
} while (0)
#define PS2_INT_VECT   INT1_vect
#endif
*/


/*
#ifdef PS2_USE_USART
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

// synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge
// set DDR of CLOCK as input to be slave
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
#endif

*/

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW



/*************************************/
/**       public parameter       **/
/*************************************/

#define MATRIX_IO_DELAY 15  // default  30
//#define QMK_KEYS_PER_SCAN 4
#define TAP_CODE_DELAY  50   // default 100
#define USB_POLLING_INTERVAL_MS   5 // default 10

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//지정된 횟수로 눌러야 토글됨
#define TAPPING_TOGGLE 3

//tap or holding
#define TAPPING_TERM 200
//#define HOLD_ON_OTHER_KEY_PRESS
//#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT   // ROLLING PRESS?
//#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
//#define TAPPING_FORCE_HOLD
//#define TAPPING_FORCE_HOLD_PER_KEY
//#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
//#define HOLD_ON_OTHER_KEY_PRESS
//#define PERMISSIVE_HOLD


//#define DEBUG_MATRIX_SCAN_RATE



#define MK_3_SPEED
#define MOUSEKEY_INTERVAL 3
#define MOUSEKEY_INITIAL_SPEED	20

#endif