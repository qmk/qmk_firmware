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

#define PORT_SHIFT  16
#define PIN_SHIFT    9

typedef enum {
    // LPC11U68 Pin Names (PORT[19:16] + PIN[15:9] + IOCON offset[8:0])

    P0_0 = (0 << PORT_SHIFT) | (0 << PIN_SHIFT) | 0x000,
    P0_1 = (0 << PORT_SHIFT) | (1 << PIN_SHIFT) | 0x004,
    P0_2 = (0 << PORT_SHIFT) | (2 << PIN_SHIFT) | 0x008,
    P0_3 = (0 << PORT_SHIFT) | (3 << PIN_SHIFT) | 0x00C,
    P0_4 = (0 << PORT_SHIFT) | (4 << PIN_SHIFT) | 0x010,
    P0_5 = (0 << PORT_SHIFT) | (5 << PIN_SHIFT) | 0x014,
    P0_6 = (0 << PORT_SHIFT) | (6 << PIN_SHIFT) | 0x018,
    P0_7 = (0 << PORT_SHIFT) | (7 << PIN_SHIFT) | 0x01C,
    P0_8 = (0 << PORT_SHIFT) | (8 << PIN_SHIFT) | 0x020,
    P0_9 = (0 << PORT_SHIFT) | (9 << PIN_SHIFT) | 0x024,
    P0_10= (0 << PORT_SHIFT) | (10<< PIN_SHIFT) | 0x028,
    P0_11= (0 << PORT_SHIFT) | (11<< PIN_SHIFT) | 0x02C,
    P0_12= (0 << PORT_SHIFT) | (12<< PIN_SHIFT) | 0x030,
    P0_13= (0 << PORT_SHIFT) | (13<< PIN_SHIFT) | 0x034,
    P0_14= (0 << PORT_SHIFT) | (14<< PIN_SHIFT) | 0x038,
    P0_15= (0 << PORT_SHIFT) | (15<< PIN_SHIFT) | 0x03C,
    P0_16= (0 << PORT_SHIFT) | (16<< PIN_SHIFT) | 0x040,
    P0_17= (0 << PORT_SHIFT) | (17<< PIN_SHIFT) | 0x044,
    P0_18= (0 << PORT_SHIFT) | (18<< PIN_SHIFT) | 0x048,
    P0_19= (0 << PORT_SHIFT) | (19<< PIN_SHIFT) | 0x04C,
    P0_20= (0 << PORT_SHIFT) | (20<< PIN_SHIFT) | 0x050,
    P0_21= (0 << PORT_SHIFT) | (21<< PIN_SHIFT) | 0x054,
    P0_22= (0 << PORT_SHIFT) | (22<< PIN_SHIFT) | 0x058,
    P0_23= (0 << PORT_SHIFT) | (23<< PIN_SHIFT) | 0x05C,

    P1_0 = (1 << PORT_SHIFT) | (0 << PIN_SHIFT) | 0x060, 
    P1_1 = (1 << PORT_SHIFT) | (1 << PIN_SHIFT) | 0x064, 
    P1_2 = (1 << PORT_SHIFT) | (2 << PIN_SHIFT) | 0x068, 
    P1_3 = (1 << PORT_SHIFT) | (3 << PIN_SHIFT) | 0x06C, 
    P1_4 = (1 << PORT_SHIFT) | (4 << PIN_SHIFT) | 0x070, 
    P1_5 = (1 << PORT_SHIFT) | (5 << PIN_SHIFT) | 0x074, 
    P1_6 = (1 << PORT_SHIFT) | (6 << PIN_SHIFT) | 0x078, 
    P1_7 = (1 << PORT_SHIFT) | (7 << PIN_SHIFT) | 0x07C, 
    P1_8 = (1 << PORT_SHIFT) | (8 << PIN_SHIFT) | 0x080, 
    P1_9 = (1 << PORT_SHIFT) | (9 << PIN_SHIFT) | 0x084, 
    P1_10= (1 << PORT_SHIFT) | (10<< PIN_SHIFT) | 0x088, 
    P1_11= (1 << PORT_SHIFT) | (11<< PIN_SHIFT) | 0x08C, 
    P1_12= (1 << PORT_SHIFT) | (12<< PIN_SHIFT) | 0x090, 
    P1_13= (1 << PORT_SHIFT) | (13<< PIN_SHIFT) | 0x094, 
    P1_14= (1 << PORT_SHIFT) | (14<< PIN_SHIFT) | 0x098, 
    P1_15= (1 << PORT_SHIFT) | (15<< PIN_SHIFT) | 0x09C, 
    P1_16= (1 << PORT_SHIFT) | (16<< PIN_SHIFT) | 0x0A0, 
    P1_17= (1 << PORT_SHIFT) | (17<< PIN_SHIFT) | 0x0A4, 
    P1_18= (1 << PORT_SHIFT) | (18<< PIN_SHIFT) | 0x0A8, 
    P1_19= (1 << PORT_SHIFT) | (19<< PIN_SHIFT) | 0x0AC, 
    P1_20= (1 << PORT_SHIFT) | (20<< PIN_SHIFT) | 0x0B0, 
    P1_21= (1 << PORT_SHIFT) | (21<< PIN_SHIFT) | 0x0B4, 
    P1_22= (1 << PORT_SHIFT) | (22<< PIN_SHIFT) | 0x0B8, 
    P1_23= (1 << PORT_SHIFT) | (23<< PIN_SHIFT) | 0x0BC, 
    P1_24= (1 << PORT_SHIFT) | (24<< PIN_SHIFT) | 0x0C0, 
    P1_25= (1 << PORT_SHIFT) | (25<< PIN_SHIFT) | 0x0C4, 
    P1_26= (1 << PORT_SHIFT) | (26<< PIN_SHIFT) | 0x0C8, 
    P1_27= (1 << PORT_SHIFT) | (27<< PIN_SHIFT) | 0x0CC, 
    P1_28= (1 << PORT_SHIFT) | (28<< PIN_SHIFT) | 0x0D0, 
    P1_29= (1 << PORT_SHIFT) | (29<< PIN_SHIFT) | 0x0D4, 
    P1_30= (1 << PORT_SHIFT) | (30<< PIN_SHIFT) | 0x0D8, 
    P1_31= (1 << PORT_SHIFT) | (31<< PIN_SHIFT) | 0x0DC, 

    P2_0 = (2 << PORT_SHIFT) | (0 << PIN_SHIFT) | 0x0F0, 
    P2_1 = (2 << PORT_SHIFT) | (1 << PIN_SHIFT) | 0x0F4, 
    P2_2 = (2 << PORT_SHIFT) | (2 << PIN_SHIFT) | 0x0FC, 
    P2_3 = (2 << PORT_SHIFT) | (3 << PIN_SHIFT) | 0x100, 
    P2_4 = (2 << PORT_SHIFT) | (4 << PIN_SHIFT) | 0x104, 
    P2_5 = (2 << PORT_SHIFT) | (5 << PIN_SHIFT) | 0x108, 
    P2_6 = (2 << PORT_SHIFT) | (6 << PIN_SHIFT) | 0x10C, 
    P2_7 = (2 << PORT_SHIFT) | (7 << PIN_SHIFT) | 0x110, 
    P2_8 = (2 << PORT_SHIFT) | (8 << PIN_SHIFT) | 0x114, 
    P2_9 = (2 << PORT_SHIFT) | (9 << PIN_SHIFT) | 0x118, 
    P2_10= (2 << PORT_SHIFT) | (10<< PIN_SHIFT) | 0x11C, 
    P2_11= (2 << PORT_SHIFT) | (11<< PIN_SHIFT) | 0x120, 
    P2_12= (2 << PORT_SHIFT) | (12<< PIN_SHIFT) | 0x124, 
    P2_13= (2 << PORT_SHIFT) | (13<< PIN_SHIFT) | 0x128, 
    P2_14= (2 << PORT_SHIFT) | (14<< PIN_SHIFT) | 0x12C, 
    P2_15= (2 << PORT_SHIFT) | (15<< PIN_SHIFT) | 0x130, 
    P2_16= (2 << PORT_SHIFT) | (16<< PIN_SHIFT) | 0x134, 
    P2_17= (2 << PORT_SHIFT) | (17<< PIN_SHIFT) | 0x138, 
    P2_18= (2 << PORT_SHIFT) | (18<< PIN_SHIFT) | 0x13C, 
    P2_19= (2 << PORT_SHIFT) | (19<< PIN_SHIFT) | 0x140, 
    P2_20= (2 << PORT_SHIFT) | (20<< PIN_SHIFT) | 0x144, 
    P2_21= (2 << PORT_SHIFT) | (21<< PIN_SHIFT) | 0x148, 
    P2_22= (2 << PORT_SHIFT) | (22<< PIN_SHIFT) | 0x14C, 
    P2_23= (2 << PORT_SHIFT) | (23<< PIN_SHIFT) | 0x150, 
    
    LED_RED   = P2_17,
    LED_GREEN = P2_16,
    LED_BLUE  = P2_18,
    
    // mbed original LED naming
    LED1 = LED_RED,
    LED2 = LED_GREEN,
    LED3 = LED_BLUE,
    LED4 = LED_BLUE,
    
    // Serial to USB pins
    USBTX = P0_19,
    USBRX = P0_18,
    
    // Arduino Shield Receptacles Names
    D0 = P0_18,
    D1 = P0_19,
    D2 = P1_18,
    D3 = P1_24,
    D4 = P1_19,
    D5 = P1_26,
    D6 = P1_27,
    D7 = P1_25,
    D8 = P1_28,
    D9 = P2_3,
    D10= P0_2,
    D11= P0_9,
    D12= P0_8,
    D13= P1_29,
    D14= P0_5,
    D15= P0_4,

    A0 = P1_9,
    A1 = P0_14,
    A2 = P0_13,
    A3 = P0_12,
    A4 = P0_5, // same port as SDA
    A5 = P0_4, // same port as SCL
    SDA= P0_5, // same port as A4
    SCL= P0_4, // same port as A5
    
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
#define STDIO_UART        UART_0

#ifdef __cplusplus
}
#endif

#endif
