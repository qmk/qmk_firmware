/* mbed Microcontroller Library
 * Copyright (c) 2006-2014 ARM Limited
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

typedef enum {
    // LPC Pin Names
    P0_0 = 0,
    P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P0_12, P0_13, P0_14, P0_15, P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31,
    P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11, P1_12, P1_13, P1_14, P1_15, P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23, P1_24, P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31,
    P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10, P2_11, P2_12,
    
    LED_RED = P0_25,
    LED_GREEN = P0_3,
    LED_BLUE = P1_1,
    
    // mbed original LED naming
    LED1 = LED_RED,
    LED2 = LED_GREEN,
    LED3 = LED_BLUE,
    LED4 = LED_BLUE,
    
    // Serial to USB pins
    USBTX = P0_18,
    USBRX = P0_13,
    
    // Arduino Shield Receptacles Names
    D0 = P0_13,
    D1 = P0_18,
    D2 = P0_29,
    D3 = P0_9,
    D4 = P0_10,
    D5 = P0_16, // same port as D13
    D6 = P1_3,
    D7 = P0_0,
    D8 = P0_24,
    D9 = P1_0,
    D10= P0_27,
    D11= P0_28,
    D12= P0_12,
    D13= P0_16, // same port as D5
    D14= P0_23,
    D15= P0_22,

    A0 = P0_8,
    A1 = P0_7,
    A2 = P0_6,
    A3 = P0_5,
    A4 = P0_23, // same port as SDA
    A5 = P0_22, // same port as SCL
    SDA= P0_23, // same port as A4
    SCL= P0_22, // same port as A5
    
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
