
/* Copyright 2019
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6465
#define DEVICE_VER      0x0001
#define MANUFACTURER    ErgoKB
#define PRODUCT         Phoenix
#define DESCRIPTION     Q.M.K for Phoenix

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 1

#define DIODE_DIRECTION COL2ROW

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define HAL_USE_SERIAL TRUE

#include "config_common.h"
#define MATRIX_COL_PINS { A0 }
#define MATRIX_ROW_PINS { A7 }

#define SPLIT_HAND_PIN B12
#define SOFT_SERIAL_PIN A9
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SPLIT_USB_TIMEOUT 500
