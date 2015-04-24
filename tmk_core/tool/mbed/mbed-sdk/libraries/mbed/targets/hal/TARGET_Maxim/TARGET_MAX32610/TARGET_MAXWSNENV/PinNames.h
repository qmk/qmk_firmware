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

    // Analog ADC pins
    AIN_0P = (0xA << PORT_SHIFT) | 0,
    AIN_1P = (0xA << PORT_SHIFT) | 1,
    AIN_2P = (0xA << PORT_SHIFT) | 2,
    AIN_3P = (0xA << PORT_SHIFT) | 3,
    AIN_4P = (0xA << PORT_SHIFT) | 4,
    AIN_5P = (0xA << PORT_SHIFT) | 5,
    AIN_0N = (0xB << PORT_SHIFT) | 0,
    AIN_1N = (0xB << PORT_SHIFT) | 1,
    AIN_2N = (0xB << PORT_SHIFT) | 2,
    AIN_3N = (0xB << PORT_SHIFT) | 3,
    AIN_4N = (0xB << PORT_SHIFT) | 4,
    AIN_5N = (0xB << PORT_SHIFT) | 5,

    // Analog differential ADC
    AIN_0D = (0xC << PORT_SHIFT) | 0,
    AIN_1D = (0xC << PORT_SHIFT) | 1,
    AIN_2D = (0xC << PORT_SHIFT) | 2,
    AIN_3D = (0xC << PORT_SHIFT) | 3,
    AIN_4D = (0xC << PORT_SHIFT) | 4,
    AIN_5D = (0xC << PORT_SHIFT) | 5,

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

    LED_RED = P1_7,
    LED_GREEN = P1_6,
    LED_BLUE = P1_4,

    // mbed original LED naming
    LED1 = LED_RED,
    LED2 = LED_GREEN,
    LED3 = LED_BLUE,
    LED4 = LED_BLUE,

    // Push button
    SW1 = P1_5,

    // UART Pins
    USBTX = P1_3,
    USBRX = P1_2,
    STDIO_UART_TX = USBTX,
    STDIO_UART_RX = USBRX,

    I2C_SCL = P0_5,
    I2C_SDA = P0_4,

    // BTLE Radio HCI
    HCI_SCK = P2_0,
    HCI_MOSI = P2_1,
    HCI_MISO = P2_2,
    HCI_CSN = P2_3,
    HCI_IRQ = P2_4,
    HCI_RST = P2_5,

    // Test points
    TP1 = P1_1,
    TP2 = P1_0,
    TP3 = P0_1,
    TP4 = P0_0,
    TP5 = P0_5,
    TP6 = P0_4,

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
