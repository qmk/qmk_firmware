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

#pragma once


/* key matrix size */
#define MATRIX_COLS  6
#define MATRIX_ROWS  9

/* default pin-out */
#define MATRIX_COL_PINS \
    { F4, F1, F0, D6, D0, D1 }
#define MATRIX_ROW_PINS \
    { F5, F6, F7, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }
#define TRACKPOINT_PINS \
    { B7, B6, D7 }

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define DIODE_DIRECTION      COL2ROW

/* key combination for command */
#define IS_COMMAND()         (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)))


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define PS2_MOUSE_INIT_DELAY 2000

#ifndef __ASSEMBLER__  // assembler doesn't like enum in .h file
enum led_sequence {
    LED_IND_LINUX,
    LED_IND_APPLE,
    LED_IND_WINDOWS,
    LED_IND_QWERTY,
    LED_IND_ALT,
    LED_IND_AUDIO,
    LED_IND_BLUETOOTH,
    LED_IND_USB,

    LED_IND_BATTERY,
    LED_IND_CAPSLOCK,
    LED_IND_GUI,
    LED_IND_FUN,
    LED_IND_NUM,
    LED_IND_PUNC,
    LED_IND_EMOJI,
    LED_IND_GREEK,

    LED_BKSP,
    LED_ENT,
    LED_RSFT,
    LED_RCTL,

    LED_RALT,
    LED_SLSH,
    LED_SCLN,
    LED_P,

    LED_O,
    LED_L,
    LED_DOT,
    LED_RGUI,

    LED_GREEK,
    LED_COMM,
    LED_K,
    LED_I,

    LED_U,
    LED_J,
    LED_M,
    LED_FUN,

    LED_RSPC,
    LED_N,
    LED_HH,
    LED_Y,

    LED_TRACKPOINT3,
    LED_TRACKPOINT2,
    LED_TRACKPOINT1,

    LED_T,
    LED_G,
    LED_B,
    LED_LSPC,

    LED_NUM,
    LED_V,
    LED_F,
    LED_R,

    LED_E,
    LED_D,
    LED_C,
    LED_EMPTY,

    LED_LGUI,
    LED_X,
    LED_S,
    LED_W,

    LED_Q,
    LED_A,
    LED_Z,
    LED_LALT,

    LED_LCTL,
    LED_LSFT,
    LED_ESC,
    LED_TAB,

    LED_TOTAL
};

#    define RGBSPS_NUM LED_TOTAL
#    define WS2812_LED_COUNT RGBSPS_NUM
#endif

/* PS/2 mouse */
#ifdef PS2_DRIVER_BUSYWAIT
#    define PS2_CLOCK_PIN  D3
#    define PS2_DATA_PIN   D2
#endif

/* PS/2 mouse interrupt version */
#ifdef PS2_DRIVER_INTERRUPT
/* uses INT1 for clock line(ATMega32U4) */
#    define PS2_CLOCK_PIN  D3
#    define PS2_DATA_PIN   D2

#    define PS2_INT_INIT()                          \
        do {                                        \
            EICRA |= ((1 << ISC31) | (0 << ISC30)); \
        } while (0)
#    define PS2_INT_ON()          \
        do {                      \
            EIMSK |= (1 << INT3); \
        } while (0)
#    define PS2_INT_OFF()          \
        do {                       \
            EIMSK &= ~(1 << INT3); \
        } while (0)
#    define PS2_INT_VECT INT3_vect
#endif

/* PS/2 mouse USART version */
#ifdef PS2_DRIVER_USART
/* XCK for clock line and RXD for data line */
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#    define PS2_USART_INIT()                                                                         \
        do {                                                                                         \
            PS2_CLOCK_DDR &= ~(1 << PS2_CLOCK_BIT);                                                  \
            PS2_DATA_DDR &= ~(1 << PS2_DATA_BIT);                                                    \
            UCSR1C = ((1 << UMSEL10) | (3 << UPM10) | (0 << USBS1) | (3 << UCSZ10) | (0 << UCPOL1)); \
            UCSR1A = 0;                                                                              \
            UBRR1H = 0;                                                                              \
            UBRR1L = 0;                                                                              \
        } while (0)
#    define PS2_USART_RX_INT_ON()                    \
        do {                                         \
            UCSR1B = ((1 << RXCIE1) | (1 << RXEN1)); \
        } while (0)
#    define PS2_USART_RX_POLL_ON() \
        do {                       \
            UCSR1B = (1 << RXEN1); \
        } while (0)
#    define PS2_USART_OFF()                           \
        do {                                          \
            UCSR1C = 0;                               \
            UCSR1B &= ~((1 << RXEN1) | (1 << TXEN1)); \
        } while (0)
#    define PS2_USART_RX_READY (UCSR1A & (1 << RXC1))
#    define PS2_USART_RX_DATA  UDR1
#    define PS2_USART_ERROR    (UCSR1A & ((1 << FE1) | (1 << DOR1) | (1 << UPE1)))
#    define PS2_USART_RX_VECT  USART1_RX_vect
#endif
