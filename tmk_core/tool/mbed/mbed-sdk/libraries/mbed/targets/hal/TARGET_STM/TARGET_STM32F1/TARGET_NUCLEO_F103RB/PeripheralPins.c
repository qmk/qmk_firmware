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

#include "PeripheralPins.h"

// =====
// Note: Commented lines are alternative possibilities which are not used per default.
//       If you change them, you will have also to modify the corresponding xxx_api.c file
//       for pwmout, analogin, analogout, ...
// =====

//*** ADC ***

const PinMap PinMap_ADC[] = {
    {PA_0, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN0
    {PA_1, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN1
    {PA_2, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN2
    {PA_3, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN3
    {PA_4, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN4
    {PA_5, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN5
    {PA_6, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN6
    {PA_7, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN7
    {PB_0, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN8
    {PB_1, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN9
    {PC_0, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN10
    {PC_1, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN11
    {PC_2, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN12
    {PC_3, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN13
    {PC_4, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN14
    {PC_5, ADC_1, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0)}, // ADC12_IN15
    {NC,   NC,    0}
};

//*** I2C ***

const PinMap PinMap_I2C_SDA[] = {
    {PB_7,  I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {PB_9,  I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 2)}, // GPIO_Remap_I2C1
    {PB_11, I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PB_6,  I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {PB_8,  I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 2)}, // GPIO_Remap_I2C1
    {PB_10, I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

//*** PWM ***

// TIM4 cannot be used because already used by the us_ticker
const PinMap PinMap_PWM[] = {
    {PA_1,  PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM2_CH2 - Default
    {PA_2,  PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM2_CH3 - Default (warning: not connected on D1 per default)
    {PA_3,  PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM2_CH4 - Default (warning: not connected on D0 per default)
    {PA_6,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM3_CH1 - Default
    {PA_7,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM3_CH2 - Default
//  {PA_7,  PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 6)}, // TIM1_CH1N - GPIO_PartialRemap_TIM1
    {PA_8,  PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH1 - Default
    {PA_9,  PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH2 - Default
    {PA_10, PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH3 - Default
    {PA_11, PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH4 - Default
    {PA_15, PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 8)}, // TIM2_CH1_ETR - GPIO_FullRemap_TIM2

    {PB_0,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM3_CH3 - Default
//  {PB_0,  PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 6)}, // TIM1_CH2N - GPIO_PartialRemap_TIM1
    {PB_1,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM3_CH4 - Default
//  {PB_1,  PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 6)}, // TIM1_CH3N - GPIO_PartialRemap_TIM1
    {PB_3,  PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 8)}, // TIM2_CH2 - GPIO_FullRemap_TIM2
    {PB_4,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 7)}, // TIM3_CH1 - GPIO_PartialRemap_TIM3
    {PB_5,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 7)}, // TIM3_CH2 - GPIO_PartialRemap_TIM3
//  {PB_6,  PWM_4, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM4_CH1 - Default (used by ticker)
//  {PB_7,  PWM_4, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM4_CH2 - Default (used by ticker)
//  {PB_8,  PWM_4, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM4_CH3 - Default (used by ticker)
//  {PB_9,  PWM_4, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM4_CH4 - Default (used by ticker)
    {PB_10, PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 8)}, // TIM2_CH3 - GPIO_FullRemap_TIM2
    {PB_11, PWM_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 8)}, // TIM2_CH4 - GPIO_FullRemap_TIM2
    {PB_13, PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH1N - Default
    {PB_14, PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH2N - Default
    {PB_15, PWM_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)}, // TIM1_CH3N - Default

    {PC_6,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 9)}, // TIM3_CH1 - GPIO_FullRemap_TIM3
    {PC_7,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 9)}, // TIM3_CH2 - GPIO_FullRemap_TIM3
    {PC_8,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 9)}, // TIM3_CH3 - GPIO_FullRemap_TIM3
    {PC_9,  PWM_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 9)}, // TIM3_CH4 - GPIO_FullRemap_TIM3
    {NC,    NC,    0}
};

//*** SERIAL ***

const PinMap PinMap_UART_TX[] = {
    {PA_2,  UART_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PA_9,  UART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB_6,  UART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 3)}, // GPIO_Remap_USART1
    {PB_10, UART_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PC_10, UART_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 5)}, // GPIO_PartialRemap_USART3
    {NC,    NC,     0}
};

const PinMap PinMap_UART_RX[] = {
    {PA_3,  UART_2, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 0)},
    {PA_10, UART_1, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 0)},
    {PB_7,  UART_1, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 3)}, // GPIO_Remap_USART1
    {PB_11, UART_3, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 0)},
    {PC_11, UART_3, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 5)}, // GPIO_PartialRemap_USART3
    {NC,    NC,     0}
};

//*** SPI ***

const PinMap PinMap_SPI_MOSI[] = {
    {PA_7,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {PB_5,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 1)}, // GPIO_Remap_SPI1
    {PB_15, SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_SPI_MISO[] = {
    {PA_6,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {PB_4,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 1)}, // GPIO_Remap_SPI1
    {PB_14, SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_SPI_SCLK[] = {
    {PA_5,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {PB_3,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 1)}, // GPIO_Remap_SPI1
    {PB_13, SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {PA_4,  SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {PA_15, SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 1)}, // GPIO_Remap_SPI1
    {PB_12, SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};
