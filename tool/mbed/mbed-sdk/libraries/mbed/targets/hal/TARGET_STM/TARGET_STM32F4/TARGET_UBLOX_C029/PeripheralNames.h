/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ADC_1 = (int)ADC1_BASE,
    ADC_2 = (int)ADC2_BASE,
    ADC_3 = (int)ADC3_BASE
} ADCName;

typedef enum {
    DAC_0 = 0,
    DAC_1
} DACName;

typedef enum {
    UART_1 = (int)USART1_BASE,
    UART_2 = (int)USART2_BASE,
    UART_3 = (int)USART3_BASE,
    UART_4 = (int)UART4_BASE,
    UART_5 = (int)UART5_BASE,
    UART_6 = (int)USART6_BASE,
    UART_7 = (int)UART7_BASE,
    UART_8 = (int)UART8_BASE
} UARTName;

#define STDIO_UART_TX  PD_8
#define STDIO_UART_RX  PD_9
#define STDIO_UART     UART_3

typedef enum {
    SPI_1 = (int)SPI1_BASE,
    SPI_2 = (int)SPI2_BASE,
    SPI_3 = (int)SPI3_BASE,
    SPI_4 = (int)SPI4_BASE,
    SPI_5 = (int)SPI5_BASE
} SPIName;

typedef enum {
    I2C_1 = (int)I2C1_BASE,
    I2C_2 = (int)I2C2_BASE,
    I2C_3 = (int)I2C3_BASE
} I2CName;

typedef enum {
    PWM_1  = (int)TIM1_BASE,
    PWM_2  = (int)TIM2_BASE,
    PWM_3  = (int)TIM3_BASE,
    PWM_4  = (int)TIM4_BASE,
    PWM_5  = (int)TIM5_BASE,
    PWM_8  = (int)TIM8_BASE,
    PWM_9  = (int)TIM9_BASE,
    PWM_10 = (int)TIM10_BASE,
    PWM_11 = (int)TIM11_BASE,
    PWM_13 = (int)TIM13_BASE,
    PWM_14 = (int)TIM14_BASE
} PWMName;

#ifdef __cplusplus
}
#endif

#endif
