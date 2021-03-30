/*
Copyright 2021 Leon Anavi <leon@anavi.org>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    ANAVI
#define PRODUCT         Macro Pad 2

/* matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 2

/*
 * Keyboard Matrix Assignments
 *
 * On this board we have direct connection: no diodes.
 */
#define DIRECT_PINS {{ B2, B0 }}

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define BACKLIGHT_PIN B1
#define BACKLIGHT_LEVELS 2
#define RGBLIGHT_SLEEP

//#define RGBLED_NUM 2
//#define RGB_DI_PIN B2

// Save as much space as we can...
#define LAYER_STATE_8BIT
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_RESET

// usbconfig.h overrides
#define USB_CFG_IOPORTNAME B
#define USB_CFG_DMINUS_BIT 3
#define USB_CFG_DPLUS_BIT 4
#define USB_COUNT_SOF 0
#define USB_INTR_CFG PCMSK
#define USB_INTR_CFG_SET (1<<USB_CFG_DPLUS_BIT)
#define USB_INTR_ENABLE_BIT PCIE
#define USB_INTR_PENDING_BIT PCIF
#define USB_INTR_VECTOR SIG_PIN_CHANGE

#define COMBO_COUNT 1
#define COMBO_TERM 500
