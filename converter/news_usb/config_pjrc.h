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
#define PRODUCT_ID      0x5021
#define MANUFACTURER    t.m.k.
#define PRODUCT         SONY NEWS keyboard converter
#define DESCRIPTION     converts SONY NEWS protocol into USB


/* matrix size */
#define MATRIX_ROWS 16  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4


/* legacy keymap support */
#define USE_LEGACY_KEYMAP


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) || \
    keyboard_report->mods == (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RSHIFT)) \
)


/* Asynchronous USART
 * 8-data bit, non parity, 1-stop bit, no flow control
 */
#ifdef __AVR_ATmega32U4__
#   define NEWS_KBD_RX_VECT        USART1_RX_vect
#   define NEWS_KBD_RX_DATA        UDR1
#   define NEWS_KBD_RX_BAUD        9600
#   define NEWS_KBD_RX_UBBR        ((F_CPU/(16UL*NEWS_KBD_RX_BAUD))-1)
#   define NEWS_KBD_RX_INIT()      do { \
        UBRR1L = (uint8_t) NEWS_KBD_RX_UBBR; \
        UBRR1H = (uint8_t) (NEWS_KBD_RX_UBBR>>8); \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); \
    } while(0)
#else
#   error "USART configuration is needed."
#endif

#endif
