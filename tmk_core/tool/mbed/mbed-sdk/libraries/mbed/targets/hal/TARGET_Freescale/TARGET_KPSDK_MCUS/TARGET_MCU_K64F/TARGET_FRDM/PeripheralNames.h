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
} RTCName;

typedef enum {
    UART_0 = 0,
    UART_1 = 1,
    UART_2 = 2,
    UART_3 = 3,
    UART_4 = 4,
} UARTName;

#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX
#define STDIO_UART        UART_0

typedef enum {
    I2C_0 = 0,
    I2C_1 = 1,
    I2C_2 = 2,
} I2CName;

#define TPM_SHIFT   8
typedef enum {
    PWM_1  = (0 << TPM_SHIFT) | (0),  // FTM0 CH0
    PWM_2  = (0 << TPM_SHIFT) | (1),  // FTM0 CH1
    PWM_3  = (0 << TPM_SHIFT) | (2),  // FTM0 CH2
    PWM_4  = (0 << TPM_SHIFT) | (3),  // FTM0 CH3
    PWM_5  = (0 << TPM_SHIFT) | (4),  // FTM0 CH4
    PWM_6  = (0 << TPM_SHIFT) | (5),  // FTM0 CH5
    PWM_7  = (0 << TPM_SHIFT) | (6),  // FTM0 CH6
    PWM_8  = (0 << TPM_SHIFT) | (7),  // FTM0 CH7
    PWM_9  = (1 << TPM_SHIFT) | (0),  // FTM1 CH0
    PWM_10 = (1 << TPM_SHIFT) | (1),  // FTM1 CH1
    PWM_11 = (1 << TPM_SHIFT) | (2),  // FTM1 CH2
    PWM_12 = (1 << TPM_SHIFT) | (3),  // FTM1 CH3
    PWM_13 = (1 << TPM_SHIFT) | (4),  // FTM1 CH4
    PWM_14 = (1 << TPM_SHIFT) | (5),  // FTM1 CH5
    PWM_15 = (1 << TPM_SHIFT) | (6),  // FTM1 CH6
    PWM_16 = (1 << TPM_SHIFT) | (7),  // FTM1 CH7
    PWM_17 = (2 << TPM_SHIFT) | (0),  // FTM2 CH0
    PWM_18 = (2 << TPM_SHIFT) | (1),  // FTM2 CH1
    PWM_19 = (2 << TPM_SHIFT) | (2),  // FTM2 CH2
    PWM_20 = (2 << TPM_SHIFT) | (3),  // FTM2 CH3
    PWM_21 = (2 << TPM_SHIFT) | (4),  // FTM2 CH4
    PWM_22 = (2 << TPM_SHIFT) | (5),  // FTM2 CH5
    PWM_23 = (2 << TPM_SHIFT) | (6),  // FTM2 CH6
    PWM_24 = (2 << TPM_SHIFT) | (7),  // FTM2 CH7
    // could be 4 or could be 3... not sure what register
    //  this is for... too much abstraction
    PWM_25 = (3 << TPM_SHIFT) | (0),  // FTM3 CH0
    PWM_26 = (3 << TPM_SHIFT) | (1),  // FTM3 CH1
    PWM_27 = (3 << TPM_SHIFT) | (2),  // FTM3 CH2
    PWM_28 = (3 << TPM_SHIFT) | (3),  // FTM3 CH3
    PWM_29 = (3 << TPM_SHIFT) | (4),  // FTM3 CH4
    PWM_30 = (3 << TPM_SHIFT) | (5),  // FTM3 CH5
    PWM_31 = (3 << TPM_SHIFT) | (6),  // FTM3 CH6
    PWM_32 = (3 << TPM_SHIFT) | (7),  // FTM3 CH7
} PWMName;

#define ADC_INSTANCE_SHIFT           8
#define ADC_B_CHANNEL_SHIFT          5
typedef enum {
    ADC0_SE4b = (0 << ADC_INSTANCE_SHIFT) | (1 << ADC_B_CHANNEL_SHIFT) | 4,
    ADC0_SE5b = (0 << ADC_INSTANCE_SHIFT) | (1 << ADC_B_CHANNEL_SHIFT) | 5,
    ADC0_SE6b = (0 << ADC_INSTANCE_SHIFT) | (1 << ADC_B_CHANNEL_SHIFT) | 6,
    ADC0_SE7b = (0 << ADC_INSTANCE_SHIFT) | (1 << ADC_B_CHANNEL_SHIFT) | 7,
    ADC0_SE8  = (0 << ADC_INSTANCE_SHIFT) | 8,
    ADC0_SE9  = (0 << ADC_INSTANCE_SHIFT) | 9,
    ADC0_SE12 = (0 << ADC_INSTANCE_SHIFT) | 12,
    ADC0_SE13 = (0 << ADC_INSTANCE_SHIFT) | 13,
    ADC0_SE14 = (0 << ADC_INSTANCE_SHIFT) | 14,
    ADC0_SE15 = (0 << ADC_INSTANCE_SHIFT) | 15,
    ADC0_SE16 = (0 << ADC_INSTANCE_SHIFT) | 16,
    ADC0_SE17 = (0 << ADC_INSTANCE_SHIFT) | 17,
    ADC0_SE18 = (0 << ADC_INSTANCE_SHIFT) | 18,
    ADC1_SE4b = (1 << ADC_INSTANCE_SHIFT) | 4,
    ADC1_SE5b = (1 << ADC_INSTANCE_SHIFT) | 5,
    ADC1_SE6b = (1 << ADC_INSTANCE_SHIFT) | 6,
    ADC1_SE7b = (1 << ADC_INSTANCE_SHIFT) | 7,
    ADC1_SE8  = (1 << ADC_INSTANCE_SHIFT) | 8,
    ADC1_SE9  = (1 << ADC_INSTANCE_SHIFT) | 9,
    ADC1_SE12 = (1 << ADC_INSTANCE_SHIFT) | 12,
    ADC1_SE13 = (1 << ADC_INSTANCE_SHIFT) | 13,
    ADC1_SE14 = (1 << ADC_INSTANCE_SHIFT) | 14,
    ADC1_SE15 = (1 << ADC_INSTANCE_SHIFT) | 15,
    ADC1_SE16 = (1 << ADC_INSTANCE_SHIFT) | 16,
    ADC1_SE17 = (1 << ADC_INSTANCE_SHIFT) | 17,
    ADC1_SE18 = (1 << ADC_INSTANCE_SHIFT) | 18,
} ADCName;

typedef enum {
    DAC_0 = 0
} DACName;


typedef enum {
    SPI_0 = 0,
    SPI_1 = 1,
    SPI_2 = 2,
} SPIName;

#ifdef __cplusplus
}
#endif

#endif
