/*
Copyright 2022 an_achronism (@an-achronism)

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
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define WS2812_PIO_USE_PIO1 // Use PIO1 on Pi Pico for RGB LEDs
#define RGB_DI_PIN GP26 // Use GPIO26 (pin 31) for LED matrix logic
#define DRIVER_LED_TOTAL 70
/* The following line is now specified in info.json under the rgblight struct,
so has been moved there instead: */
// #define RGBLED_NUM 70
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
