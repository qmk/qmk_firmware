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

typedef enum {
    P0_0 = 0,
    P0_1 = 1,
    P0_2 = 2,
    P0_3 = 3,
    P0_4 = 4,
    P0_5 = 5,
    
    dp1 = P0_5,
    dp2 = P0_4,
    dp3 = P0_3,
    dp4 = P0_2,
    dp5 = P0_1,
    dp8 = P0_0,
    
    // mbed original LED naming
    LED1 = P0_2,
    LED2 = P0_2,
    LED3 = P0_2,
    LED4 = P0_2,
    LED_RED = P0_2,
    
    // Serial to USB pins
    USBTX = P0_4,
    USBRX = P0_0,
    
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
