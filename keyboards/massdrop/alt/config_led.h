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

#ifndef _config_led_h_
#define _config_led_h_

//Define number of ISSI3733 drivers being used (1...16)
#define ISSI3733_DRIVER_COUNT 2

//Hardware address of each driver (Refer to ISSI3733 pdf "Table 1 Slave Address" and keyboard schematic)
#define ISSI3773_DRIVER_ADDRESSES { 0xA0, 0xBE }

//LED I2C bus speed
#define I2C_HZ 580000

//Count of LED bodies
#define ISSI3733_LED_COUNT 105

//Default Global Current Register value (Default brightness 0 - 255)
#define ISSI3733_GCR_DEFAULT 128

#define LED_GCR_MAX                 165         //Max GCR value (0 - 255) WARNING: Raising this value may overload the LED drivers and USB bus
#define LED_GCR_STEP                10          //GCR increment/decrement value

//Automatic power rollback and recovery
#define V5_HIGH                     2540        //5V high level (After low power detect, point at which LEDs are allowed to use more power )
#define V5_LOW                      2480        //5V low level (LED power rolled back to stay above this limit)
#define V5_CAT                      2200        //5V catastrophic level (Host USB port potential to shut down)

#define ANIMATION_SPEED_STEP        1

#define BREATHE_MIN_STEP            0
#define BREATHE_MAX_STEP            255

//LED Mapping - More practically generated from a spreadsheet program
//id: ID of the LED (Sync with PCB callouts)
//x: Physical X coordinate of LED (units do not matter)
//y: Physical Y coordinate of LED (units do not matter)
//drv: 1-Based index of ISSI3773_DRIVER_ADDRESSES
//cs: Matrix wiring CS col (1-16)
//swr: Matrix wiring SW Red row (1-12)
//swg: Matrix wiring SW Green row (1-12)
//swb: Matrix wiring SW Blue row (1-12)
//scan: Associated key scancode if any
//Note: Origin 0,0 may be located anywhere as the software will do the final layout
#define ISSI3733_LED_MAP { \
 { .id = 1, .x = 0, .y = 0, .adr = { .drv = 2, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 0 }, \
 { .id = 2, .x = 0.75, .y = 0, .adr = { .drv = 2, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 1 }, \
 { .id = 3, .x = 1.5, .y = 0, .adr = { .drv = 2, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 2 }, \
 { .id = 4, .x = 2.25, .y = 0, .adr = { .drv = 2, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 3 }, \
 { .id = 5, .x = 3, .y = 0, .adr = { .drv = 2, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 4 }, \
 { .id = 6, .x = 3.75, .y = 0, .adr = { .drv = 2, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 5 }, \
 { .id = 7, .x = 4.5, .y = 0, .adr = { .drv = 2, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 6 }, \
 { .id = 8, .x = 5.25, .y = 0, .adr = { .drv = 2, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 7 }, \
 { .id = 9, .x = 6, .y = 0, .adr = { .drv = 1, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 8 }, \
 { .id = 10, .x = 6.75, .y = 0, .adr = { .drv = 1, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 9 }, \
 { .id = 11, .x = 7.5, .y = 0, .adr = { .drv = 1, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 10 }, \
 { .id = 12, .x = 8.25, .y = 0, .adr = { .drv = 1, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 11 }, \
 { .id = 13, .x = 9, .y = 0, .adr = { .drv = 1, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 12 }, \
 { .id = 14, .x = 10.125, .y = 0, .adr = { .drv = 1, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 13 }, \
 { .id = 15, .x = 11.25, .y = 0, .adr = { .drv = 1, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 14 }, \
 { .id = 16, .x = 0.188, .y = -0.75, .adr = { .drv = 2, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 15 }, \
 { .id = 17, .x = 1.125, .y = -0.75, .adr = { .drv = 2, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 16 }, \
 { .id = 18, .x = 1.875, .y = -0.75, .adr = { .drv = 2, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 17 }, \
 { .id = 19, .x = 2.625, .y = -0.75, .adr = { .drv = 2, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 18 }, \
 { .id = 20, .x = 3.375, .y = -0.75, .adr = { .drv = 2, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 19 }, \
 { .id = 21, .x = 4.125, .y = -0.75, .adr = { .drv = 2, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 20 }, \
 { .id = 22, .x = 4.875, .y = -0.75, .adr = { .drv = 2, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 21 }, \
 { .id = 23, .x = 5.625, .y = -0.75, .adr = { .drv = 1, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 22 }, \
 { .id = 24, .x = 6.375, .y = -0.75, .adr = { .drv = 1, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 23 }, \
 { .id = 25, .x = 7.125, .y = -0.75, .adr = { .drv = 1, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 24 }, \
 { .id = 26, .x = 7.875, .y = -0.75, .adr = { .drv = 1, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 25 }, \
 { .id = 27, .x = 8.625, .y = -0.75, .adr = { .drv = 1, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 26 }, \
 { .id = 28, .x = 9.375, .y = -0.75, .adr = { .drv = 1, .cs = 11, .swr = 11, .swg = 10, .swb = 12 }, .scan = 27 }, \
 { .id = 29, .x = 10.313, .y = -0.75, .adr = { .drv = 1, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 28 }, \
 { .id = 30, .x = 11.25, .y = -0.75, .adr = { .drv = 1, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 29 }, \
 { .id = 31, .x = 0.281, .y = -1.5, .adr = { .drv = 2, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 30 }, \
 { .id = 32, .x = 1.313, .y = -1.5, .adr = { .drv = 2, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 31 }, \
 { .id = 33, .x = 2.063, .y = -1.5, .adr = { .drv = 2, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 32 }, \
 { .id = 34, .x = 2.813, .y = -1.5, .adr = { .drv = 2, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 33 }, \
 { .id = 35, .x = 3.563, .y = -1.5, .adr = { .drv = 2, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 34 }, \
 { .id = 36, .x = 4.313, .y = -1.5, .adr = { .drv = 2, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 35 }, \
 { .id = 37, .x = 5.063, .y = -1.5, .adr = { .drv = 2, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 36 }, \
 { .id = 38, .x = 5.813, .y = -1.5, .adr = { .drv = 1, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 37 }, \
 { .id = 39, .x = 6.563, .y = -1.5, .adr = { .drv = 1, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 38 }, \
 { .id = 40, .x = 7.313, .y = -1.5, .adr = { .drv = 1, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 39 }, \
 { .id = 41, .x = 8.063, .y = -1.5, .adr = { .drv = 1, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 40 }, \
 { .id = 42, .x = 8.813, .y = -1.5, .adr = { .drv = 1, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 41 }, \
 { .id = 43, .x = 10.031, .y = -1.5, .adr = { .drv = 1, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 43 }, \
 { .id = 44, .x = 11.25, .y = -1.5, .adr = { .drv = 1, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 44 }, \
 { .id = 45, .x = 0.469, .y = -2.25, .adr = { .drv = 2, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 45 }, \
 { .id = 46, .x = 1.688, .y = -2.25, .adr = { .drv = 2, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 47 }, \
 { .id = 47, .x = 2.438, .y = -2.25, .adr = { .drv = 2, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 48 }, \
 { .id = 48, .x = 3.188, .y = -2.25, .adr = { .drv = 2, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 49 }, \
 { .id = 49, .x = 3.938, .y = -2.25, .adr = { .drv = 2, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 50 }, \
 { .id = 50, .x = 4.688, .y = -2.25, .adr = { .drv = 2, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 51 }, \
 { .id = 51, .x = 5.438, .y = -2.25, .adr = { .drv = 2, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 52 }, \
 { .id = 52, .x = 6.188, .y = -2.25, .adr = { .drv = 1, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 53 }, \
 { .id = 53, .x = 6.938, .y = -2.25, .adr = { .drv = 1, .cs = 10, .swr = 11, .swg = 10, .swb = 12 }, .scan = 54 }, \
 { .id = 54, .x = 7.688, .y = -2.25, .adr = { .drv = 1, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 55 }, \
 { .id = 55, .x = 8.438, .y = -2.25, .adr = { .drv = 1, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 56 }, \
 { .id = 56, .x = 9.469, .y = -2.25, .adr = { .drv = 1, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 57 }, \
 { .id = 57, .x = 10.5, .y = -2.25, .adr = { .drv = 1, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 58 }, \
 { .id = 58, .x = 11.25, .y = -2.25, .adr = { .drv = 1, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 59 }, \
 { .id = 59, .x = 0.094, .y = -3, .adr = { .drv = 2, .cs = 10, .swr = 8, .swg = 7, .swb = 9 }, .scan = 60 }, \
 { .id = 60, .x = 1.031, .y = -3, .adr = { .drv = 2, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 61 }, \
 { .id = 61, .x = 1.969, .y = -3, .adr = { .drv = 2, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 62 }, \
 { .id = 62, .x = 4.781, .y = -3, .adr = { .drv = 2, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 66 }, \
 { .id = 63, .x = 7.594, .y = -3, .adr = { .drv = 1, .cs = 10, .swr = 5, .swg = 4, .swb = 6 }, .scan = 70 }, \
 { .id = 64, .x = 8.531, .y = -3, .adr = { .drv = 1, .cs = 10, .swr = 2, .swg = 1, .swb = 3 }, .scan = 71 }, \
 { .id = 65, .x = 9.75, .y = -3, .adr = { .drv = 1, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 72 }, \
 { .id = 66, .x = 10.5, .y = -3, .adr = { .drv = 1, .cs = 12, .swr = 8, .swg = 7, .swb = 9 }, .scan = 73 }, \
 { .id = 67, .x = 11.25, .y = -3, .adr = { .drv = 1, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 74 }, \
 { .id = 68, .x = -0.338, .y = -3.338, .adr = { .drv = 2, .cs = 11, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 69, .x = 0.39, .y = -3.443, .adr = { .drv = 2, .cs = 11, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 70, .x = 1.263, .y = -3.443, .adr = { .drv = 2, .cs = 11, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 71, .x = 2.135, .y = -3.443, .adr = { .drv = 2, .cs = 11, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 72, .x = 3.008, .y = -3.443, .adr = { .drv = 2, .cs = 12, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 73, .x = 3.88, .y = -3.443, .adr = { .drv = 2, .cs = 12, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 74, .x = 4.753, .y = -3.443, .adr = { .drv = 2, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 75, .x = 5.625, .y = -3.443, .adr = { .drv = 2, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 76, .x = 6.497, .y = -3.443, .adr = { .drv = 1, .cs = 9, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 77, .x = 7.37, .y = -3.443, .adr = { .drv = 1, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 78, .x = 8.242, .y = -3.443, .adr = { .drv = 1, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 79, .x = 9.115, .y = -3.443, .adr = { .drv = 1, .cs = 13, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 80, .x = 9.987, .y = -3.443, .adr = { .drv = 1, .cs = 13, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 81, .x = 10.86, .y = -3.443, .adr = { .drv = 1, .cs = 13, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 82, .x = 11.588, .y = -3.338, .adr = { .drv = 1, .cs = 13, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 83, .x = 11.693, .y = -2.623, .adr = { .drv = 1, .cs = 12, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 84, .x = 11.693, .y = -1.873, .adr = { .drv = 1, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 85, .x = 11.693, .y = -1.123, .adr = { .drv = 1, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 86, .x = 11.693, .y = -0.373, .adr = { .drv = 1, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 87, .x = 11.588, .y = 0.338, .adr = { .drv = 1, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 88, .x = 9.908, .y = 0.443, .adr = { .drv = 1, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 89, .x = 9.288, .y = 0.443, .adr = { .drv = 1, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 90, .x = 8.625, .y = 0.443, .adr = { .drv = 1, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 91, .x = 7.875, .y = 0.443, .adr = { .drv = 1, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 92, .x = 7.125, .y = 0.443, .adr = { .drv = 1, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 93, .x = 6.375, .y = 0.443, .adr = { .drv = 1, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 94, .x = 5.625, .y = 0.443, .adr = { .drv = 1, .cs = 14, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 95, .x = 4.875, .y = 0.443, .adr = { .drv = 2, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 96, .x = 4.125, .y = 0.443, .adr = { .drv = 2, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 97, .x = 3.375, .y = 0.443, .adr = { .drv = 2, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 98, .x = 2.625, .y = 0.443, .adr = { .drv = 2, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 99, .x = 1.875, .y = 0.443, .adr = { .drv = 2, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 100, .x = 1.125, .y = 0.443, .adr = { .drv = 2, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 101, .x = -0.338, .y = 0.338, .adr = { .drv = 2, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 102, .x = -0.443, .y = -0.373, .adr = { .drv = 2, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 103, .x = -0.443, .y = -1.123, .adr = { .drv = 2, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 255 }, \
 { .id = 104, .x = -0.443, .y = -1.873, .adr = { .drv = 2, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 105, .x = -0.443, .y = -2.623, .adr = { .drv = 2, .cs = 10, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
};


#define USB_LED_INDICATOR_ENABLE    //Comment out to disable indicator functionality
#ifdef USB_LED_INDICATOR_ENABLE     //Scan codes refer to actual key matrix codes, not KC_* (255 to disable)
    #define USB_LED_NUM_LOCK_SCANCODE       255
    #define USB_LED_CAPS_LOCK_SCANCODE      30
    #define USB_LED_SCROLL_LOCK_SCANCODE    255
    #define USB_LED_COMPOSE_SCANCODE        255
    #define USB_LED_KANA_SCANCODE           255
#endif //USB_LED_INDICATOR_ENABLE

#endif //_config_led_h_
