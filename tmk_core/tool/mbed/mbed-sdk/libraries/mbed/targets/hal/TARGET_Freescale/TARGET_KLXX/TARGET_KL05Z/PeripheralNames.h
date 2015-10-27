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
    OSC32KCLK = 0,
    RTC_CLKIN = 2
} RTCName;

typedef enum {
    UART_0 = (int)UART0_BASE
} UARTName;

#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX
#define STDIO_UART        UART_0

typedef enum {
    I2C_0 = (int)I2C0_BASE,
    I2C_1 = -1
} I2CName;

typedef enum {
    ADC0_SE0  =  0,
    ADC0_SE1  =  1,
    ADC0_SE2  =  2,
    ADC0_SE3  =  3,
    ADC0_SE4  =  4,
    ADC0_SE5  =  5,
    ADC0_SE6  =  6,
    ADC0_SE7  =  7,
    ADC0_SE8  =  8,
    ADC0_SE9  =  9,
    ADC0_SE10 =  10,
    ADC0_SE11 =  11,
    ADC0_SE12 =  12,
    ADC0_SE13 =  13
} ADCName;

typedef enum {
    DAC_0 = 0
} DACName;

typedef enum {
    SPI_0 = (int)SPI0_BASE
} SPIName;

#define TPM_SHIFT   8
typedef enum {
    PWM_1  = (0 << TPM_SHIFT) | (0),  // TPM0 CH0
    PWM_2  = (0 << TPM_SHIFT) | (1),  // TPM0 CH1
    PWM_3  = (0 << TPM_SHIFT) | (2),  // TPM0 CH2
    PWM_4  = (0 << TPM_SHIFT) | (3),  // TPM0 CH3
    PWM_5  = (0 << TPM_SHIFT) | (4),  // TPM0 CH4
    PWM_6  = (0 << TPM_SHIFT) | (5),  // TPM0 CH5

    PWM_7  = (1 << TPM_SHIFT) | (0),  // TPM1 CH0
    PWM_8  = (1 << TPM_SHIFT) | (1),  // TPM1 CH1
} PWMName;

#ifdef __cplusplus
}
#endif

#endif
