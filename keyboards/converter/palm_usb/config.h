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

/* This code makes use of cy384's Arduino USB HID adapter for the Palm Portable
 Keyboard, released under the BSD licence */




#pragma once

// IO pins to serial
// https://deskthority.net/wiki/Arduino_Pro_Micro for pin lookup
#define VCC_PIN D1 // pro micro 2
#define RX_PIN   D0 //pro micro 3 , was 8 on cy384
#define RTS_PIN  C6 // 5  //[ was D4 // 4 on the cy384
#define DCD_PIN  E6  //7

// if using the particular arduino pinout of CY384
#ifdef CY384
    #define GND_PIN  D7 //6
    #define PULLDOWN_PIN  B1 // 15
#endif

#ifndef HANDSPRING
// Set to 1 for Handspring or to disable RTS/DCD based handshake.
    #define HANDSPRING 0
#endif

#define MAXDROP 10 // check if keyboard is connected every X polling cycles
#define SLEEP_TIMEOUT 500000 // check keyboard/reset this many millis


#define MATRIX_ROWS 12
#define MATRIX_COLS 8

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)) || \
    get_mods() == (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)) || \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
