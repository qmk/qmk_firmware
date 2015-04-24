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
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STDIO_UART_TX     TX_PIN_NUMBER
#define STDIO_UART_RX     RX_PIN_NUMBER
#define STDIO_UART        UART_0

typedef enum {
    UART_0 = (int)NRF_UART0_BASE
} UARTName;


typedef enum {
    SPI_0 = (int)NRF_SPI0_BASE,
    SPI_1 = (int)NRF_SPI1_BASE,
    SPIS = (int)NRF_SPIS1_BASE
} SPIName;

typedef enum {
    PWM_1 = 0,
    PWM_2
} PWMName;

typedef enum {
    I2C_0 = (int)NRF_TWI0_BASE,
    I2C_1 = (int)NRF_TWI1_BASE
} I2CName;

typedef enum {
    ADC0_0 = (int)NRF_ADC_BASE
} ADCName;

#ifdef __cplusplus
}
#endif

#endif
