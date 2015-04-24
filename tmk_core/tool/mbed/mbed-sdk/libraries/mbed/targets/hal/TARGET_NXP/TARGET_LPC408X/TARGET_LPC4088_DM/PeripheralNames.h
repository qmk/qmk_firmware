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
    UART_0 = (int)LPC_UART0_BASE,
    UART_1 = (int)LPC_UART1_BASE,
    UART_2 = (int)LPC_UART2_BASE,
    UART_3 = (int)LPC_UART3_BASE,
    UART_4 = (int)LPC_UART4_BASE
} UARTName;

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
    DAC_0 = 0
} DACName;

typedef enum {
    SPI_0 = (int)LPC_SSP0_BASE,
    SPI_1 = (int)LPC_SSP1_BASE,
    SPI_2 = (int)LPC_SSP2_BASE
} SPIName;

typedef enum {
    I2C_0 = (int)LPC_I2C0_BASE,
    I2C_1 = (int)LPC_I2C1_BASE,
    I2C_2 = (int)LPC_I2C2_BASE
} I2CName;

typedef enum {
    PWM0_1 = 1,
    PWM0_2,
    PWM0_3,
    PWM0_4,
    PWM0_5,
    PWM0_6,
    PWM1_1,
    PWM1_2,
    PWM1_3,
    PWM1_4,
    PWM1_5,
    PWM1_6
} PWMName;

typedef enum {
     CAN_1 = (int)LPC_CAN1_BASE,
     CAN_2 = (int)LPC_CAN2_BASE
} CANName;

#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX
#define STDIO_UART        UART_0

// Default peripherals
#define MBED_SPI0         p7, p8, p9
#define MBED_SPI1         p46, p44, p42, p45
#define MBED_SPI2         p15, p16, p17, p18

#define MBED_UART3        p29, p30
#define MBED_UART4        p19, p18
#define MBED_UARTUSB      USBTX, USBRX

#define MBED_I2C1         p12, p13

#define MBED_CAN1         p12, p13
#define MBED_CAN2         p41, p43

#define MBED_ANALOGOUT0   p30

#define MBED_ANALOGIN2    p29
#define MBED_ANALOGIN3    p30

#define MBED_PWMOUT0      p9
#define MBED_PWMOUT1      p8
#define MBED_PWMOUT2      p7

#ifdef __cplusplus
}
#endif

#endif
