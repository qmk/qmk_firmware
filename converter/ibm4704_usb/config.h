/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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
#define PRODUCT_ID      0x4707
#define DEVICE_VER      0x0001
#define MANUFACTURER    t.m.k.
#define PRODUCT         IBM 4704 keyboard converter
#define DESCRIPTION     convert IBM 4704 keyboard to USB


/* matrix size */
#define MATRIX_ROWS 16  // keycode bit3-6 
#define MATRIX_COLS 8   // keycode bit0-2


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)



/* Pin configuration */
#define IBM4704_CLOCK_PORT  PORTD
#define IBM4704_CLOCK_PIN   PIND
#define IBM4704_CLOCK_DDR   DDRD
#define IBM4704_CLOCK_BIT   1
#define IBM4704_DATA_PORT   PORTD
#define IBM4704_DATA_PIN    PIND
#define IBM4704_DATA_DDR    DDRD
#define IBM4704_DATA_BIT    0

/* Pin interrupt on rising edge of clock */
#define IBM4704_INT_INIT()  do { EICRA |= ((1<<ISC11)|(1<<ISC10)); } while (0)
#define IBM4704_INT_ON()    do { EIFR |= (1<<INTF1); EIMSK |= (1<<INT1); } while (0)
#define IBM4704_INT_OFF()   do { EIMSK &= ~(1<<INT1); } while (0)
#define IBM4704_INT_VECT    INT1_vect


#endif
