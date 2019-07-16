/*
Copyright 2019 Massdrop Inc.

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

//Define number of IS31FL3733 drivers being used (1...16)
#define ISSI3733_DRIVER_COUNT 2
#define DRIVER_LED_TOTAL ISSI3733_LED_COUNT

//Hardware address of each driver (Refer to IS31FL3733 pdf "Table 1 Slave Address" and keyboard schematic)
#define ISSI3773_DRIVER_ADDRESSES { 0xA0, 0xBE }

//LED I2C bus speed
#define I2C_HZ 580000

//Count of LED bodies
#define ISSI3733_LED_COUNT 87

#define LED_GCR_MAX                 165         //Max GCR value (0 - 255) WARNING: Raising this value may overload the LED drivers and USB bus
#define LED_GCR_STEP                10          //GCR increment/decrement value

#ifdef USE_MASSDROP_CONFIGURATOR
#define ANIMATION_SPEED_STEP        1

#define BREATHE_STEP                1
#define BREATHE_MIN_STEP            0
#define BREATHE_MAX_STEP            255
#endif

//Default Global Current Register value (Default brightness 0 - 255)
#define ISSI3733_GCR_DEFAULT LED_GCR_MAX

//Automatic power rollback and recovery
#define V5_HIGH                     2494        //5V high level (After low power detect, point at which LEDs are allowed to use more power )
#define V5_LOW                      2434        //5V low level (LED power rolled back to stay above this limit)
#define V5_CAT                      2206        //5V catastrophic level (Host USB port potential to shut down)

//LED Mapping - More practically generated from a spreadsheet program
//id: ID of the LED (Sync with PCB callouts)
//x: Physical X coordinate of LED (units do not matter)
//y: Physical Y coordinate of LED (units do not matter)
//drv: 1-Based index of ISSI3773_DRIVER_ADDRESSES
//cs: Matrix wiring CS col (1-16)
//swr: Matrix wiring SW Red row (1-12)
//swg: Matrix wiring SW Green row (1-12)
//swb: Matrix wiring SW Blue row (1-12)
//scan: Associated key matrix scancode (set 255 if none or 254 for LED to turn off in alternating mode)
//Note: Origin 0,0 may be located anywhere as the software will do the final layout
#define ISSI3733_LED_MAP { \
 { .id = 1, .x = 0.36, .y = 3.362, .adr = { .drv = 2, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 0 }, \
 { .id = 2, .x = 1.11, .y = 3.362, .adr = { .drv = 2, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 1 }, \
 { .id = 3, .x = 1.86, .y = 3.362, .adr = { .drv = 2, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 2 }, \
 { .id = 4, .x = 2.61, .y = 3.362, .adr = { .drv = 2, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 3 }, \
 { .id = 5, .x = 3.36, .y = 3.362, .adr = { .drv = 2, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 4 }, \
 { .id = 6, .x = 4.11, .y = 3.362, .adr = { .drv = 2, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 5 }, \
 { .id = 7, .x = 4.86, .y = 3.362, .adr = { .drv = 2, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 6 }, \
 { .id = 8, .x = 5.61, .y = 3.362, .adr = { .drv = 1, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 7 }, \
 { .id = 9, .x = 6.36, .y = 3.362, .adr = { .drv = 1, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 8 }, \
 { .id = 10, .x = 7.11, .y = 3.362, .adr = { .drv = 1, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 9 }, \
 { .id = 11, .x = 7.86, .y = 3.362, .adr = { .drv = 1, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 10 }, \
 { .id = 12, .x = 8.61, .y = 3.362, .adr = { .drv = 1, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 11 }, \
 { .id = 13, .x = 9.36, .y = 3.362, .adr = { .drv = 1, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 12 }, \
 { .id = 14, .x = 10.485, .y = 3.362, .adr = { .drv = 1, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 13 }, \
 { .id = 15, .x = 0.548, .y = 2.612, .adr = { .drv = 2, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 14 }, \
 { .id = 16, .x = 1.485, .y = 2.612, .adr = { .drv = 2, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 15 }, \
 { .id = 17, .x = 2.235, .y = 2.612, .adr = { .drv = 2, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 16 }, \
 { .id = 18, .x = 2.985, .y = 2.612, .adr = { .drv = 2, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 17 }, \
 { .id = 19, .x = 3.735, .y = 2.612, .adr = { .drv = 2, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 18 }, \
 { .id = 20, .x = 4.485, .y = 2.612, .adr = { .drv = 2, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 19 }, \
 { .id = 21, .x = 5.235, .y = 2.612, .adr = { .drv = 2, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 20 }, \
 { .id = 22, .x = 5.985, .y = 2.612, .adr = { .drv = 1, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 21 }, \
 { .id = 23, .x = 6.735, .y = 2.612, .adr = { .drv = 1, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 22 }, \
 { .id = 24, .x = 7.485, .y = 2.612, .adr = { .drv = 1, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 23 }, \
 { .id = 25, .x = 8.235, .y = 2.612, .adr = { .drv = 1, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 24 }, \
 { .id = 26, .x = 8.985, .y = 2.612, .adr = { .drv = 1, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 25 }, \
 { .id = 27, .x = 9.735, .y = 2.612, .adr = { .drv = 1, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 26 }, \
 { .id = 28, .x = 10.673, .y = 2.612, .adr = { .drv = 1, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 27 }, \
 { .id = 29, .x = 0.641, .y = 1.862, .adr = { .drv = 2, .cs = 11, .swr = 11, .swg = 10, .swb = 12 }, .scan = 28 }, \
 { .id = 30, .x = 1.673, .y = 1.862, .adr = { .drv = 2, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 29 }, \
 { .id = 31, .x = 2.423, .y = 1.862, .adr = { .drv = 2, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 30 }, \
 { .id = 32, .x = 3.173, .y = 1.862, .adr = { .drv = 2, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 31 }, \
 { .id = 33, .x = 3.923, .y = 1.862, .adr = { .drv = 2, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 32 }, \
 { .id = 34, .x = 4.673, .y = 1.862, .adr = { .drv = 2, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 33 }, \
 { .id = 35, .x = 5.423, .y = 1.862, .adr = { .drv = 2, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 34 }, \
 { .id = 36, .x = 6.173, .y = 1.862, .adr = { .drv = 1, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 35 }, \
 { .id = 37, .x = 6.923, .y = 1.862, .adr = { .drv = 1, .cs = 11, .swr = 11, .swg = 10, .swb = 12 }, .scan = 36 }, \
 { .id = 38, .x = 7.673, .y = 1.862, .adr = { .drv = 1, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 37 }, \
 { .id = 39, .x = 8.423, .y = 1.862, .adr = { .drv = 1, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 38 }, \
 { .id = 40, .x = 9.173, .y = 1.862, .adr = { .drv = 1, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 39 }, \
 { .id = 41, .x = 10.391, .y = 1.862, .adr = { .drv = 1, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 41 }, \
 { .id = 42, .x = 0.829, .y = 1.112, .adr = { .drv = 2, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 42 }, \
 { .id = 43, .x = 2.048, .y = 1.112, .adr = { .drv = 2, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 44 }, \
 { .id = 44, .x = 2.798, .y = 1.112, .adr = { .drv = 2, .cs = 14, .swr = 11, .swg = 10, .swb = 12 }, .scan = 45 }, \
 { .id = 45, .x = 3.548, .y = 1.112, .adr = { .drv = 2, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 46 }, \
 { .id = 46, .x = 4.298, .y = 1.112, .adr = { .drv = 2, .cs = 16, .swr = 8, .swg = 7, .swb = 9 }, .scan = 47 }, \
 { .id = 47, .x = 5.048, .y = 1.112, .adr = { .drv = 2, .cs = 16, .swr = 11, .swg = 10, .swb = 12 }, .scan = 48 }, \
 { .id = 48, .x = 5.798, .y = 1.112, .adr = { .drv = 1, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 49 }, \
 { .id = 49, .x = 6.548, .y = 1.112, .adr = { .drv = 1, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 50 }, \
 { .id = 50, .x = 7.298, .y = 1.112, .adr = { .drv = 1, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 51 }, \
 { .id = 51, .x = 8.048, .y = 1.112, .adr = { .drv = 1, .cs = 14, .swr = 11, .swg = 10, .swb = 12 }, .scan = 52 }, \
 { .id = 52, .x = 8.798, .y = 1.112, .adr = { .drv = 1, .cs = 16, .swr = 11, .swg = 10, .swb = 12 }, .scan = 53 }, \
 { .id = 53, .x = 10.204, .y = 1.112, .adr = { .drv = 1, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 55 }, \
 { .id = 54, .x = 0.454, .y = 0.362, .adr = { .drv = 2, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 56 }, \
 { .id = 55, .x = 1.391, .y = 0.362, .adr = { .drv = 2, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 57 }, \
 { .id = 56, .x = 2.329, .y = 0.362, .adr = { .drv = 2, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 58 }, \
 { .id = 57, .x = 5.141, .y = 0.362, .adr = { .drv = 2, .cs = 16, .swr = 2, .swg = 1, .swb = 3 }, .scan = 62 }, \
 { .id = 58, .x = 7.954, .y = 0.362, .adr = { .drv = 1, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 66 }, \
 { .id = 59, .x = 8.891, .y = 0.362, .adr = { .drv = 1, .cs = 16, .swr = 2, .swg = 1, .swb = 3 }, .scan = 67 }, \
 { .id = 60, .x = 9.829, .y = 0.362, .adr = { .drv = 1, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 68 }, \
 { .id = 61, .x = 10.766, .y = 0.362, .adr = { .drv = 1, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 69 }, \
 { .id = 62, .x = 0.74, .y = 3, .adr = { .drv = 2, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 63, .x = 1.714, .y = 3, .adr = { .drv = 2, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 64, .x = 2.688, .y = 3, .adr = { .drv = 2, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 65, .x = 3.662, .y = 3, .adr = { .drv = 2, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 66, .x = 4.636, .y = 3, .adr = { .drv = 2, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 67, .x = 5.61, .y = 3, .adr = { .drv = 1, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 68, .x = 6.584, .y = 3, .adr = { .drv = 1, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 69, .x = 7.558, .y = 3, .adr = { .drv = 1, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 70, .x = 8.532, .y = 3, .adr = { .drv = 1, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 71, .x = 9.506, .y = 3, .adr = { .drv = 1, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 72, .x = 10.48, .y = 3, .adr = { .drv = 1, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 73, .x = 0.74, .y = 0.74, .adr = { .drv = 2, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 74, .x = 1.714, .y = 0.74, .adr = { .drv = 2, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 75, .x = 2.688, .y = 0.74, .adr = { .drv = 2, .cs = 14, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 76, .x = 3.662, .y = 0.74, .adr = { .drv = 2, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 77, .x = 4.636, .y = 0.74, .adr = { .drv = 2, .cs = 16, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 78, .x = 5.61, .y = 0.74, .adr = { .drv = 1, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 79, .x = 6.584, .y = 0.74, .adr = { .drv = 1, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 80, .x = 7.558, .y = 0.74, .adr = { .drv = 1, .cs = 14, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 81, .x = 8.532, .y = 0.74, .adr = { .drv = 1, .cs = 16, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 82, .x = 9.506, .y = 0.74, .adr = { .drv = 1, .cs = 16, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 83, .x = 10.48, .y = 0.74, .adr = { .drv = 1, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 84, .x = 0.74, .y = 2.25, .adr = { .drv = 2, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 85, .x = 0.74, .y = 1.5, .adr = { .drv = 2, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 86, .x = 10.48, .y = 2.25, .adr = { .drv = 1, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 87, .x = 10.48, .y = 1.5, .adr = { .drv = 1, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
};

#define USB_LED_INDICATOR_ENABLE    //Comment out to disable indicator functionality
#ifdef USB_LED_INDICATOR_ENABLE     //Scan codes refer to actual key matrix codes, not KC_* (255 to disable)
    #define USB_LED_NUM_LOCK_SCANCODE       255
    #define USB_LED_CAPS_LOCK_SCANCODE      28
    #define USB_LED_SCROLL_LOCK_SCANCODE    21
    #define USB_LED_COMPOSE_SCANCODE        255
    #define USB_LED_KANA_SCANCODE           255
#endif //USB_LED_INDICATOR_ENABLE
