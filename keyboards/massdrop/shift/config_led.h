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
#define ISSI3733_DRIVER_COUNT 3
#define DRIVER_LED_TOTAL ISSI3733_LED_COUNT

//Hardware address of each driver (Refer to IS31FL3733 pdf "Table 1 Slave Address" and keyboard schematic)
#define ISSI3773_DRIVER_ADDRESSES { 0xA0, 0xBE, 0xA6 }

//LED I2C bus speed
#define I2C_HZ 870000

//Count of LED bodies
#define ISSI3733_LED_COUNT 160

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
 { .id = 1, .x = 0.474, .y = 5.162, .adr = { .drv = 1, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 0 }, \
 { .id = 2, .x = 1.974, .y = 5.162, .adr = { .drv = 1, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 1 }, \
 { .id = 3, .x = 2.724, .y = 5.162, .adr = { .drv = 1, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 2 }, \
 { .id = 4, .x = 3.474, .y = 5.162, .adr = { .drv = 1, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 18 }, \
 { .id = 5, .x = 4.224, .y = 5.162, .adr = { .drv = 1, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 3 }, \
 { .id = 6, .x = 5.349, .y = 5.162, .adr = { .drv = 1, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 4 }, \
 { .id = 7, .x = 6.099, .y = 5.162, .adr = { .drv = 1, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 5 }, \
 { .id = 8, .x = 6.849, .y = 5.162, .adr = { .drv = 1, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 6 }, \
 { .id = 9, .x = 7.599, .y = 5.162, .adr = { .drv = 1, .cs = 10, .swr = 11, .swg = 10, .swb = 12 }, .scan = 22 }, \
 { .id = 10, .x = 8.724, .y = 5.162, .adr = { .drv = 2, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 7 }, \
 { .id = 11, .x = 9.474, .y = 5.162, .adr = { .drv = 2, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 23 }, \
 { .id = 12, .x = 10.224, .y = 5.162, .adr = { .drv = 2, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 8 }, \
 { .id = 13, .x = 10.974, .y = 5.162, .adr = { .drv = 2, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 24 }, \
 { .id = 14, .x = 12.099, .y = 5.162, .adr = { .drv = 2, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 9 }, \
 { .id = 15, .x = 12.849, .y = 5.162, .adr = { .drv = 2, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 10 }, \
 { .id = 16, .x = 13.599, .y = 5.162, .adr = { .drv = 2, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 11 }, \
 { .id = 17, .x = 14.349, .y = 5.162, .adr = { .drv = 2, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 12 }, \
 { .id = 18, .x = 12.099, .y = 4.412, .adr = { .drv = 2, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 25 }, \
 { .id = 19, .x = 12.849, .y = 4.412, .adr = { .drv = 2, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 26 }, \
 { .id = 20, .x = 13.599, .y = 4.412, .adr = { .drv = 2, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 27 }, \
 { .id = 21, .x = 14.349, .y = 4.412, .adr = { .drv = 2, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 28 }, \
 { .id = 22, .x = 0.474, .y = 3.662, .adr = { .drv = 1, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 16 }, \
 { .id = 23, .x = 1.224, .y = 3.662, .adr = { .drv = 1, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 17 }, \
 { .id = 24, .x = 1.974, .y = 3.662, .adr = { .drv = 1, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 33 }, \
 { .id = 25, .x = 2.724, .y = 3.662, .adr = { .drv = 1, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 34 }, \
 { .id = 26, .x = 3.474, .y = 3.662, .adr = { .drv = 1, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 50 }, \
 { .id = 27, .x = 4.224, .y = 3.662, .adr = { .drv = 1, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 19 }, \
 { .id = 28, .x = 4.974, .y = 3.662, .adr = { .drv = 1, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 35 }, \
 { .id = 29, .x = 5.724, .y = 3.662, .adr = { .drv = 1, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 20 }, \
 { .id = 30, .x = 6.474, .y = 3.662, .adr = { .drv = 1, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 21 }, \
 { .id = 31, .x = 7.224, .y = 3.662, .adr = { .drv = 1, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 37 }, \
 { .id = 32, .x = 7.974, .y = 3.662, .adr = { .drv = 1, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 38 }, \
 { .id = 33, .x = 8.724, .y = 3.662, .adr = { .drv = 2, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 54 }, \
 { .id = 34, .x = 9.474, .y = 3.662, .adr = { .drv = 2, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 39 }, \
 { .id = 35, .x = 10.599, .y = 3.662, .adr = { .drv = 2, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 40 }, \
 { .id = 36, .x = 12.099, .y = 3.662, .adr = { .drv = 2, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 41 }, \
 { .id = 37, .x = 12.849, .y = 3.662, .adr = { .drv = 2, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 42 }, \
 { .id = 38, .x = 13.599, .y = 3.662, .adr = { .drv = 2, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 43 }, \
 { .id = 39, .x = 14.349, .y = 3.662, .adr = { .drv = 2, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 44 }, \
 { .id = 40, .x = 0.662, .y = 2.912, .adr = { .drv = 1, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 32 }, \
 { .id = 41, .x = 1.599, .y = 2.912, .adr = { .drv = 1, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 49 }, \
 { .id = 42, .x = 2.349, .y = 2.912, .adr = { .drv = 1, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 65 }, \
 { .id = 43, .x = 3.099, .y = 2.912, .adr = { .drv = 1, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 66 }, \
 { .id = 44, .x = 3.849, .y = 2.912, .adr = { .drv = 1, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 51 }, \
 { .id = 45, .x = 4.599, .y = 2.912, .adr = { .drv = 1, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 67 }, \
 { .id = 46, .x = 5.349, .y = 2.912, .adr = { .drv = 1, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 36 }, \
 { .id = 47, .x = 6.099, .y = 2.912, .adr = { .drv = 1, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 52 }, \
 { .id = 48, .x = 6.849, .y = 2.912, .adr = { .drv = 1, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 53 }, \
 { .id = 49, .x = 7.599, .y = 2.912, .adr = { .drv = 1, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 69 }, \
 { .id = 50, .x = 8.349, .y = 2.912, .adr = { .drv = 2, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 70 }, \
 { .id = 51, .x = 9.099, .y = 2.912, .adr = { .drv = 2, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 55 }, \
 { .id = 52, .x = 9.849, .y = 2.912, .adr = { .drv = 2, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 56 }, \
 { .id = 53, .x = 10.787, .y = 2.912, .adr = { .drv = 2, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 72 }, \
 { .id = 54, .x = 12.099, .y = 2.912, .adr = { .drv = 2, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 57 }, \
 { .id = 55, .x = 12.849, .y = 2.912, .adr = { .drv = 2, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 58 }, \
 { .id = 56, .x = 13.599, .y = 2.912, .adr = { .drv = 2, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 59 }, \
 { .id = 57, .x = 14.349, .y = 2.912, .adr = { .drv = 2, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 60 }, \
 { .id = 58, .x = 0.756, .y = 2.162, .adr = { .drv = 1, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 48 }, \
 { .id = 59, .x = 1.787, .y = 2.162, .adr = { .drv = 1, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 81 }, \
 { .id = 60, .x = 2.537, .y = 2.162, .adr = { .drv = 1, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 97 }, \
 { .id = 61, .x = 3.287, .y = 2.162, .adr = { .drv = 1, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 82 }, \
 { .id = 62, .x = 4.037, .y = 2.162, .adr = { .drv = 1, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 83 }, \
 { .id = 63, .x = 4.787, .y = 2.162, .adr = { .drv = 1, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 99 }, \
 { .id = 64, .x = 5.537, .y = 2.162, .adr = { .drv = 1, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 68 }, \
 { .id = 65, .x = 6.287, .y = 2.162, .adr = { .drv = 1, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 84 }, \
 { .id = 66, .x = 7.037, .y = 2.162, .adr = { .drv = 1, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 85 }, \
 { .id = 67, .x = 7.787, .y = 2.162, .adr = { .drv = 1, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 86 }, \
 { .id = 68, .x = 8.537, .y = 2.162, .adr = { .drv = 2, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 71 }, \
 { .id = 69, .x = 9.287, .y = 2.162, .adr = { .drv = 2, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 88 }, \
 { .id = 70, .x = 10.506, .y = 2.162, .adr = { .drv = 2, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 104 }, \
 { .id = 71, .x = 12.099, .y = 2.162, .adr = { .drv = 2, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 73 }, \
 { .id = 72, .x = 12.849, .y = 2.162, .adr = { .drv = 2, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 74 }, \
 { .id = 73, .x = 13.599, .y = 2.162, .adr = { .drv = 2, .cs = 15, .swr = 2, .swg = 1, .swb = 3 }, .scan = 75 }, \
 { .id = 74, .x = 14.349, .y = 2.162, .adr = { .drv = 2, .cs = 16, .swr = 2, .swg = 1, .swb = 3 }, .scan = 76 }, \
 { .id = 75, .x = 0.943, .y = 1.412, .adr = { .drv = 1, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 64 }, \
 { .id = 76, .x = 2.162, .y = 1.412, .adr = { .drv = 1, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 113 }, \
 { .id = 77, .x = 2.912, .y = 1.412, .adr = { .drv = 1, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 98 }, \
 { .id = 78, .x = 3.662, .y = 1.412, .adr = { .drv = 1, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 114 }, \
 { .id = 79, .x = 4.412, .y = 1.412, .adr = { .drv = 1, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 115 }, \
 { .id = 80, .x = 5.162, .y = 1.412, .adr = { .drv = 1, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 100 }, \
 { .id = 81, .x = 5.912, .y = 1.412, .adr = { .drv = 1, .cs = 15, .swr = 5, .swg = 4, .swb = 6 }, .scan = 117 }, \
 { .id = 82, .x = 6.662, .y = 1.412, .adr = { .drv = 1, .cs = 15, .swr = 2, .swg = 1, .swb = 3 }, .scan = 101 }, \
 { .id = 83, .x = 7.414, .y = 1.41, .adr = { .drv = 1, .cs = 16, .swr = 2, .swg = 1, .swb = 3 }, .scan = 102 }, \
 { .id = 84, .x = 8.162, .y = 1.412, .adr = { .drv = 2, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 87 }, \
 { .id = 85, .x = 8.912, .y = 1.412, .adr = { .drv = 2, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 103 }, \
 { .id = 86, .x = 9.943, .y = 1.412, .adr = { .drv = 2, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 120 }, \
 { .id = 87, .x = 12.099, .y = 1.412, .adr = { .drv = 2, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 89 }, \
 { .id = 88, .x = 12.849, .y = 1.412, .adr = { .drv = 2, .cs = 14, .swr = 5, .swg = 4, .swb = 6 }, .scan = 90 }, \
 { .id = 89, .x = 13.599, .y = 1.412, .adr = { .drv = 2, .cs = 15, .swr = 5, .swg = 4, .swb = 6 }, .scan = 91 }, \
 { .id = 90, .x = 11.162, .y = 1.224, .adr = { .drv = 2, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 105 }, \
 { .id = 91, .x = 14.349, .y = 1.037, .adr = { .drv = 2, .cs = 16, .swr = 8, .swg = 7, .swb = 9 }, .scan = 92 }, \
 { .id = 92, .x = 0.568, .y = 0.662, .adr = { .drv = 1, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 80 }, \
 { .id = 93, .x = 1.506, .y = 0.662, .adr = { .drv = 1, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 96 }, \
 { .id = 94, .x = 2.443, .y = 0.662, .adr = { .drv = 1, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 112 }, \
 { .id = 95, .x = 5.256, .y = 0.662, .adr = { .drv = 1, .cs = 14, .swr = 5, .swg = 4, .swb = 6 }, .scan = 116 }, \
 { .id = 96, .x = 8.162, .y = 0.662, .adr = { .drv = 2, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 118 }, \
 { .id = 97, .x = 9.287, .y = 0.662, .adr = { .drv = 2, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 119 }, \
 { .id = 98, .x = 12.849, .y = 0.662, .adr = { .drv = 2, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 107 }, \
 { .id = 99, .x = 13.599, .y = 0.662, .adr = { .drv = 2, .cs = 15, .swr = 8, .swg = 7, .swb = 9 }, .scan = 108 }, \
 { .id = 100, .x = 10.412, .y = 0.474, .adr = { .drv = 2, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 121 }, \
 { .id = 101, .x = 11.162, .y = 0.474, .adr = { .drv = 2, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 122 }, \
 { .id = 102, .x = 11.912, .y = 0.474, .adr = { .drv = 2, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 106 }, \
 { .id = 103, .x = 0.168, .y = 5.468, .adr = { .drv = 3, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 104, .x = 0.827, .y = 5.571, .adr = { .drv = 3, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 105, .x = 2.144, .y = 5.571, .adr = { .drv = 3, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 106, .x = 2.802, .y = 5.571, .adr = { .drv = 3, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 107, .x = 3.461, .y = 5.571, .adr = { .drv = 3, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 108, .x = 4.119, .y = 5.571, .adr = { .drv = 3, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 109, .x = 4.778, .y = 5.571, .adr = { .drv = 3, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 110, .x = 5.436, .y = 5.571, .adr = { .drv = 3, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 111, .x = 6.095, .y = 5.571, .adr = { .drv = 3, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 112, .x = 6.753, .y = 5.571, .adr = { .drv = 3, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 113, .x = 7.412, .y = 5.571, .adr = { .drv = 3, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 114, .x = 8.07, .y = 5.571, .adr = { .drv = 3, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 115, .x = 8.729, .y = 5.571, .adr = { .drv = 3, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 116, .x = 9.387, .y = 5.571, .adr = { .drv = 3, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 117, .x = 10.046, .y = 5.571, .adr = { .drv = 3, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 118, .x = 10.704, .y = 5.571, .adr = { .drv = 3, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 119, .x = 11.363, .y = 5.571, .adr = { .drv = 3, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 120, .x = 12.021, .y = 5.571, .adr = { .drv = 3, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 121, .x = 12.68, .y = 5.571, .adr = { .drv = 3, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 122, .x = 13.997, .y = 5.571, .adr = { .drv = 3, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 123, .x = 14.656, .y = 5.468, .adr = { .drv = 3, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 124, .x = 14.759, .y = 4.806, .adr = { .drv = 3, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 125, .x = 14.759, .y = 4.143, .adr = { .drv = 3, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 126, .x = 14.759, .y = 3.481, .adr = { .drv = 3, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 127, .x = 14.759, .y = 2.818, .adr = { .drv = 3, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 128, .x = 14.759, .y = 2.156, .adr = { .drv = 3, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 129, .x = 14.759, .y = 1.493, .adr = { .drv = 3, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 130, .x = 14.759, .y = 0.831, .adr = { .drv = 3, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 131, .x = 14.656, .y = 0.168, .adr = { .drv = 3, .cs = 14, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 132, .x = 13.997, .y = 0.065, .adr = { .drv = 3, .cs = 11, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 133, .x = 13.338, .y = 0.065, .adr = { .drv = 3, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 134, .x = 12.68, .y = 0.065, .adr = { .drv = 3, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 135, .x = 12.021, .y = 0.065, .adr = { .drv = 3, .cs = 10, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 136, .x = 11.363, .y = 0.065, .adr = { .drv = 3, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 137, .x = 10.704, .y = 0.065, .adr = { .drv = 3, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 138, .x = 10.046, .y = 0.065, .adr = { .drv = 3, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 139, .x = 9.387, .y = 0.065, .adr = { .drv = 3, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 140, .x = 8.729, .y = 0.065, .adr = { .drv = 3, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 141, .x = 8.07, .y = 0.065, .adr = { .drv = 3, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 142, .x = 7.412, .y = 0.065, .adr = { .drv = 3, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 143, .x = 6.753, .y = 0.065, .adr = { .drv = 3, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 144, .x = 6.095, .y = 0.065, .adr = { .drv = 3, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 145, .x = 5.436, .y = 0.065, .adr = { .drv = 3, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 146, .x = 4.778, .y = 0.065, .adr = { .drv = 3, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 147, .x = 4.119, .y = 0.065, .adr = { .drv = 3, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 148, .x = 3.461, .y = 0.065, .adr = { .drv = 3, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 149, .x = 2.802, .y = 0.065, .adr = { .drv = 3, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 150, .x = 2.144, .y = 0.065, .adr = { .drv = 3, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 151, .x = 1.485, .y = 0.065, .adr = { .drv = 3, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 152, .x = 0.827, .y = 0.065, .adr = { .drv = 3, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 153, .x = 0.168, .y = 0.168, .adr = { .drv = 3, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 154, .x = 0.065, .y = 0.831, .adr = { .drv = 3, .cs = 15, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 155, .x = 0.065, .y = 1.493, .adr = { .drv = 3, .cs = 15, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 156, .x = 0.065, .y = 2.156, .adr = { .drv = 3, .cs = 15, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 157, .x = 0.065, .y = 2.818, .adr = { .drv = 3, .cs = 15, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 158, .x = 0.065, .y = 3.481, .adr = { .drv = 3, .cs = 16, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 159, .x = 0.065, .y = 4.143, .adr = { .drv = 3, .cs = 16, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 160, .x = 0.065, .y = 4.806, .adr = { .drv = 3, .cs = 16, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 } \
};

#define USB_LED_INDICATOR_ENABLE    //Comment out to disable indicator functionality
#ifdef USB_LED_INDICATOR_ENABLE     //Scan codes refer to actual key matrix codes, not KC_* (255 to disable)
    #define USB_LED_NUM_LOCK_SCANCODE       41
    #define USB_LED_CAPS_LOCK_SCANCODE      48
    #define USB_LED_SCROLL_LOCK_SCANCODE    28
    #define USB_LED_COMPOSE_SCANCODE        255
    #define USB_LED_KANA_SCANCODE           255
#endif //USB_LED_INDICATOR_ENABLE
