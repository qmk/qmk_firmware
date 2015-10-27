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
    UART_0 = (int)LPC_USART_BASE
} UARTName;

typedef enum {
    I2C_0 = (int)LPC_I2C_BASE
} I2CName;

typedef enum {
    ADC0_0 = 0,
    ADC0_1,
    ADC0_2,
    ADC0_3,
    ADC0_4,
    ADC0_5,
    ADC0_6,
    ADC0_7
} ADCName;

typedef enum {
    SPI_0 = (int)LPC_SSP0_BASE,
    SPI_1 = (int)LPC_SSP1_BASE
} SPIName;

typedef enum {
    PWM_1 = 0,
    PWM_2,
    PWM_3,
    PWM_4,
    PWM_5,
    PWM_6,
    PWM_7,
    PWM_8,
    PWM_9,
    PWM_10,
    PWM_11,
    PWM_12,
    PWM_13
} PWMName;

#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX
#define STDIO_UART        UART_0

// Default peripherals
#define MBED_SPI0         P0_9, P0_8, P0_6, P0_2        // MOSI, MISO, CLK, SEL
#define MBED_SPI1         P0_21, P0_22, P1_15, P01_19   // MOSI, MISO, CLK, SEL

#define MBED_UART0        USBTX, USBRX
#define MBED_UARTUSB      USBTX, USBRX

#define MBED_I2C0         P0_5, P0_4

#define MBED_ANALOGIN0    P0_11
#define MBED_ANALOGIN1    P0_12
#define MBED_ANALOGIN2    P0_13
#define MBED_ANALOGIN3    P0_14
#define MBED_ANALOGIN4    P0_15
#define MBED_ANALOGIN5    P0_16
#define MBED_ANALOGIN6    P0_22
#define MBED_ANALOGIN7    P0_23

#ifdef __cplusplus
}
#endif

#endif
