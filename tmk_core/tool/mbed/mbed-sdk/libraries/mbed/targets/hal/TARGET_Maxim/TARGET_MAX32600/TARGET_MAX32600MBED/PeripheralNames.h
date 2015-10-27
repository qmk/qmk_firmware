/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */
 
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UART_0 = MXC_BASE_UART0,
    UART_1 = MXC_BASE_UART1,
    STDIO_UART = UART_1
} UARTName;

typedef enum {
    I2C_0 = MXC_BASE_I2CM0,
    I2C_1 = MXC_BASE_I2CM1
} I2CName;

typedef enum {
    SPI_0 = MXC_BASE_SPI0,
    SPI_1 = MXC_BASE_SPI1,
    SPI_2 = MXC_BASE_SPI2
} SPIName;

typedef enum {
    PWM_0 = MXC_BASE_PT0,
    PWM_1 = MXC_BASE_PT1,
    PWM_2 = MXC_BASE_PT2,
    PWM_3 = MXC_BASE_PT3,
    PWM_4 = MXC_BASE_PT4,
    PWM_5 = MXC_BASE_PT5,
    PWM_6 = MXC_BASE_PT6,
    PWM_7 = MXC_BASE_PT7
} PWMName;

typedef enum {
    ADC = MXC_BASE_ADC
} ADCName;

typedef enum {
    DAC0 = MXC_BASE_DAC0,
    DAC1 = MXC_BASE_DAC1,
    DAC2 = MXC_BASE_DAC2,
    DAC3 = MXC_BASE_DAC3,
} DACName;

#ifdef __cplusplus
}
#endif

#endif
