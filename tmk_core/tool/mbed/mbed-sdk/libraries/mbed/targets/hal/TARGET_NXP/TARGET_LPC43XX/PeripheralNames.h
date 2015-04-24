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
    UART_1 = (int)LPC_UART1_BASE,
    UART_2 = (int)LPC_USART2_BASE,
    UART_3 = (int)LPC_USART3_BASE
} UARTName;

typedef enum {
    ADC0_0 = 0,
    ADC0_1,
    ADC0_2,
    ADC0_3,
    ADC0_4,
    ADC0_5,
    ADC0_6,
    ADC0_7,
    ADC1_0,
    ADC1_1,
    ADC1_2,
    ADC1_3,
    ADC1_4,
    ADC1_5,
    ADC1_6,
    ADC1_7
} ADCName;

typedef enum {
    DAC_0 = 0
} DACName;

typedef enum {
    SPI_0 = (int)LPC_SSP0_BASE,
    SPI_1 = (int)LPC_SSP1_BASE
} SPIName;

typedef enum {
    I2C_0 = (int)LPC_I2C0_BASE,
    I2C_1 = (int)LPC_I2C1_BASE
} I2CName;

typedef enum {
    PWM_0,
    PWM_1,
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
    PWM_13,
    PWM_14,
    PWM_15
} PWMName;

typedef enum {
     CAN_0 = (int)LPC_C_CAN0_BASE,
     CAN_1 = (int)LPC_C_CAN1_BASE
} CANName;

#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX
#define STDIO_UART        UART_2

// Default peripherals
#define MBED_SPI0         SPI0_MOSI, SPI0_MISO, SPI0_SCK, SPI0_SSEL
#define MBED_SPI1         SPI1_MOSI, SPI1_MISO, SPI1_SCK, SPI1_SSEL

#define MBED_UART0        UART0_TX, UART0_RX
#define MBED_UART1        UART1_TX, UART1_RX
#define MBED_UART2        UART2_TX, UART2_RX
#define MBED_UART3        UART3_TX, UART3_RX
#define MBED_UARTUSB      USBTX, USBRX

#define COM1              MBED_UART0
#define COM2              MBED_UART1
#define COM3              MBED_UART2
#define COM4              MBED_UART3

#define MBED_I2C0         I2C0_SDA, I2C0_SCL
#define MBED_I2C1         I2C1_SDA, I2C1_SCL

#define MBED_CAN0         p30, p29

#define MBED_ANALOGOUT0   DAC0

#define MBED_ANALOGIN0    ADC0
#define MBED_ANALOGIN1    ADC1
#define MBED_ANALOGIN2    ADC2
#define MBED_ANALOGIN3    ADC3
#define MBED_ANALOGIN4    ADC4
#define MBED_ANALOGIN5    ADC5
#define MBED_ANALOGIN6    ADC6
#define MBED_ANALOGIN7    ADC7

#define MBED_PWMOUT0      p26
#define MBED_PWMOUT1      p25
#define MBED_PWMOUT2      p24
#define MBED_PWMOUT3      p23
#define MBED_PWMOUT4      p22
#define MBED_PWMOUT5      p21

#ifdef __cplusplus
}
#endif

#endif
