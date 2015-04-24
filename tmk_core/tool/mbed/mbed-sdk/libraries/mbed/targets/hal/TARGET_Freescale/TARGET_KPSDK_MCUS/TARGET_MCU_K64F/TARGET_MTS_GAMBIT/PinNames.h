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

#define GPIO_PORT_SHIFT 12

typedef enum {
    PTA0  = (0 << GPIO_PORT_SHIFT | 0 ),
    PTA1  = (0 << GPIO_PORT_SHIFT | 1 ),
    PTA2  = (0 << GPIO_PORT_SHIFT | 2 ),
    PTA3  = (0 << GPIO_PORT_SHIFT | 3 ),
    PTA4  = (0 << GPIO_PORT_SHIFT | 4 ),
    PTA5  = (0 << GPIO_PORT_SHIFT | 5 ),
    PTA6  = (0 << GPIO_PORT_SHIFT | 6 ),
    PTA7  = (0 << GPIO_PORT_SHIFT | 7 ),
    PTA8  = (0 << GPIO_PORT_SHIFT | 8 ),
    PTA9  = (0 << GPIO_PORT_SHIFT | 9 ),
    PTA10 = (0 << GPIO_PORT_SHIFT | 10),
    PTA11 = (0 << GPIO_PORT_SHIFT | 11),
    PTA12 = (0 << GPIO_PORT_SHIFT | 12),
    PTA13 = (0 << GPIO_PORT_SHIFT | 13),
    PTA14 = (0 << GPIO_PORT_SHIFT | 14),
    PTA15 = (0 << GPIO_PORT_SHIFT | 15),
    PTA16 = (0 << GPIO_PORT_SHIFT | 16),
    PTA17 = (0 << GPIO_PORT_SHIFT | 17),
    PTA18 = (0 << GPIO_PORT_SHIFT | 18),
    PTA19 = (0 << GPIO_PORT_SHIFT | 19),
    PTA20 = (0 << GPIO_PORT_SHIFT | 20),
    PTA21 = (0 << GPIO_PORT_SHIFT | 21),
    PTA22 = (0 << GPIO_PORT_SHIFT | 22),
    PTA23 = (0 << GPIO_PORT_SHIFT | 23),
    PTA24 = (0 << GPIO_PORT_SHIFT | 24),
    PTA25 = (0 << GPIO_PORT_SHIFT | 25),
    PTA26 = (0 << GPIO_PORT_SHIFT | 26),
    PTA27 = (0 << GPIO_PORT_SHIFT | 27),
    PTA28 = (0 << GPIO_PORT_SHIFT | 28),
    PTA29 = (0 << GPIO_PORT_SHIFT | 29),
    PTA30 = (0 << GPIO_PORT_SHIFT | 30),
    PTA31 = (0 << GPIO_PORT_SHIFT | 31),
    PTB0  = (1 << GPIO_PORT_SHIFT | 0 ),
    PTB1  = (1 << GPIO_PORT_SHIFT | 1 ),
    PTB2  = (1 << GPIO_PORT_SHIFT | 2 ),
    PTB3  = (1 << GPIO_PORT_SHIFT | 3 ),
    PTB4  = (1 << GPIO_PORT_SHIFT | 4 ),
    PTB5  = (1 << GPIO_PORT_SHIFT | 5 ),
    PTB6  = (1 << GPIO_PORT_SHIFT | 6 ),
    PTB7  = (1 << GPIO_PORT_SHIFT | 7 ),
    PTB8  = (1 << GPIO_PORT_SHIFT | 8 ),
    PTB9  = (1 << GPIO_PORT_SHIFT | 9 ),
    PTB10 = (1 << GPIO_PORT_SHIFT | 10),
    PTB11 = (1 << GPIO_PORT_SHIFT | 11),
    PTB12 = (1 << GPIO_PORT_SHIFT | 12),
    PTB13 = (1 << GPIO_PORT_SHIFT | 13),
    PTB14 = (1 << GPIO_PORT_SHIFT | 14),
    PTB15 = (1 << GPIO_PORT_SHIFT | 15),
    PTB16 = (1 << GPIO_PORT_SHIFT | 16),
    PTB17 = (1 << GPIO_PORT_SHIFT | 17),
    PTB18 = (1 << GPIO_PORT_SHIFT | 18),
    PTB19 = (1 << GPIO_PORT_SHIFT | 19),
    PTB20 = (1 << GPIO_PORT_SHIFT | 20),
    PTB21 = (1 << GPIO_PORT_SHIFT | 21),
    PTB22 = (1 << GPIO_PORT_SHIFT | 22),
    PTB23 = (1 << GPIO_PORT_SHIFT | 23),
    PTB24 = (1 << GPIO_PORT_SHIFT | 24),
    PTB25 = (1 << GPIO_PORT_SHIFT | 25),
    PTB26 = (1 << GPIO_PORT_SHIFT | 26),
    PTB27 = (1 << GPIO_PORT_SHIFT | 27),
    PTB28 = (1 << GPIO_PORT_SHIFT | 28),
    PTB29 = (1 << GPIO_PORT_SHIFT | 29),
    PTB30 = (1 << GPIO_PORT_SHIFT | 30),
    PTB31 = (1 << GPIO_PORT_SHIFT | 31),
    PTC0  = (2 << GPIO_PORT_SHIFT | 0 ),
    PTC1  = (2 << GPIO_PORT_SHIFT | 1 ),
    PTC2  = (2 << GPIO_PORT_SHIFT | 2 ),
    PTC3  = (2 << GPIO_PORT_SHIFT | 3 ),
    PTC4  = (2 << GPIO_PORT_SHIFT | 4 ),
    PTC5  = (2 << GPIO_PORT_SHIFT | 5 ),
    PTC6  = (2 << GPIO_PORT_SHIFT | 6 ),
    PTC7  = (2 << GPIO_PORT_SHIFT | 7 ),
    PTC8  = (2 << GPIO_PORT_SHIFT | 8 ),
    PTC9  = (2 << GPIO_PORT_SHIFT | 9 ),
    PTC10 = (2 << GPIO_PORT_SHIFT | 10),
    PTC11 = (2 << GPIO_PORT_SHIFT | 11),
    PTC12 = (2 << GPIO_PORT_SHIFT | 12),
    PTC13 = (2 << GPIO_PORT_SHIFT | 13),
    PTC14 = (2 << GPIO_PORT_SHIFT | 14),
    PTC15 = (2 << GPIO_PORT_SHIFT | 15),
    PTC16 = (2 << GPIO_PORT_SHIFT | 16),
    PTC17 = (2 << GPIO_PORT_SHIFT | 17),
    PTC18 = (2 << GPIO_PORT_SHIFT | 18),
    PTC19 = (2 << GPIO_PORT_SHIFT | 19),
    PTC20 = (2 << GPIO_PORT_SHIFT | 20),
    PTC21 = (2 << GPIO_PORT_SHIFT | 21),
    PTC22 = (2 << GPIO_PORT_SHIFT | 22),
    PTC23 = (2 << GPIO_PORT_SHIFT | 23),
    PTC24 = (2 << GPIO_PORT_SHIFT | 24),
    PTC25 = (2 << GPIO_PORT_SHIFT | 25),
    PTC26 = (2 << GPIO_PORT_SHIFT | 26),
    PTC27 = (2 << GPIO_PORT_SHIFT | 27),
    PTC28 = (2 << GPIO_PORT_SHIFT | 28),
    PTC29 = (2 << GPIO_PORT_SHIFT | 29),
    PTC30 = (2 << GPIO_PORT_SHIFT | 30),
    PTC31 = (2 << GPIO_PORT_SHIFT | 31),
    PTD0  = (3 << GPIO_PORT_SHIFT | 0 ),
    PTD1  = (3 << GPIO_PORT_SHIFT | 1 ),
    PTD2  = (3 << GPIO_PORT_SHIFT | 2 ),
    PTD3  = (3 << GPIO_PORT_SHIFT | 3 ),
    PTD4  = (3 << GPIO_PORT_SHIFT | 4 ),
    PTD5  = (3 << GPIO_PORT_SHIFT | 5 ),
    PTD6  = (3 << GPIO_PORT_SHIFT | 6 ),
    PTD7  = (3 << GPIO_PORT_SHIFT | 7 ),
    PTD8  = (3 << GPIO_PORT_SHIFT | 8 ),
    PTD9  = (3 << GPIO_PORT_SHIFT | 9 ),
    PTD10 = (3 << GPIO_PORT_SHIFT | 10),
    PTD11 = (3 << GPIO_PORT_SHIFT | 11),
    PTD12 = (3 << GPIO_PORT_SHIFT | 12),
    PTD13 = (3 << GPIO_PORT_SHIFT | 13),
    PTD14 = (3 << GPIO_PORT_SHIFT | 14),
    PTD15 = (3 << GPIO_PORT_SHIFT | 15),
    PTD16 = (3 << GPIO_PORT_SHIFT | 16),
    PTD17 = (3 << GPIO_PORT_SHIFT | 17),
    PTD18 = (3 << GPIO_PORT_SHIFT | 18),
    PTD19 = (3 << GPIO_PORT_SHIFT | 19),
    PTD20 = (3 << GPIO_PORT_SHIFT | 20),
    PTD21 = (3 << GPIO_PORT_SHIFT | 21),
    PTD22 = (3 << GPIO_PORT_SHIFT | 22),
    PTD23 = (3 << GPIO_PORT_SHIFT | 23),
    PTD24 = (3 << GPIO_PORT_SHIFT | 24),
    PTD25 = (3 << GPIO_PORT_SHIFT | 25),
    PTD26 = (3 << GPIO_PORT_SHIFT | 26),
    PTD27 = (3 << GPIO_PORT_SHIFT | 27),
    PTD28 = (3 << GPIO_PORT_SHIFT | 28),
    PTD29 = (3 << GPIO_PORT_SHIFT | 29),
    PTD30 = (3 << GPIO_PORT_SHIFT | 30),
    PTD31 = (3 << GPIO_PORT_SHIFT | 31),
    PTE0  = (4 << GPIO_PORT_SHIFT | 0 ),
    PTE1  = (4 << GPIO_PORT_SHIFT | 1 ),
    PTE2  = (4 << GPIO_PORT_SHIFT | 2 ),
    PTE3  = (4 << GPIO_PORT_SHIFT | 3 ),
    PTE4  = (4 << GPIO_PORT_SHIFT | 4 ),
    PTE5  = (4 << GPIO_PORT_SHIFT | 5 ),
    PTE6  = (4 << GPIO_PORT_SHIFT | 6 ),
    PTE7  = (4 << GPIO_PORT_SHIFT | 7 ),
    PTE8  = (4 << GPIO_PORT_SHIFT | 8 ),
    PTE9  = (4 << GPIO_PORT_SHIFT | 9 ),
    PTE10 = (4 << GPIO_PORT_SHIFT | 10),
    PTE11 = (4 << GPIO_PORT_SHIFT | 11),
    PTE12 = (4 << GPIO_PORT_SHIFT | 12),
    PTE13 = (4 << GPIO_PORT_SHIFT | 13),
    PTE14 = (4 << GPIO_PORT_SHIFT | 14),
    PTE15 = (4 << GPIO_PORT_SHIFT | 15),
    PTE16 = (4 << GPIO_PORT_SHIFT | 16),
    PTE17 = (4 << GPIO_PORT_SHIFT | 17),
    PTE18 = (4 << GPIO_PORT_SHIFT | 18),
    PTE19 = (4 << GPIO_PORT_SHIFT | 19),
    PTE20 = (4 << GPIO_PORT_SHIFT | 20),
    PTE21 = (4 << GPIO_PORT_SHIFT | 21),
    PTE22 = (4 << GPIO_PORT_SHIFT | 22),
    PTE23 = (4 << GPIO_PORT_SHIFT | 23),
    PTE24 = (4 << GPIO_PORT_SHIFT | 24),
    PTE25 = (4 << GPIO_PORT_SHIFT | 25),
    PTE26 = (4 << GPIO_PORT_SHIFT | 26),
    PTE27 = (4 << GPIO_PORT_SHIFT | 27),
    PTE28 = (4 << GPIO_PORT_SHIFT | 28),
    PTE29 = (4 << GPIO_PORT_SHIFT | 29),
    PTE30 = (4 << GPIO_PORT_SHIFT | 30),
    PTE31 = (4 << GPIO_PORT_SHIFT | 31),

    // led color naming
    LED_GREEN = PTC0,

    // mbed original LED naming
    LED1 = PTD15,
    LED2 = PTD14,
    LED3 = PTD13,
    LED4 = PTD11,
    LED5 = PTD12,
    STATUS = LED_GREEN,

    // USB Pins
    USBTX = PTB17,
    USBRX = PTB16,

    // SPI Pins
    SPI0_SOUT = PTC6,
    SPI0_SIN = PTC7,
    SPI0_SCK = PTC5,

    SPI1_SOUT = PTE3,
    SPI1_SIN = PTE1,
    SPI1_SCK = PTE2,

    // SPI Chip Select Pins
    SPI0_NCS0 = PTC4,
    SPI0_NCS1 = PTC3,
    SPI0_NCS2 = PTC2,
    SPI0_NCS3 = PTC1,

    SPI1_NCS0 = PTE4,
    SPI1_NCS1 = PTE0,
    SPI1_NCS2 = PTE5,
    SPI1_NCS3 = PTE6,

    // GPIO's
    AP1_GPIO1 = PTB7,
    AP1_GPIO2 = PTB6,
    AP1_GPIO3 = PTB5,
    AP1_GPIO4 = PTB4,

    AP2_GPIO1 = PTA27,
    AP2_GPIO2 = PTA26,
    AP2_GPIO3 = PTA25,
    AP2_GPIO4 = PTA24,

    // Cellular Radio Serial Pins
    RADIO_SERIAL_TX = PTE8,
    RADIO_SERIAL_RX = PTE9,
    RADIO_SERIAL_RTS = PTE11,
    RADIO_SERIAL_CTS = PTE10,
    RADIO_SERIAL_DTR = PTE26,
    RADIO_SERIAL_DSR = PTE25,
    RADIO_SERIAL_RI = PTE24,
    RADIO_SERIAL_CD = PTE12,

    DAC0_OUT = 0xFEFE, /* DAC does not have Pin Name in RM */

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;


typedef enum {
    PullNone = 0,
    PullDown = 1,
    PullUp   = 2,
    PullDefault = PullUp
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
