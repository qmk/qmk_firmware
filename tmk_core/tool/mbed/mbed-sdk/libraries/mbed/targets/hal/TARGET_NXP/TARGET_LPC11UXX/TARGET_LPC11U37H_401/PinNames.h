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
    // LPC11U Pin Names
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
    P0_24 = 24,
    P0_25 = 25,
    P0_26 = 26,
    P0_27 = 27,

    P1_0 = 32,
    P1_1 = 33,
    P1_2 = 34,
    P1_3 = 35,
    P1_4 = 36,
    P1_5 = 37,
    P1_6 = 38,
    P1_7 = 39,
    P1_8 = 40,
    P1_9 = 41,
    P1_10 = 42,
    P1_11 = 43,
    P1_12 = 44,
    P1_13 = 45,
    P1_14 = 46,
    P1_15 = 47,
    P1_16 = 48,
    P1_17 = 49,
    P1_18 = 50,
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

    // LED Names
    LED1 = P1_24,
    LED2 = P1_25,
    LED3 = P1_26,
    LED4 = P0_0,
    LED5 = P1_3,
    LED6 = P1_2,
    LED7 = P1_1,
    LED8 = P1_0,

    // BTN Names
    BTN1 = P0_16,
    BTN2 = P0_1,
    
    // UART
    UART_TX = P0_19,
    UART_RX = P0_18,

    // Arduino Shield Receptacles Names
    D0 = P0_18,
    D1 = P0_19,
    D2 = P1_17,
    D3 = P1_24,
    D4 = P1_5,
    D5 = P0_1,
    D6 = P1_27,
    D7 = P0_7,
    D8 = P0_2,
    D9 = P1_25,
    D10= P1_23,
    D11= P0_21,
    D12= P0_22,
    D13= P1_15,
    D14= P0_5,
    D15= P0_4,

    A0 = P0_11,
    A1 = P0_12,
    A2 = P0_13,
    A3 = P0_16,
    A4 = P0_5, // same port as SDA
    A5 = P0_4, // same port as SCL
    
    SDA= P0_5, // same port as A4
    SCL= P0_4, // same port as A5
    
    //SD Card pins
    SDMOSI = P0_9,
    SDMISO = P0_8,
    SDSCLK = P1_29,
    SDSSEL = P1_12,
    
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
