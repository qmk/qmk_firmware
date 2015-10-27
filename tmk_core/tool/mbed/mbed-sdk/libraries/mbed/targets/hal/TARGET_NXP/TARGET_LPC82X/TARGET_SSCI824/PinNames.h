/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PIN_SHIFT 8

typedef enum {
// LPC824 Pin Names (PIN[11:8] + IOCON offset[7:0])

    P0_0  = ( 0 << PIN_SHIFT) | 0x44,
    P0_1  = ( 1 << PIN_SHIFT) | 0x2C,
    P0_2  = ( 2 << PIN_SHIFT) | 0x18,
    P0_3  = ( 3 << PIN_SHIFT) | 0x14,
    P0_4  = ( 4 << PIN_SHIFT) | 0x10,
    P0_5  = ( 5 << PIN_SHIFT) | 0x0C,
    P0_6  = ( 6 << PIN_SHIFT) | 0x40,
    P0_7  = ( 7 << PIN_SHIFT) | 0x3C,
    P0_8  = ( 8 << PIN_SHIFT) | 0x38,
    P0_9  = ( 9 << PIN_SHIFT) | 0x34,
    P0_10 = (10 << PIN_SHIFT) | 0x20,
    P0_11 = (11 << PIN_SHIFT) | 0x1C,
    P0_12 = (12 << PIN_SHIFT) | 0x08,
    P0_13 = (13 << PIN_SHIFT) | 0x04,
    P0_14 = (14 << PIN_SHIFT) | 0x48,
    P0_15 = (15 << PIN_SHIFT) | 0x28,
    P0_16 = (16 << PIN_SHIFT) | 0x24,
    P0_17 = (17 << PIN_SHIFT) | 0x00,
    P0_18 = (18 << PIN_SHIFT) | 0x78,
    P0_19 = (19 << PIN_SHIFT) | 0x74,
    P0_20 = (20 << PIN_SHIFT) | 0x70,
    P0_21 = (21 << PIN_SHIFT) | 0x6C,
    P0_22 = (22 << PIN_SHIFT) | 0x68,
    P0_23 = (23 << PIN_SHIFT) | 0x64,
    P0_24 = (24 << PIN_SHIFT) | 0x60,
    P0_25 = (25 << PIN_SHIFT) | 0x5C,
    P0_26 = (26 << PIN_SHIFT) | 0x58,
    P0_27 = (27 << PIN_SHIFT) | 0x54,
    P0_28 = (28 << PIN_SHIFT) | 0x50,
    
    dp2 = P0_4,
    dp3 = P0_28,
    dp4 = P0_11,
    dp5 = P0_10,
    dp6 = P0_16,
    dp7 = P0_27,
    dp8 = P0_26,
    dp9 = P0_25,
    dp10 = P0_24,
    dp11 = P0_15,
    dp12 = P0_1,
    
    dp15 = P0_6,
    dp16 = P0_0,
    dp17 = P0_14,
    dp18 = P0_23,
    dp19 = P0_22,
    dp20 = P0_21,
    dp21 = P0_20,
    dp22 = P0_19,
    dp23 = P0_17,
    dp24 = P0_13,
    dp25 = P0_12,
    dp26 = P0_5,
    
    LED_RED = P0_20,
    LED_GREEN = P0_21,
    LED_BLUE = P0_22,
    
    // mbed original LED naming
    LED1 = LED_RED,
    LED2 = LED_GREEN,
    LED3 = LED_BLUE,
    LED4 = LED_BLUE,
    
    // Serial to USB pins
    USBTX = P0_7,
    USBRX = P0_18,
    
    // I2C pins
    SCL = P0_10,
    SDA = P0_11,
    I2C_SCL = P0_10,
    I2C_SDA = P0_11,
    
    // Not connected
    NC = (int)0xFFFFFFFF,
} PinName;

typedef enum {
    PullUp = 2,
    PullDown = 1,
    PullNone = 0,
    Repeater = 3,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX

typedef struct {
    unsigned char n;
    unsigned char offset;
} SWM_Map;

#ifdef __cplusplus
}
#endif

#endif
