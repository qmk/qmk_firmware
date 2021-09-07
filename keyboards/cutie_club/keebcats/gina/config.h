/*
Copyright 2021 Cutie Club

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

#include "config_common.h"
#include "mcp23X17/mcp23X17.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFB9C
#define PRODUCT_ID 0x0060
#define DEVICE_VER 0x0000
#define MANUFACTURER Cutie Club
#define PRODUCT Keebcats Gina

#define GPIO_EXPANDER_ADDRESS (0b0100000 << 1)

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Assignments
 */
#define MCP_ROW_PINS { MCP_B4, MCP_A4, MCP_A5, MCP_A6, MCP_A7 }
#define MCP_COL_PINS { MCP_B0, MCP_A3, MCP_A2, MCP_A1, MCP_A0 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
