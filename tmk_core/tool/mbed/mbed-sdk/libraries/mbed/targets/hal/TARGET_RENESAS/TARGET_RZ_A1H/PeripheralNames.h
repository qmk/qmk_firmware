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
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UART0,
    UART1,
    UART2,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
} UARTName;

// PWMType & 1 == 1 then have to use PWDTR[12] == 1
typedef enum {
    PWM1A  = 0,
    PWM1B,
    PWM1C,
    PWM1D,
    PWM1E,
    PWM1F,
    PWM1G,
    PWM1H,
    PWM2A  = 0x10,
    PWM2B,
    PWM2C,
    PWM2D,
    PWM2E,
    PWM2F,
    PWM2G,
    PWM2H,
} PWMType;

typedef enum {
    PWM0_PIN,
    PWM1_PIN,
    PWM2_PIN,
    PWM3_PIN,
    PWM4_PIN,
    PWM5_PIN,
    PWM6_PIN,
    PWM7_PIN,
    PWM8_PIN,
    PWM9_PIN,
    PWM10_PIN,
    PWM11_PIN,
    PWM12_PIN,
    PWM13_PIN,
} PWMName;

typedef enum {
    AN0= 0,
    AN1= 1,
    AN2= 2,
    AN3= 3,
    AN4= 4,
    AN5= 5,
    AN6= 6,
    AN7= 7,
} ADCName;

typedef enum {
    SPI_0 = 0,
    SPI_1,
    SPI_2,
} SPIName;

typedef enum {
    I2C_0 = 0,
    I2C_1,
    I2C_2,
    I2C_3 
} I2CName;


#define STDIO_UART_TX     USBTX
#define STDIO_UART_RX     USBRX
#define STDIO_UART        UART2



#ifdef __cplusplus
}
#endif

#endif
