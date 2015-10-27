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

#define PORT_SHIFT  5

typedef enum {
    // LPC11U24 HVQFN33 Pin Names
    P0_0 = 0,
    P0_1 = 1,
    P0_2 = 2,
    P0_3 = 3,
    P0_4 = 4,
    P0_5 = 5,
    P0_6 = 6,
    P0_7 = 7,
    P0_8 = 8,
    P0_9 = 9,
    P0_10 = 10,
    P0_11 = 11,
    P0_12 = 12,
    P0_13 = 13,
    P0_14 = 14,
    P0_15 = 15,
    P0_16 = 16,
    P0_17 = 17,
    P0_18 = 18,
    P0_19 = 19,
    P0_20 = 20,
    P0_21 = 21,
    P0_22 = 22,
    P0_23 = 23,

    P1_15 = 47,
    P1_19 = 51,

    // Other mbed Pin Names
    LED1 = P0_7,
    LED2 = P0_8,
    LED3 = P0_2,
    LED4 = P0_20,
    LED5 = P1_19,
    LED6 = P0_17,
    LED7 = P0_23,

    USBTX = P0_19,
    USBRX = P0_18,

    I2C_SCL = P0_4,
    I2C_SDA = P0_5,

    // Not connected
    NC = (int)0xFFFFFFFF,
} PinName;

typedef enum {
    CHANNEL0 = FLEX_INT0_IRQn,
    CHANNEL1 = FLEX_INT1_IRQn,
    CHANNEL2 = FLEX_INT2_IRQn,
    CHANNEL3 = FLEX_INT3_IRQn,
    CHANNEL4 = FLEX_INT4_IRQn,
    CHANNEL5 = FLEX_INT5_IRQn,
    CHANNEL6 = FLEX_INT6_IRQn,
    CHANNEL7 = FLEX_INT7_IRQn
} Channel;

typedef enum {
    PullUp = 2,
    PullDown = 1,
    PullNone = 0,
    Repeater = 3,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
