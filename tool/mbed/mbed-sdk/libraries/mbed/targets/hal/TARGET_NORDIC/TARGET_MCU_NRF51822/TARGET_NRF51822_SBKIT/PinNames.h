/* mbed Microcontroller Library
 * Copyright (c) 2013 Nordic Semiconductor
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

#define PORT_SHIFT  3

typedef enum {
    p0  = 0,
    p1  = 1,
    p2  = 2,
    p3  = 3,
    p5  = 5,
    p8  = 8,
    p9  = 9,
    p11 = 11,
    p12 = 12,
    p15 = 15,
    p16 = 16,
    p18 = 18,
    p20 = 20,
    p21 = 21,
    p24 = 24,

    P0_0  = p0,
    P0_1  = p1,
    P0_2  = p2,
    P0_3  = p3,
    P0_5  = p5,

    P0_8  = p8,
    P0_9  = p9,
    P0_11 = p11,
    P0_12 = p12,
    P0_15 = p15,

    P0_16 = p16,
    P0_18 = p18,
    P0_20 = p20,
    P0_21 = p21,

    P0_24 = p24,

    LED1    = p16,
    LED2    = p12,
    LED3    = p15,
    LEDR    = LED1,
    LEDG    = LED2,
    LEDB    = LED3,

    BUTTON1 = p8,
    BUTTON2 = p18,

    RX_PIN_NUMBER  = p21,
    TX_PIN_NUMBER  = p24,
    CTS_PIN_NUMBER = p0,
    RTS_PIN_NUMBER = p20,

    SPI_PSELMOSI0 = p2,
    SPI_PSELMISO0 = p5,
    SPI_PSELSS0   = p1,
    SPI_PSELSCK0  = p3,

    I2C_SDA0 = p9,
    I2C_SCL0 = p11,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullNone = 0,
    PullDown = 1,
    PullUp = 3,
    PullDefault = PullUp
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
