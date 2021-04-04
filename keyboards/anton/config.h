/* Copyright 2021 Leonez <Leonez@nuaa.edu.cn>
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
#define PRODUCT_ID      0x6324
#define DEVICE_VER      0x0001
#define MANUFACTURER ZHUWENQ
#define PRODUCT ANTON

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { A6, B1, B9, B10, B11, B13, B14, B15, A8, A15, B3, B4, B5, B6, B7, B8 }
#define MATRIX_ROW_PINS { C13, C14, C15, A1, A4, A5 }
#define DIODE_DIRECTION ROW2COL

#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//#defin// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN B12
// The number of LEDs connected
#define DRIVER_LED_TOTAL 84

// limit the brightness of rgb
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170
#define RGB_DISABLE_WHEN_USB_SUSPENDED false


#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT//10
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT//8
#define DISABLE_RGB_MATRIX_BAND_SAT//6
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS//24
#define DISABLE_RGB_MATRIX_RAINDROPS//23
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS//22

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5


