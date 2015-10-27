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

/* PCR - 0x1000 */
#define PORT_SHIFT  12

typedef enum {
    PTA0 = 0x0,
    PTA1 = 0x4,
    PTA2 = 0x8,
    PTA3 = 0xc,
    PTA4 = 0x10,
    PTA5 = 0x14,
    PTA6 = 0x18,
    PTA7 = 0x1c,
    PTA8 = 0x20,
    PTA9 = 0x24,
    PTA10 = 0x28,
    PTA11 = 0x2c,
    PTA12 = 0x30,
    PTA13 = 0x34,
    PTA14 = 0x38,
    PTA15 = 0x3c,
    PTA16 = 0x40,
    PTA17 = 0x44,
    PTA18 = 0x48,
    PTA19 = 0x4c,
    PTB0 = 0x1000,
    PTB1 = 0x1004,
    PTB2 = 0x1008,
    PTB3 = 0x100c,
    PTB4 = 0x1010,
    PTB5 = 0x1014,
    PTB6 = 0x1018,
    PTB7 = 0x101c,
    PTB8 = 0x1020,
    PTB9 = 0x1024,
    PTB10 = 0x1028,
    PTB11 = 0x102c,
    PTB12 = 0x1030,
    PTB13 = 0x1034,
    PTB14 = 0x1038,
    PTB15 = 0x103c,
    PTB16 = 0x1040,
    PTB17 = 0x1044,
    PTB18 = 0x1048,
    PTB19 = 0x104c,
    PTB20 = 0x1050,

    LED_RED   = PTB8,
    LED_GREEN = PTB9,
    LED_BLUE  = PTB10,

    // mbed original LED naming
    LED1 = LED_RED,
    LED2 = LED_GREEN,
    LED3 = LED_BLUE,
    LED4 = LED_BLUE,

    // USB Pins
    USBTX = PTB1,
    USBRX = PTB2,

    // Arduino Headers
    D0 = PTB2,
    D1 = PTB1,
    D2 = PTA11,
    D3 = PTB5,
    D4 = PTA10,
    D5 = PTA12,
    D6 = PTB6,
    D7 = PTB7,
    D8 = PTB10,
    D9 = PTB11,
    D10 = PTA5,
    D11 = PTA7,
    D12 = PTA6,
    D13 = PTB0,
    D14 = PTB4,
    D15 = PTB3,

    A0 = PTB8,
    A1 = PTB9,
    A2 = PTA8,
    A3 = PTA0,
    A4 = PTA9,
    A5 = PTB13,

    I2C_SCL = D15,
    I2C_SDA = D14,

    TSI_ELEC0 = PTA13,
    TSI_ELEC1 = PTB12,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

/* PullDown not available for KL05 */
typedef enum {
    PullNone = 0,
    PullUp   = 2,
    PullDefault = PullUp
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
