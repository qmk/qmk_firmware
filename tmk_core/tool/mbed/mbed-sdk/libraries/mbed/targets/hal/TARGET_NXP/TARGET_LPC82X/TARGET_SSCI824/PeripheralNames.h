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
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

// Default peripherals

// SPI: MOSI, MISO, CLK, SEL
#define MBED_SPI0         P0_26, P0_25, P0_24, P0_15

#define MBED_UART0        P0_7, P0_18
#define MBED_UARTUSB      USBTX, USBRX

#define MBED_I2C0         P0_11, P0_10

typedef enum {
    ADC_0 = 0,
    ADC_1,
    ADC_2,
    ADC_3,
    ADC_4,
    ADC_5,
    ADC_6,
    ADC_7,
    ADC_8,
    ADC_9,
    ADC_10,
    ADC_11,
} ADCName;


#ifdef __cplusplus
}
#endif

#endif
