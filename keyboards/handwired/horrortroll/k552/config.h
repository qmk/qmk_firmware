/*
Copyright 2021 HorrorTroll

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x7326 //Redragon
#define PRODUCT_ID      0x5104
#define DEVICE_VER      0x0001
#define MANUFACTURER    Redragon
#define PRODUCT         K552 Kumara
#define DESCRIPTION     Handwired K552 Kumara

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

//                         0   1   2   3   4   5   6   7   8   9   10   11   12  13  14  15  16
#define MATRIX_ROW_PINS { C0, C1, C2, C3, C4, C5 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, B0, B1, B13, B14, B15, C6, C7, C8, C9 }

#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define EEPROM_PAGE_SIZE
#define FEE_PAGE_SIZE (uint16_t)0x800
#define FEE_DENSITY_PAGES 4

#define EEPROM_START_ADDRESS
#define FEE_MCU_FLASH_SIZE                              \
({                                                      \
    uint16_t flash_size = *(uint16_t*)FLASHSIZE_BASE;   \
    (flash_size <= 512) ? flash_size : 512;             \
})
