/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

/* key matrix size */
#define MATRIX_ROWS_PER_SIDE 5
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define DIODE_DIRECTION ROW2COL

#define LAYOUT(\
    kc0r0, kc1r0 ,kc2r0, kc3r0, kc4r0, kc5r0 ,kc6r0, kc7r0,\
    kc0r1, kc1r1 ,kc2r1, kc3r1, kc4r1, kc5r1 ,kc6r1, kc7r1,\
    kc0r2, kc1r2 ,kc2r2, kc3r2, kc4r2, kc5r2 ,kc6r2, kc7r2,\
    kc0r3, kc1r3 ,kc2r3, kc3r3, kc4r3, kc5r3 ,kc6r3, kc7r3,\
    kc0r4, kc1r4 ,kc2r4, kc3r4, kc4r4, kc5r4 ,kc6r4, kc7r4 \
  ) { \
    { kc0r0, kc1r0 ,kc2r0, kc3r0, kc4r0, kc5r0 ,kc6r0, kc7r0 }, \
    { kc0r1, kc1r1 ,kc2r1, kc3r1, kc4r1, kc5r1 ,kc6r1, kc7r1 }, \
    { kc0r2, kc1r2 ,kc2r2, kc3r2, kc4r2, kc5r2 ,kc6r2, kc7r2 }, \
    { kc0r3, kc1r3 ,kc2r3, kc3r3, kc4r3, kc5r3 ,kc6r3, kc7r3 }, \
    { kc0r4, kc1r4 ,kc2r4, kc3r4, kc4r4, kc5r4 ,kc6r4, kc7r4 }  \
}

#define SPLIT_LAYOUT(\
    lc0r0, lc1r0 ,lc2r0, lc3r0, lc4r0, lc5r0 ,lc6r0, lc7r0, \
    lc0r1, lc1r1 ,lc2r1, lc3r1, lc4r1, lc5r1 ,lc6r1, lc7r1, \
    lc0r2, lc1r2 ,lc2r2, lc3r2, lc4r2, lc5r2 ,lc6r2, lc7r2, \
    lc0r3, lc1r3 ,lc2r3, lc3r3, lc4r3, lc5r3 ,lc6r3, lc7r3, \
    lc0r4, lc1r4 ,lc2r4, lc3r4, lc4r4, lc5r4 ,lc6r4, lc7r4, \
    rc7r0, rc6r0, rc5r0 ,rc4r0, rc3r0, rc2r0, rc1r0 ,rc0r0, \
    rc7r1, rc6r1, rc5r1 ,rc4r1, rc3r1, rc2r1, rc1r1 ,rc0r1, \
    rc7r2, rc6r2, rc5r2 ,rc4r2, rc3r2, rc2r2, rc1r2 ,rc0r2, \
    rc7r3, rc6r3, rc5r3 ,rc4r3, rc3r3, rc2r3, rc1r3 ,rc0r3, \
    rc7r4, rc6r4, rc5r4 ,rc4r4, rc3r4, rc2r4, rc1r4 ,rc0r4  \
  ) { \
    { rc0r0, rc1r0 ,rc2r0, rc3r0, rc4r0, rc5r0 ,rc6r0, rc7r0 }, \
    { rc0r1, rc1r1 ,rc2r1, rc3r1, rc4r1, rc5r1 ,rc6r1, rc7r1 }, \
    { rc0r2, rc1r2 ,rc2r2, rc3r2, rc4r2, rc5r2 ,rc6r2, rc7r2 }, \
    { rc0r3, rc1r3 ,rc2r3, rc3r3, rc4r3, rc5r3 ,rc6r3, rc7r3 }, \
    { rc0r4, rc1r4 ,rc2r4, rc3r4, rc4r4, rc5r4 ,rc6r4, rc7r4 }, \
    { lc0r0, lc1r0 ,lc2r0, lc3r0, lc4r0, lc5r0 ,lc6r0, lc7r0 }, \
    { lc0r1, lc1r1 ,lc2r1, lc3r1, lc4r1, lc5r1 ,lc6r1, lc7r1 }, \
    { lc0r2, lc1r2 ,lc2r2, lc3r2, lc4r2, lc5r2 ,lc6r2, lc7r2 }, \
    { lc0r3, lc1r3 ,lc2r3, lc3r3, lc4r3, lc5r3 ,lc6r3, lc7r3 }, \
    { lc0r4, lc1r4 ,lc2r4, lc3r4, lc4r4, lc5r4 ,lc6r4, lc7r4 } \
}

#define LAYOUT_TO_INDEX(row, col) ((row)*MATRIX_COLS+(col))

#define RGBLED_NUM       72
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_SPLIT { 36, 36 }
//#define SPLIT_TRANSPORT_MIRROR


//#define RGB_DISABLE_WHEN_USB_SUSPENDED
//#define RGB_DISABLE_TIMEOUT 62000

#define NUM_SHIFT_REGISTERS 5

// Split keyboard
// https://docs.qmk.fm/#/feature_split_keyboard?id=split-keyboard
#define SERIAL_USART_TX_PIN GP5
//#define SERIAL_PIO_USE_PIO1
//#define SPLIT_USB_DETECT
//#define SPLIT_USB_TIMEOUT 2000
//#define SPLIT_USB_TIMEOUT_POLL 10
#define EE_HANDS
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
//#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_POLY_DATA

//see also https://docs.qmk.fm/#/feature_pointing_device?id=split-keyboard-configuration
//#define SPLIT_POINTING_ENABLE
