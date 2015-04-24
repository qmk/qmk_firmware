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

typedef enum {
    UART_0 = (int)LPC_USART0_BASE,
    UART_1 = (int)LPC_USART1_BASE,
    UART_2 = (int)LPC_USART2_BASE,
    UART_3 = (int)LPC_USART3_BASE,
    UART_4 = (int)LPC_USART4_BASE,
} UARTName;
	
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

typedef enum {
    SPI_0 = (int)LPC_SSP0_BASE,
    SPI_1 = (int)LPC_SSP1_BASE
} SPIName;

typedef enum {
    I2C_0 = (int)LPC_I2C0_BASE,
    I2C_1 = (int)LPC_I2C1_BASE
} I2CName;

typedef enum {
    SCT0_0 = 0,
    SCT0_1,
    SCT0_2,
    SCT0_3,
    SCT1_0,
    SCT1_1,
    SCT1_2,
    SCT1_3,
} PWMName;

#ifdef __cplusplus
}
#endif

#endif
