/* Copyright 2019 Neil Kettle
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#ifdef RIGHT_HALF
# include <stdint.h>
# include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md")
# define I2C_ADDR        0b0100000
# define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
# define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
# define IODIRA          0x00            // i/o direction register
# define IODIRB          0x01
# define GPPUA           0x0C            // GPIO pull-up resistor register
# define GPPUB           0x0D
# define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
# define GPIOB           0x13
# define OLATA           0x14            // output latch register
# define OLATB           0x15

extern i2c_status_t mcp23018_status;
# define MCP23018_I2C_TIMEOUT 100

uint8_t init_mcp23018(void);
#endif

#define ___ KC_NO
#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 *
 *  LEFT HAND                                        RIGHT HAND
 * ┌-----┬-----┬-----┬-----┬-----┬-----┬-----┐    ┌-----┬-----┬-----┬-----┬-----┬-----┬----------┐
 * │ L00 │ L01 │ L02 │ L03 │ L04 │ L05 │ L06 │    │ R07 │ R08 │ R09 │ R0A │ R0B │ R0C │ R0D      │
 * ├-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┘ ┌--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬-------┤
 * │ L10    │ L11 │ L12 │ L13 │ L14 │ L15 │    │ R16 │ R17 │ R18 │ R19 │ R1A │ R1B │ R1C │ R1D   │
 * ├--------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴-------┤
 * │ L20     │ L21 │ L22 │ L23 │ L24 │ L25 │    │ R26 │ R27 │ R28 │ R29 │ R2A │ R2B │ R2C        │
 * ├---------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬-----┬-----┤
 * │ L30      │ L31 │ L32 │ L33 │ L34 │ L35 │    │ R36 │ R37 │ R38 │ R39 │ R3A │ R3B │ R3C │ R3D │
 * ├------┬---┴-┬---┴--┬--┴-----┴----┬┴----┬┘   ┌┴-----┴-----┴--┬--┴----┬┴-----┼-----┼-----┼-----┤
 * │ L40  │ L41 │ L42  │ L43         │ L45 │    │ R46           │ R48   │ R4A  │ R4B │ R4C │ R4D │
 * └------┴-----┴------┴-------------┴-----┘    └---------------┴-------┴------┴-----┴-----┴-----┘
 */
#define LAYOUT(                                                      \
    L00, L01, L02, L03, L04, L05, L06,      R07, R08, R09, R0A, R0B, R0C, R0D, \
    L10, L11, L12, L13, L14, L15,      R16, R17, R18, R19, R1A, R1B, R1C, R1D, \
    L20, L21, L22, L23, L24, L25,      R26, R27, R28, R29, R2A, R2B, R2C,      \
    L30, L31, L32, L33, L34, L35,      R36, R37, R38, R39, R3A, R3B, R3C, R3D, \
    L40, L41, L42, L43,      L45,      R46,      R48,      R4A, R4B, R4C, R4D  \
    )                       \
   /* matrix positions */   \
   {                        \
    { ___, ___, ___, ___, ___, ___, ___, R46, R48, R4A, R4B, R4C, R4D, R3D },  \
    { L40, L41, L42, L43, L45, L06, ___, R36, R37, R38, R39, R3A, R3B, R3C },  \
    { L30, L31, L32, L33, L34, L35, ___, R26, R27, R28, R29, R2A, R2B, R2C },  \
    { L20, L21, L22, L23, L24, L25, ___, R17, R18, R19, R1A, R1B, R1C, R1D },  \
    { L10, L11, L12, L13, L14, L15, ___, R07, R08, R09, R0A, R0B, R0C, R0D },  \
    { L00, L01, L02, L03, L04, L05, ___, R16, ___, ___, ___, ___, ___, ___ }   \
   }

