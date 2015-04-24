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
 
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"
#include "gpio_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT  = MXC_V_GPIO_OUT_MODE_HIGH_Z,
    PIN_OUTPUT = MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE
} PinDirection;

#define PORT_SHIFT  12
#define PINNAME_TO_PORT(name)   ((unsigned int)(name) >> PORT_SHIFT)
#define PINNAME_TO_PIN(name)    ((unsigned int)(name) & ~(0xFFFFFFFF << PORT_SHIFT))

typedef enum {
    P0_0 = (0 << PORT_SHIFT) | 0,
    P0_1 = (0 << PORT_SHIFT) | 1,
    P0_2 = (0 << PORT_SHIFT) | 2,
    P0_3 = (0 << PORT_SHIFT) | 3,
    P0_4 = (0 << PORT_SHIFT) | 4,
    P0_5 = (0 << PORT_SHIFT) | 5,
    P0_6 = (0 << PORT_SHIFT) | 6,
    P0_7 = (0 << PORT_SHIFT) | 7,

    P1_0 = (1 << PORT_SHIFT) | 0,
    P1_1 = (1 << PORT_SHIFT) | 1,
    P1_2 = (1 << PORT_SHIFT) | 2,
    P1_3 = (1 << PORT_SHIFT) | 3,
    P1_4 = (1 << PORT_SHIFT) | 4,
    P1_5 = (1 << PORT_SHIFT) | 5,
    P1_6 = (1 << PORT_SHIFT) | 6,
    P1_7 = (1 << PORT_SHIFT) | 7,

    P2_0 = (2 << PORT_SHIFT) | 0,
    P2_1 = (2 << PORT_SHIFT) | 1,
    P2_2 = (2 << PORT_SHIFT) | 2,
    P2_3 = (2 << PORT_SHIFT) | 3,
    P2_4 = (2 << PORT_SHIFT) | 4,
    P2_5 = (2 << PORT_SHIFT) | 5,
    P2_6 = (2 << PORT_SHIFT) | 6,
    P2_7 = (2 << PORT_SHIFT) | 7,

    P3_0 = (3 << PORT_SHIFT) | 0,
    P3_1 = (3 << PORT_SHIFT) | 1,
    P3_2 = (3 << PORT_SHIFT) | 2,
    P3_3 = (3 << PORT_SHIFT) | 3,
    P3_4 = (3 << PORT_SHIFT) | 4,
    P3_5 = (3 << PORT_SHIFT) | 5,
    P3_6 = (3 << PORT_SHIFT) | 6,
    P3_7 = (3 << PORT_SHIFT) | 7,

    P4_0 = (4 << PORT_SHIFT) | 0,
    P4_1 = (4 << PORT_SHIFT) | 1,
    P4_2 = (4 << PORT_SHIFT) | 2,
    P4_3 = (4 << PORT_SHIFT) | 3,
    P4_4 = (4 << PORT_SHIFT) | 4,
    P4_5 = (4 << PORT_SHIFT) | 5,
    P4_6 = (4 << PORT_SHIFT) | 6,
    P4_7 = (4 << PORT_SHIFT) | 7,

    P5_0 = (5 << PORT_SHIFT) | 0,
    P5_1 = (5 << PORT_SHIFT) | 1,
    P5_2 = (5 << PORT_SHIFT) | 2,
    P5_3 = (5 << PORT_SHIFT) | 3,
    P5_4 = (5 << PORT_SHIFT) | 4,
    P5_5 = (5 << PORT_SHIFT) | 5,
    P5_6 = (5 << PORT_SHIFT) | 6,
    P5_7 = (5 << PORT_SHIFT) | 7,

    P6_0 = (6 << PORT_SHIFT) | 0,
    P6_1 = (6 << PORT_SHIFT) | 1,
    P6_2 = (6 << PORT_SHIFT) | 2,
    P6_3 = (6 << PORT_SHIFT) | 3,
    P6_4 = (6 << PORT_SHIFT) | 4,
    P6_5 = (6 << PORT_SHIFT) | 5,
    P6_6 = (6 << PORT_SHIFT) | 6,
    P6_7 = (6 << PORT_SHIFT) | 7,

    P7_0 = (7 << PORT_SHIFT) | 0,
    P7_1 = (7 << PORT_SHIFT) | 1,
    P7_2 = (7 << PORT_SHIFT) | 2,
    P7_3 = (7 << PORT_SHIFT) | 3,
    P7_4 = (7 << PORT_SHIFT) | 4,
    P7_5 = (7 << PORT_SHIFT) | 5,
    P7_6 = (7 << PORT_SHIFT) | 6,
    P7_7 = (7 << PORT_SHIFT) | 7,

    // Analog ADC pins
    AIN_0P = (0xA << PORT_SHIFT) | 0,
    AIN_1P = (0xA << PORT_SHIFT) | 1,
    AIN_2P = (0xA << PORT_SHIFT) | 2,
    AIN_3P = (0xA << PORT_SHIFT) | 3,
    AIN_4P = (0xA << PORT_SHIFT) | 4,
    AIN_5P = (0xA << PORT_SHIFT) | 5,
    AIN_6P = (0xA << PORT_SHIFT) | 6,
    AIN_7P = (0xA << PORT_SHIFT) | 7,

    AIN_0N = (0xB << PORT_SHIFT) | 0,
    AIN_1N = (0xB << PORT_SHIFT) | 1,
    AIN_2N = (0xB << PORT_SHIFT) | 2,
    AIN_3N = (0xB << PORT_SHIFT) | 3,
    AIN_4N = (0xB << PORT_SHIFT) | 4,
    AIN_5N = (0xB << PORT_SHIFT) | 5,
    AIN_6N = (0xB << PORT_SHIFT) | 6,
    AIN_7N = (0xB << PORT_SHIFT) | 7,

    // Analog differential ADC
    AIN_0D = (0xC << PORT_SHIFT) | 0,
    AIN_1D = (0xC << PORT_SHIFT) | 1,
    AIN_2D = (0xC << PORT_SHIFT) | 2,
    AIN_3D = (0xC << PORT_SHIFT) | 3,
    AIN_4D = (0xC << PORT_SHIFT) | 4,
    AIN_5D = (0xC << PORT_SHIFT) | 5,
    AIN_6D = (0xC << PORT_SHIFT) | 6,
    AIN_7D = (0xC << PORT_SHIFT) | 7,

    // OPAMP Positive supply pins
    AOUT_AP = (0xD << PORT_SHIFT) | 0,
    AOUT_BP = (0xD << PORT_SHIFT) | 1,
    AOUT_CP = (0xD << PORT_SHIFT) | 2,
    AOUT_DP = (0xD << PORT_SHIFT) | 3,

    // OPAMP Negative supply pins
    AOUT_AN = (0xE << PORT_SHIFT) | 0,
    AOUT_BN = (0xE << PORT_SHIFT) | 1,
    AOUT_CN = (0xE << PORT_SHIFT) | 2,
    AOUT_DN = (0xE << PORT_SHIFT) | 3,

    // DAC Output pins
    AOUT_AO = (0xF << PORT_SHIFT) | 0,
    AOUT_BO = (0xF << PORT_SHIFT) | 1,
    AOUT_CO = (0xF << PORT_SHIFT) | 2,
    AOUT_DO = (0xF << PORT_SHIFT) | 3,

    LED_GREEN  = P7_4,
    LED_RED    = P7_0,
    LED_YELLOW = P6_6,
    LED_BLUE   = P7_6,

    // mbed original LED naming
    LED1 = LED_RED,
    LED2 = LED_GREEN,
    LED3 = LED_BLUE,
    LED4 = LED_YELLOW,

    // Push button
    SW2 = P6_4,
    SW3 = P6_5,

    // UART pins
    USBTX = P7_3,
    USBRX = P7_2,
    STDIO_UART_TX = USBTX,
    STDIO_UART_RX = USBRX,

    // I2C pins
    I2C0_SCL = P2_4,
    I2C0_SDA = P2_5,

    I2C1_SCL = P2_7,
    I2C1_SDA = P2_6,

    // UART pins
    UART0_RX  = P1_0,
    UART0_TX  = P1_1,
    UART0_CTS = P1_2,
    UART0_RTS = P1_3,

    UART1_RX  = P1_2,
    UART1_TX  = P1_3,
    UART1_CTS = P2_6,
    UART1_RTS = P2_7,

    // SPI pins
    SPI0_SCK  = P6_0,
    SPI0_MOSI = P6_1,
    SPI0_MISO = P6_2,
    SPI0_SS   = P6_3,

    SPI2_SCK  = P2_0,
    SPI2_MOSI = P2_1,
    SPI2_MISO = P2_2,
    SPI2_SS   = P2_3,

    // Arduino Headers
    D0  = P1_0,
    D1  = P1_1,
    D2  = P1_2,
    D3  = P1_3,
    D4  = P1_4,
    D5  = P1_5,
    D6  = P1_6,
    D7  = P1_7,
    D8  = P2_5,
    D9  = P2_4,
    D10 = P2_3,
    D11 = P2_1,
    D12 = P2_2,
    D13 = P2_0,
    D14 = P2_6,
    D15 = P2_7,
    A0  = AIN_0P,
    A1  = AIN_1P,
    A2  = AIN_2P,
    A3  = AIN_3P,
    A4  = AIN_4P,
    A5  = AIN_5P,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullUp,
    OpenDrain,
    PullNone,
    PullDefault = PullUp
} PinMode;

typedef enum {
    LED_ON = 0,
    LED_OFF = 1
} LedStates;

#ifdef __cplusplus
}
#endif

#endif
