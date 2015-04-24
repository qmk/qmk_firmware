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
    // LPC1347 Pin Names
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

    P1_13 = 45,
    P1_14 = 46,
    P1_15 = 47,
    P1_16 = 48,

    P1_19 = 51,
    P1_20 = 52,
    P1_21 = 53,
    P1_22 = 54,
    P1_23 = 55,
    P1_24 = 56,
    P1_25 = 57,
    P1_26 = 58,
    P1_27 = 59,
    P1_28 = 60,
    P1_29 = 61,

    P1_31 = 63,

    // DIP Pin Names
    p1  = P0_0,
    p2  = P0_11,
    p3  = P0_12,
    p4  = P0_13,
    p5  = P0_14,
    p6  = P1_31,
    p8  = P0_16,
    p9  = P0_22,
    p10 = P0_23,
    p13 = P1_29,
    p14 = P1_21,
    p15 = P0_8,
    p16 = P0_9,
    p17 = P1_24,
    p18 = P0_4,
    p19 = P1_13,
    p20 = P1_14,
    p21 = P1_22,
    p22 = P0_17,
    p23 = P0_5,
    p24 = P0_21,
    p25 = P0_19,
    p26 = P0_18,
    p27 = P1_15,
    p28 = P1_16,
    p29 = P1_25,
    p30 = P1_19,
    p33 = P0_20,
    p34 = P0_2,
    p35 = P1_26,
    p36 = P1_27,
    p37 = P1_20,
    p38 = P1_23,
    p39 = P0_7,
    p40 = P1_28,

    UART_TX = P0_19,
    UART_RX = P0_18,

    // Not connected
    NC = (int)0xFFFFFFFF,

    LED1 = p21,
    LED2 = p21,
    LED3 = p21,
    LED4 = p21,

    // Standard but not supported pins
    USBTX = NC,
    USBRX = NC,

} PinName;

typedef enum {
    CHANNEL0 = PIN_INT0_IRQn,
    CHANNEL1 = PIN_INT1_IRQn,
    CHANNEL2 = PIN_INT2_IRQn,
    CHANNEL3 = PIN_INT3_IRQn,
    CHANNEL4 = PIN_INT4_IRQn,
    CHANNEL5 = PIN_INT5_IRQn,
    CHANNEL6 = PIN_INT6_IRQn,
    CHANNEL7 = PIN_INT7_IRQn
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
