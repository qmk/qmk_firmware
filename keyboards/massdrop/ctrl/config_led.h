/*
Copyright 2018 Massdrop Inc.

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

//Define number of ISSI3733 drivers being used (1...16)
#define ISSI3733_DRIVER_COUNT 2
#define RGB_MATRIX_LED_COUNT ISSI3733_LED_COUNT

//Hardware address of each driver (Refer to ISSI3733 pdf "Table 1 Slave Address" and keyboard schematic)
#define ISSI3773_DRIVER_ADDRESSES { 0xA0, 0xBE }

//LED I2C bus speed
#define I2C_HZ 580000

//Count of LED bodies
#define ISSI3733_LED_COUNT 119

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
#define V5_HIGH                     2540        //5V high level (After low power detect, point at which LEDs are allowed to use more power )
#define V5_LOW                      2480        //5V low level (LED power rolled back to stay above this limit)
#define V5_CAT                      2200        //5V catastrophic level (Host USB port potential to shut down)

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
 { .id = 1, .x = 0, .y = 0, .adr = { .drv = 2, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 0 }, \
 { .id = 2, .x = 1.5, .y = 0, .adr = { .drv = 2, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 1 }, \
 { .id = 3, .x = 2.25, .y = 0, .adr = { .drv = 2, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 2 }, \
 { .id = 4, .x = 3, .y = 0, .adr = { .drv = 2, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 3 }, \
 { .id = 5, .x = 3.75, .y = 0, .adr = { .drv = 2, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 4 }, \
 { .id = 6, .x = 4.875, .y = 0, .adr = { .drv = 2, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 5 }, \
 { .id = 7, .x = 5.625, .y = 0, .adr = { .drv = 2, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 6 }, \
 { .id = 8, .x = 6.375, .y = 0, .adr = { .drv = 1, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 7 }, \
 { .id = 9, .x = 7.125, .y = 0, .adr = { .drv = 1, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 48 }, \
 { .id = 10, .x = 8.25, .y = 0, .adr = { .drv = 1, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 49 }, \
 { .id = 11, .x = 9, .y = 0, .adr = { .drv = 1, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 50 }, \
 { .id = 12, .x = 9.75, .y = 0, .adr = { .drv = 1, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 51 }, \
 { .id = 13, .x = 10.5, .y = 0, .adr = { .drv = 1, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 52 }, \
 { .id = 14, .x = 11.625, .y = 0, .adr = { .drv = 1, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 53 }, \
 { .id = 15, .x = 12.375, .y = 0, .adr = { .drv = 1, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 54 }, \
 { .id = 16, .x = 13.125, .y = 0, .adr = { .drv = 1, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 55 }, \
 { .id = 17, .x = 0, .y = -1.125, .adr = { .drv = 2, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 8 }, \
 { .id = 18, .x = 0.75, .y = -1.125, .adr = { .drv = 2, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 9 }, \
 { .id = 19, .x = 1.5, .y = -1.125, .adr = { .drv = 2, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 10 }, \
 { .id = 20, .x = 2.25, .y = -1.125, .adr = { .drv = 2, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 11 }, \
 { .id = 21, .x = 3, .y = -1.125, .adr = { .drv = 2, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 12 }, \
 { .id = 22, .x = 3.75, .y = -1.125, .adr = { .drv = 2, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 13 }, \
 { .id = 23, .x = 4.5, .y = -1.125, .adr = { .drv = 2, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 14 }, \
 { .id = 24, .x = 5.25, .y = -1.125, .adr = { .drv = 2, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 15 }, \
 { .id = 25, .x = 6, .y = -1.125, .adr = { .drv = 1, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 56 }, \
 { .id = 26, .x = 6.75, .y = -1.125, .adr = { .drv = 1, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 57 }, \
 { .id = 27, .x = 7.5, .y = -1.125, .adr = { .drv = 1, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 58 }, \
 { .id = 28, .x = 8.25, .y = -1.125, .adr = { .drv = 1, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 59 }, \
 { .id = 29, .x = 9, .y = -1.125, .adr = { .drv = 1, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 60 }, \
 { .id = 30, .x = 10.125, .y = -1.125, .adr = { .drv = 1, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 61 }, \
 { .id = 31, .x = 11.625, .y = -1.125, .adr = { .drv = 1, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 62 }, \
 { .id = 32, .x = 12.375, .y = -1.125, .adr = { .drv = 1, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 63 }, \
 { .id = 33, .x = 13.125, .y = -1.125, .adr = { .drv = 1, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 79 }, \
 { .id = 34, .x = 0.188, .y = -1.875, .adr = { .drv = 2, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 16 }, \
 { .id = 35, .x = 1.125, .y = -1.875, .adr = { .drv = 2, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 17 }, \
 { .id = 36, .x = 1.875, .y = -1.875, .adr = { .drv = 2, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 18 }, \
 { .id = 37, .x = 2.625, .y = -1.875, .adr = { .drv = 2, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 19 }, \
 { .id = 38, .x = 3.375, .y = -1.875, .adr = { .drv = 2, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 20 }, \
 { .id = 39, .x = 4.125, .y = -1.875, .adr = { .drv = 2, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 21 }, \
 { .id = 40, .x = 4.875, .y = -1.875, .adr = { .drv = 2, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 22 }, \
 { .id = 41, .x = 5.625, .y = -1.875, .adr = { .drv = 2, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 23 }, \
 { .id = 42, .x = 6.375, .y = -1.875, .adr = { .drv = 1, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 64 }, \
 { .id = 43, .x = 7.125, .y = -1.875, .adr = { .drv = 1, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 65 }, \
 { .id = 44, .x = 7.875, .y = -1.875, .adr = { .drv = 1, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 66 }, \
 { .id = 45, .x = 8.625, .y = -1.875, .adr = { .drv = 1, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 67 }, \
 { .id = 46, .x = 9.375, .y = -1.875, .adr = { .drv = 1, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 68 }, \
 { .id = 47, .x = 10.312, .y = -1.875, .adr = { .drv = 1, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 69 }, \
 { .id = 48, .x = 11.625, .y = -1.875, .adr = { .drv = 1, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 70 }, \
 { .id = 49, .x = 12.375, .y = -1.875, .adr = { .drv = 1, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 71 }, \
 { .id = 50, .x = 13.125, .y = -1.875, .adr = { .drv = 1, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 78 }, \
 { .id = 51, .x = 0.281, .y = -2.625, .adr = { .drv = 2, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 24 }, \
 { .id = 52, .x = 1.313, .y = -2.625, .adr = { .drv = 2, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 25 }, \
 { .id = 53, .x = 2.063, .y = -2.625, .adr = { .drv = 2, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 26 }, \
 { .id = 54, .x = 2.812, .y = -2.625, .adr = { .drv = 2, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 27 }, \
 { .id = 55, .x = 3.562, .y = -2.625, .adr = { .drv = 2, .cs = 11, .swr = 11, .swg = 10, .swb = 12 }, .scan = 28 }, \
 { .id = 56, .x = 4.312, .y = -2.625, .adr = { .drv = 2, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 29 }, \
 { .id = 57, .x = 5.062, .y = -2.625, .adr = { .drv = 2, .cs = 10, .swr = 11, .swg = 10, .swb = 12 }, .scan = 30 }, \
 { .id = 58, .x = 5.812, .y = -2.625, .adr = { .drv = 2, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 31 }, \
 { .id = 59, .x = 6.562, .y = -2.625, .adr = { .drv = 1, .cs = 16, .swr = 11, .swg = 10, .swb = 12 }, .scan = 72 }, \
 { .id = 60, .x = 7.312, .y = -2.625, .adr = { .drv = 1, .cs = 15, .swr = 11, .swg = 10, .swb = 12 }, .scan = 73 }, \
 { .id = 61, .x = 8.062, .y = -2.625, .adr = { .drv = 1, .cs = 14, .swr = 11, .swg = 10, .swb = 12 }, .scan = 74 }, \
 { .id = 62, .x = 8.812, .y = -2.625, .adr = { .drv = 1, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 75 }, \
 { .id = 63, .x = 10.031, .y = -2.625, .adr = { .drv = 1, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 76 }, \
 { .id = 64, .x = 0.469, .y = -3.375, .adr = { .drv = 2, .cs = 14, .swr = 5, .swg = 4, .swb = 6 }, .scan = 32 }, \
 { .id = 65, .x = 1.688, .y = -3.375, .adr = { .drv = 2, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 33 }, \
 { .id = 66, .x = 2.438, .y = -3.375, .adr = { .drv = 2, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 34 }, \
 { .id = 67, .x = 3.188, .y = -3.375, .adr = { .drv = 2, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 35 }, \
 { .id = 68, .x = 3.938, .y = -3.375, .adr = { .drv = 2, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 36 }, \
 { .id = 69, .x = 4.688, .y = -3.375, .adr = { .drv = 2, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 37 }, \
 { .id = 70, .x = 5.438, .y = -3.375, .adr = { .drv = 2, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 38 }, \
 { .id = 71, .x = 6.188, .y = -3.375, .adr = { .drv = 2, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 39 }, \
 { .id = 72, .x = 6.938, .y = -3.375, .adr = { .drv = 1, .cs = 16, .swr = 8, .swg = 7, .swb = 9 }, .scan = 80 }, \
 { .id = 73, .x = 7.688, .y = -3.375, .adr = { .drv = 1, .cs = 15, .swr = 8, .swg = 7, .swb = 9 }, .scan = 81 }, \
 { .id = 74, .x = 8.438, .y = -3.375, .adr = { .drv = 1, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 82 }, \
 { .id = 75, .x = 9.844, .y = -3.375, .adr = { .drv = 1, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 83 }, \
 { .id = 76, .x = 12.375, .y = -3.375, .adr = { .drv = 1, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 77 }, \
 { .id = 77, .x = 0.094, .y = -4.125, .adr = { .drv = 2, .cs = 14, .swr = 11, .swg = 10, .swb = 12 }, .scan = 40 }, \
 { .id = 78, .x = 1.031, .y = -4.125, .adr = { .drv = 2, .cs = 14, .swr = 8, .swg = 7, .swb = 9 }, .scan = 41 }, \
 { .id = 79, .x = 1.969, .y = -4.125, .adr = { .drv = 2, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 42 }, \
 { .id = 80, .x = 4.781, .y = -4.125, .adr = { .drv = 2, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 43 }, \
 { .id = 81, .x = 7.594, .y = -4.125, .adr = { .drv = 1, .cs = 16, .swr = 5, .swg = 4, .swb = 6 }, .scan = 44 }, \
 { .id = 82, .x = 8.531, .y = -4.125, .adr = { .drv = 1, .cs = 15, .swr = 5, .swg = 4, .swb = 6 }, .scan = 45 }, \
 { .id = 83, .x = 9.469, .y = -4.125, .adr = { .drv = 1, .cs = 14, .swr = 5, .swg = 4, .swb = 6 }, .scan = 46 }, \
 { .id = 84, .x = 10.406, .y = -4.125, .adr = { .drv = 1, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 47 }, \
 { .id = 85, .x = 11.625, .y = -4.125, .adr = { .drv = 1, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 84 }, \
 { .id = 86, .x = 12.375, .y = -4.125, .adr = { .drv = 1, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 85 }, \
 { .id = 87, .x = 13.125, .y = -4.125, .adr = { .drv = 1, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 86 }, \
 { .id = 88, .x = 13.433, .y = -4.43, .adr = { .drv = 1, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 89, .x = 12.285, .y = -4.535, .adr = { .drv = 1, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 90, .x = 11.14, .y = -4.535, .adr = { .drv = 1, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 91, .x = 9.995, .y = -4.535, .adr = { .drv = 1, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 92, .x = 8.85, .y = -4.535, .adr = { .drv = 1, .cs = 15, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 93, .x = 7.705, .y = -4.535, .adr = { .drv = 1, .cs = 16, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 94, .x = 6.56, .y = -4.535, .adr = { .drv = 2, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 95, .x = 5.415, .y = -4.535, .adr = { .drv = 2, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 96, .x = 4.27, .y = -4.535, .adr = { .drv = 2, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 97, .x = 3.125, .y = -4.535, .adr = { .drv = 2, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 98, .x = 1.98, .y = -4.535, .adr = { .drv = 2, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 99, .x = 0.835, .y = -4.535, .adr = { .drv = 2, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 100, .x = -0.307, .y = -4.43, .adr = { .drv = 2, .cs = 15, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 101, .x = -0.41, .y = -3.245, .adr = { .drv = 2, .cs = 15, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 102, .x = -0.41, .y = -2.06, .adr = { .drv = 2, .cs = 15, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 103, .x = -0.41, .y = -0.875, .adr = { .drv = 2, .cs = 15, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 104, .x = -0.308, .y = 0.31, .adr = { .drv = 2, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 105, .x = 0.835, .y = 0.415, .adr = { .drv = 2, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 106, .x = 1.98, .y = 0.415, .adr = { .drv = 2, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 107, .x = 3.125, .y = 0.415, .adr = { .drv = 2, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 108, .x = 4.27, .y = 0.415, .adr = { .drv = 2, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 109, .x = 5.415, .y = 0.415, .adr = { .drv = 2, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 110, .x = 6.56, .y = 0.415, .adr = { .drv = 1, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 111, .x = 7.705, .y = 0.415, .adr = { .drv = 1, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 112, .x = 8.85, .y = 0.415, .adr = { .drv = 1, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 113, .x = 9.995, .y = 0.415, .adr = { .drv = 1, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 114, .x = 11.14, .y = 0.415, .adr = { .drv = 1, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 115, .x = 12.285, .y = 0.415, .adr = { .drv = 1, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 116, .x = 13.432, .y = 0.31, .adr = { .drv = 1, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 117, .x = 13.535, .y = -0.875, .adr = { .drv = 1, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }, \
 { .id = 118, .x = 13.535, .y = -2.06, .adr = { .drv = 1, .cs = 10, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 119, .x = 13.535, .y = -3.245, .adr = { .drv = 1, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
};

#define USB_LED_INDICATOR_ENABLE    //Comment out to disable indicator functionality
#ifdef USB_LED_INDICATOR_ENABLE     //Scan codes refer to actual key matrix codes, not KC_* (255 to disable)
    #define USB_LED_NUM_LOCK_SCANCODE       255
    #define USB_LED_CAPS_LOCK_SCANCODE      24
    #define USB_LED_SCROLL_LOCK_SCANCODE    54
    #define USB_LED_COMPOSE_SCANCODE        255
    #define USB_LED_KANA_SCANCODE           255
#endif //USB_LED_INDICATOR_ENABLE
