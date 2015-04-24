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
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

// See stm32f4xx_hal_gpio.h and stm32f4xx_hal_gpio_ex.h for values of MODE, PUPD and AFNUM
#define STM_PIN_DATA(MODE, PUPD, AFNUM)  ((int)(((AFNUM) << 7) | ((PUPD) << 4) | ((MODE) << 0)))
#define STM_PIN_DATA_EXT(MODE, PUPD, AFNUM, CHANNEL, INVERTED)  ((int)(((INVERTED & 0x01) << 15) | ((CHANNEL & 0x0F) << 11) | ((AFNUM & 0x0F) << 7) | ((PUPD & 0x07) << 4) | ((MODE & 0x0F) << 0)))
#define STM_PIN_MODE(X)   (((X) >> 0) & 0x0F)
#define STM_PIN_PUPD(X)   (((X) >> 4) & 0x07)
#define STM_PIN_AFNUM(X)  (((X) >> 7) & 0x0F)
#define STM_PIN_AFNUM(X)    (((X) >> 7)  & 0x0F)
#define STM_PIN_CHANNEL(X)  (((X) >> 11) & 0x0F)
#define STM_PIN_INVERTED(X) (((X) >> 15) & 0x01)
#define STM_MODE_INPUT              (0)
#define STM_MODE_OUTPUT_PP          (1)
#define STM_MODE_OUTPUT_OD          (2)
#define STM_MODE_AF_PP              (3)
#define STM_MODE_AF_OD              (4)
#define STM_MODE_ANALOG             (5)
#define STM_MODE_IT_RISING          (6)
#define STM_MODE_IT_FALLING         (7)
#define STM_MODE_IT_RISING_FALLING  (8)
#define STM_MODE_EVT_RISING         (9)
#define STM_MODE_EVT_FALLING        (10)
#define STM_MODE_EVT_RISING_FALLING (11)
#define STM_MODE_IT_EVT_RESET       (12)

// High nibble = port number (0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H)
// Low nibble  = pin number
#define STM_PORT(X) (((uint32_t)(X) >> 4) & 0xF)
#define STM_PIN(X)  ((uint32_t)(X) & 0xF)

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

typedef enum {
    PA_0  = 0x00,
    PA_1  = 0x01,
    PA_2  = 0x02,
    PA_3  = 0x03,
    PA_4  = 0x04,
    PA_5  = 0x05,
    PA_6  = 0x06,
    PA_7  = 0x07,
    PA_8  = 0x08,
    PA_9  = 0x09,
    PA_10 = 0x0A,
    PA_11 = 0x0B,
    PA_12 = 0x0C,
    PA_13 = 0x0D,
    PA_14 = 0x0E,
    PA_15 = 0x0F,

    PB_0  = 0x10,
    PB_1  = 0x11,
    PB_2  = 0x12,
    PB_3  = 0x13,
    PB_4  = 0x14,
    PB_5  = 0x15,
    PB_6  = 0x16,
    PB_7  = 0x17,
    PB_8  = 0x18,
    PB_9  = 0x19,
    PB_10 = 0x1A,
    PB_12 = 0x1C,
    PB_13 = 0x1D,
    PB_14 = 0x1E,
    PB_15 = 0x1F,

    PC_0  = 0x20,
    PC_1  = 0x21,
    PC_2  = 0x22,
    PC_3  = 0x23,
    PC_4  = 0x24,
    PC_5  = 0x25,
    PC_6  = 0x26,
    PC_7  = 0x27,
    PC_8  = 0x28,
    PC_9  = 0x29,
    PC_10 = 0x2A,
    PC_11 = 0x2B,
    PC_12 = 0x2C,
    PC_13 = 0x2D,
    PC_14 = 0x2E,
    PC_15 = 0x2F,

    PD_2  = 0x32,

    PH_0  = 0x70,
    PH_1  = 0x71,

    // Arduino connector namings
    A0          = PA_0,
    A1          = PA_1,
    A2          = PA_4,
    A3          = PB_0,
    A4          = PC_1,
    A5          = PC_0,
    D0          = PA_3,
    D1          = PA_2,
    D2          = PA_10,
    D3          = PB_3,
    D4          = PB_5,
    D5          = PB_4,
    D6          = PB_10,
    D7          = PA_8,
    D8          = PA_9,
    D9          = PC_7,
    D10         = PB_6,
    D11         = PA_7,
    D12         = PA_6,
    D13         = PA_5,
    D14         = PB_9,
    D15         = PB_8,

    // Generic signals namings
    LED1        = PA_5,
    LED2        = PA_5,
    LED3        = PA_5,
    LED4        = PA_5,
    USER_BUTTON = PC_13,
    SERIAL_TX   = PA_2,
    SERIAL_RX   = PA_3,
    USBTX       = PA_2,
    USBRX       = PA_3,
    I2C_SCL     = PB_8,
    I2C_SDA     = PB_9,
    SPI_MOSI    = PA_7,
    SPI_MISO    = PA_6,
    SPI_SCK     = PA_5,
    SPI_CS      = PB_6,
    PWM_OUT     = PB_3,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullNone  = 0,
    PullUp    = 1,
    PullDown  = 2,
    OpenDrain = 3,
    PullDefault = PullNone
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
