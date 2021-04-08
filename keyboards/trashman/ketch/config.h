/* 
Copyright 2021 Evan Sailer, Jetpacktuxedo, & QMK Firmware

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include "config_common.h"

#define VENDOR_ID     0xFEAE
#define PRODUCT_ID    0x8947
#define DEVICE_VER    0x0001
#define MANUFACTURER  trash man
#define PRODUCT       Ketch

#define MATRIX_ROWS 6
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { F5, F1, F0, F7, B6, F6 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4, D5, D6, D7 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define USB_MAX_POWER_CONSUMPTION 100
#define RGB_DI_PIN F4
#define RGBLED_NUM 10
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define NO_USB_STARTUP_CHECK
