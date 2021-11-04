 /* Copyright 2021 Wizad-GG
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

#include "config_common.h"

#define VENDOR_ID    0x4A4B
#define PRODUCT_ID   0xEF6A
#define DEVICE_VER   0x0001
#define MANUFACTURER JadooKB
#define PRODUCT      JKB65 RGB

#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { E6, B7, F7, F4, F5 }
#define MATRIX_COL_PINS { F6,B1,F1,C7,C6,B6,B5,B4,D7,B3,D4,D5,D3,D2,D1,D0 }

#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN F0

#define DRIVER_LED_TOTAL 67

#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_TIMEOUT 90000


#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
