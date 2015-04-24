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

#define PORT_SHIFT  4

typedef enum {
    P0_0 = 0,
          P0_1, P0_2, P0_3, P0_4, P0_5,_P0_6,_P0_7,_P0_8,_P0_9,_P0_10,_P0_11,_P0_12,_P0_13,_P0_14,_P0_15,
    P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11, P1_12, P1_13, P1_14, P1_15, 
    P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10, P2_11, P2_12, P2_13, P2_14, P2_15, 
    P3_0, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7, P3_8, P3_9, P3_10, P3_11, P3_12, P3_13, P3_14, P3_15, 
    P4_0, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7, P4_8, P4_9, P4_10, P4_11, P4_12, P4_13, P4_14, P4_15, 
    P5_0, P5_1, P5_2, P5_3, P5_4, P5_5, P5_6, P5_7, P5_8, P5_9, P5_10, P5_11, P5_12, P5_13, P5_14, P5_15, 
    P6_0, P6_1, P6_2, P6_3, P6_4, P6_5, P6_6, P6_7, P6_8, P6_9, P6_10, P6_11, P6_12, P6_13, P6_14, P6_15, 
    P7_0, P7_1, P7_2, P7_3, P7_4, P7_5, P7_6, P7_7, P7_8, P7_9, P7_10, P7_11, P7_12, P7_13, P7_14, P7_15, 
    P8_0, P8_1, P8_2, P8_3, P8_4, P8_5, P8_6, P8_7, P8_8, P8_9, P8_10, P8_11, P8_12, P8_13, P8_14, P8_15, 
    P9_0, P9_1, P9_2, P9_3, P9_4, P9_5, P9_6, P9_7, P9_8, P9_9, P9_10, P9_11, P9_12, P9_13, P9_14, P9_15, 
    P10_0,P10_1,P10_2,P10_3,P10_4,P10_5,P10_6,P10_7,P10_8,P10_9,P10_10,P10_11,P10_12,P10_13,P10_14,P10_15,
    P11_0,P11_1,P11_2,P11_3,P11_4,P11_5,P11_6,P11_7,P11_8,P11_9,P11_10,P11_11,P11_12,P11_13,P11_14,P11_15, 

    // mbed Pin Names
    LED1 = P6_13,
    LED2 = P6_14,
    LED3 = P6_15,
    LED4 = P6_12,

    LED_RED  = LED1,
    LED_GREEN= LED2,
    LED_BLUE = LED3,
    LED_USER = LED4,

    USBTX = P6_3,
    USBRX = P6_2,

    // Arduiono Pin Names
    D0 = P2_15,
    D1 = P2_14,
    D2 = P4_7,
    D3 = P4_6,
    D4 = P4_5,
    D5 = P4_4,
    D6 = P8_13,
    D7 = P8_11,
    D8 = P8_15,
    D9 = P8_14,
    D10 = P10_13,
    D11 = P10_14,
    D12 = P10_15,
    D13 = P10_12,
    D14 = P1_3,
    D15 = P1_2,

    A0 = P1_8,
    A1 = P1_9,
    A2 = P1_10,
    A3 = P1_11,
    A4 = P1_13,
    A5 = P1_15,

    I2C_SCL = D15,
    I2C_SDA = D14,

    USER_BUTTON0 = P6_0,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

#define PINGROUP(pin) (((pin)>>PORT_SHIFT)&0x0f)
#define PINNO(pin) ((pin)&0x0f)

#ifdef __cplusplus
}
#endif

#endif
