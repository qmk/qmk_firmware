/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
#define MANUFACTURER    homebrew
#define PRODUCT         Santoku
#define DESCRIPTION     compact split keyboard with built-in support for Trackpoints and OLED display

/* diode direction */
#define DIODE_DIRECTION COL2ROW

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_COL_PINS { F1, F0, B6, B2, B3, B1, C7, E6, B7, B5, B4, C6 }
#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define UNUSED_PINS

// Configure the SSD1306OLED display
//#define USE_I2C
#define SSD1306OLED
#define OLED_DISPLAY_128X64

// Configure rotary encoder
#define ENCODERS_PAD_A { D4 }
#define ENCODERS_PAD_B { D7 }
#define ENCODER_RESOLUTION 2

#ifdef PS2_MOUSE_ENABLE
//#define PS2_MOUSE_STREAMING_MODE TRUE

//#define PS2_MOUSE_SCROLL_DIVISOR_H 7
//#define PS2_MOUSE_SCROLL_DIVISOR_V 7	
//#define PS2_MOUSE_SCROLL_BTN_SEND 500 /* Default is 300 */

//#define PS2_MOUSE_X_MULTIPLIER 1
//#define PS2_MOUSE_Y_MULTIPLIER 1
//#define PS2_MOUSE_V_MULTIPLIER 1

#define PS2_MOUSE_SCROLL_BTN_MASK 0
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2

//#define PS2_MOUSE_SCROLL_DIVISOR_H 15	
//#define PS2_MOUSE_SCROLL_DIVISOR_V 15	

#define PS2_MOUSE_INIT_DELAY 1000 /* Default */
#endif

#ifdef PS2_USE_USART

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
#endif


#ifdef PS2_USE_INT
//#define PS2_MOUSE_STREAM_MODE
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

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


#ifdef PS2_USE_ART
//#define PS2_MOUSE_USE_REMOTE_MODE

#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

#endif


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// TODO: Play with this setting. Is this the cause of the crazy Trackpoint cursor after wakeup?
#define LOCKING_RESYNC_ENABLE

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
