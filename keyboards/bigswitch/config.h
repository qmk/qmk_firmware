/*
Copyright 2018 QMK Contributors

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0xB195
#define DEVICE_VER      0x0001
#define MANUFACTURER    flehrad
#define PRODUCT         BigSwitch PCB
#define DESCRIPTION     A single key board for Novelkeys Big Switch

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* key matrix pins */
#define MATRIX_ROW_PINS { B5 }
#define MATRIX_COL_PINS { B6 }
#define UNUSED_PINS { }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 50

/* key combination for command */
#define IS_COMMAND() ( \
    false \
)


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#endif

#endif
