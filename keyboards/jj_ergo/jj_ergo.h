/*
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

#include "quantum.h"

#ifdef RIGHT_HALF
# include <stdint.h>
# include "i2c_master.h"

# define I2C_ADDR        0b0100000
# define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
# define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
# define IODIRA          0x00
# define IODIRB          0x01
# define GPPUA           0x0C
# define GPPUB           0x0D
# define GPIOA           0x12
# define GPIOB           0x13
# define OLATA           0x14
# define OLATB           0x15

extern i2c_status_t mcp23018_status;
# define MCP23018_I2C_TIMEOUT 100

uint8_t init_mcp23018(void);
#endif

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 *
 *  LEFT HAND                                                                                          RIGHT HAND
 *
 * ,--------------------------------------------------.       ,--------------------------------------------------.
 * |  L00   | L01  | L02  | L03  | L04  | L05  | L06  |       | R00  | R01  | R02  | R03  | R04  | R05  | R06    |
 * |--------+------+------+------+------+-------------|       |------+------+------+------+------+------+--------|
 * |  L10   | L11  | L12  | L13  | L14  | L15  | L16  |       | R10  | R11  | R12  | R13  | R14  | R15  | R16    |
 * |--------+------+------+------+------+------|      |       |      |------+------+------+------+------+--------|
 * |  L20   | L21  | L22  | L23  | L24  | L25  |------|       |------| R21  | R22  | R23  | R24  | R25  | R26    |
 * |--------+------+------+------+------+------| L36  |       | R30  |------+------+------+------+------+--------|
 * |  L30   | L31  | L32  | L33  | L34  | L35  |      |       |      | R31  | R32  | R33  | R34  | R35  | R36    |
 * `--------+------+------+------+------+-------------'       `-------------+------+------+------+------+--------'
 *   | L40  | L41  | L42  | L43  | L44  |                                   | R42  | R43  | R44  | R45  | R46  |
 *   `----------------------------------'                                   `----------------------------------'
 *                                        ,-------------.   ,-------------.
 *                                        | L55  | L56  |   | R50  |  R51   |
 *                                 ,------|------|------|   |------+--------+------.
 *                                 |      |      | L54  |   | R52  |        |      |
 *                                 | L53  | L52  |------|   |------|  R54   | R53  |
 *                                 |      |      | L51  |   | R55  |        |      |
 *                                 `--------------------'   `----------------------'
 */

#define LAYOUT(                                                                                 \
                           L00,L01,L02,L03,L04,L05,L06,        R00,R01,R02,R03,R04,R05,R06,     \
                           L10,L11,L12,L13,L14,L15,L16,        R10,R11,R12,R13,R14,R15,R16,     \
                           L20,L21,L22,L23,L24,L25,                R21,R22,R23,R24,R25,R26,     \
                           L30,L31,L32,L33,L34,L35,L36,        R30,R31,R32,R33,R34,R35,R36,     \
                           L40,L41,L42,L43,L44,                        R42,R43,R44,R45,R46,     \
                                               L55,L56,        R50,R51,                         \
                                                   L54,        R52,                             \
                                           L53,L52,L51,        R55,R54,R53                      \
  )                                                                                             \
{                                                                                               \
   {                    ___,___,L56,L51,L54,___,L55,          R06,R05,R04,R03,R02,R01,R00    }, \
   {                    L00,L01,L02,L03,L04,L05,L06,          R16,R15,R14,R13,R12,R11,R10    }, \
   {                    L10,L11,L12,L13,L14,L15,L16,          R26,R25,R24,R23,R22,R21,___    }, \
   {                    L20,L21,L22,L23,L24,L25,___,          R36,R35,R34,R33,R32,R31,R30    }, \
   {                    L30,L31,L32,L33,L34,L35,L36,          R46,R45,R44,R43,R42,R53,R54    }, \
   {                    L40,L41,L42,L43,L44,L53,L52,          ___,___,R55,R50,R52,___,R51    }  \
}
