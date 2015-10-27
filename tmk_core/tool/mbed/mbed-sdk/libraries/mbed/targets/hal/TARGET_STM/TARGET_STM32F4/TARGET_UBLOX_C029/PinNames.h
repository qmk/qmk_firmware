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
    PA_0  = 0x00, PA_1  = 0x01, PA_2  = 0x02, PA_3  = 0x03,
    PA_4  = 0x04, PA_5  = 0x05, PA_6  = 0x06, PA_7  = 0x07,
    PA_8  = 0x08, PA_9  = 0x09, PA_10 = 0x0A, PA_11 = 0x0B,
    PA_12 = 0x0C, PA_13 = 0x0D, PA_14 = 0x0E, PA_15 = 0x0F,

    PB_0  = 0x10, PB_1  = 0x11, PB_2  = 0x12, PB_3  = 0x13,
    PB_4  = 0x14, PB_5  = 0x15, PB_6  = 0x16, PB_7  = 0x17,
    PB_8  = 0x18, PB_9  = 0x19, PB_10 = 0x1A, PB_11 = 0x1B,
    PB_12 = 0x1C, PB_13 = 0x1D, PB_14 = 0x1E, PB_15 = 0x1F,

    PC_0  = 0x20, PC_1  = 0x21, PC_2  = 0x22, PC_3  = 0x23,
    PC_4  = 0x24, PC_5  = 0x25, PC_6  = 0x26, PC_7  = 0x27,
    PC_8  = 0x28, PC_9  = 0x29, PC_10 = 0x2A, PC_11 = 0x2B,
    PC_12 = 0x2C, PC_13 = 0x2D, PC_14 = 0x2E, PC_15 = 0x2F,

    PD_0  = 0x30, PD_1  = 0x31, PD_2  = 0x32, PD_3  = 0x33,
    PD_4  = 0x34, PD_5  = 0x35, PD_6  = 0x36, PD_7  = 0x37,
    PD_8  = 0x38, PD_9  = 0x39, PD_10 = 0x3A, PD_11 = 0x3B,
    PD_12 = 0x3C, PD_13 = 0x3D, PD_14 = 0x3E, PD_15 = 0x3F,
    
    PE_0  = 0x40, PE_1  = 0x41, PE_2  = 0x42, PE_3  = 0x43,
    PE_4  = 0x44, PE_5  = 0x45, PE_6  = 0x46, PE_7  = 0x47,
    PE_8  = 0x48, PE_9  = 0x49, PE_10 = 0x4A, PE_11 = 0x4B,
    PE_12 = 0x4C, PE_13 = 0x4D, PE_14 = 0x4E, PE_15 = 0x4F,

    PF_0  = 0x50, PF_1  = 0x51, PF_2  = 0x52, PF_3  = 0x53,
    PF_4  = 0x54, PF_5  = 0x55, PF_6  = 0x56, PF_7  = 0x57,
    PF_8  = 0x58, PF_9  = 0x59, PF_10 = 0x5A, PF_11 = 0x5B,
    PF_12 = 0x5C, PF_13 = 0x5D, PF_14 = 0x5E, PF_15 = 0x5F,

    PG_0  = 0x60, PG_1  = 0x61, PG_2  = 0x62, PG_3  = 0x63,
    PG_4  = 0x64, PG_5  = 0x65, PG_6  = 0x66, PG_7  = 0x67,
    PG_8  = 0x68, PG_9  = 0x69, PG_10 = 0x6A, PG_11 = 0x6B,
    PG_12 = 0x6C, PG_13 = 0x6D, PG_14 = 0x6E, PG_15 = 0x6F,

    PH_0  = 0x70, PH_1  = 0x71, PH_2  = 0x72, PH_3  = 0x73,
    PH_4  = 0x74, PH_5  = 0x75, PH_6  = 0x76, PH_7  = 0x77,
    PH_8  = 0x78, PH_9  = 0x79, PH_10 = 0x7A, PH_11 = 0x7B,
    PH_12 = 0x7C, PH_13 = 0x7D, PH_14 = 0x7E, PH_15 = 0x7F,

    // Module Pins
    // A
    P_A5    = PC_2,   // UART-DTR
    P_A6    = PF_2,   // Switch-0
    P_A7    = PE_0,   // Red, Mode
    P_A8    = PB_6,   // Green, Switch-1
    P_A9    = PB_8,   // Blue
    P_A10   = PA_11,  // UART-CTS
    P_A11   = PA_9,   // UART-TXD
    P_A12   = PA_12,  // UART-RTS
    P_A13   = PA_10,  // UART-RXD
    P_A14   = PD_9,   // GPIO-0
    P_A15   = PD_8,   // GPIO-1
    P_A16   = PD_11,  // GPIO-2
    P_A17   = PD_12,  // GPIO-3
    P_A18   = PA_3,   // UART-DSR
    // B
    // C
    P_C5    = PG_4,   // SPI-IRQ
    P_C6    = PE_13,  // SPI-MISO
    P_C8    = PE_12,  // Res
    P_C10   = PE_14,  // SPI-MOSI
    P_C11   = PE_11,  // SPI-CS0
    P_C12   = PE_9,   // Res
    P_C13   = PF_6,   // GPIO-4
    P_C14   = PC_1,   // RMII-MDC
    P_C15   = PA_2,   // RMII-MDIO
    P_C16   = PF_7,   // GPIO-7
    P_C17   = PF_1,   // I2C-SCL
    P_C18   = PF_0,   // I2C-SDA
    // D
    P_D1    = PB_12,  // RMII-TXD0
    P_D2    = PB_13,  // RMII-TXD1
    P_D3    = PB_11,  // RMII-TXEN
    P_D4    = PA_7,   // RMII-CRSDV
    P_D5    = PC_4,   // RMII-RXD0
    P_D6    = PC_5,   // RMII-RXD1
    P_D8    = PA_1,   // RMII-REFCLK
    // TP
    P_TP5   = PB_4,   // NTRST
    P_TP7   = PA_13,  // TMS  SWDIO
    P_TP8   = PA_15,  // TDI
    P_TP9   = PA_14,  // TCK  SWCLK
    P_TP10  = PB_3,   // TDO  

    // Board Pins
    // A0-A5
    A0      = PF_7,
    A1      = PF_6,
    A2      = PA_3,
    A3      = PC_2,
    A4      = PG_4,  // not AI
    A5      = PB_3,  // not AI
    // D0-D15
    D0      = PD_9,   // RX
    D1      = PD_8,   // TX
    D2      = PA_10,  // RX
    D3      = PA_11,
    D4      = PA_12,
    D5      = PA_15,
    D6      = PD_11,
    D7      = PD_12,
    D8      = PA_9,   // TX
    D9      = PE_9,   // shared with SW1
    D10     = PE_11,  // SSEL
    D11     = PE_14,  // MOSI
    D12     = PE_13,  // MISO
    D13     = PE_12,  // SCK
    D14     = PF_0,   // SDA
    D15     = PF_1,   // SCL
    // Internal
    LED1    = PE_0,   // Red
    LED2    = PB_6,   // Green / shared with SW1
    LED_RED = PE_0,   // Red
    LED_GRE = PB_6,   // Green / shared with SW1
    LED_BLU = PB_8,   // Blue
    SW0     = PF_2,	  // Switch 0
    SW1     = PB_6,   // Switch 1 / shared with LED_GRE
    SDCS    = PE_9,   // SD Card CS / shared with D9
    USBRXD  = PD_9,   // RX
    USBTXD  = PD_8,   // TX

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
