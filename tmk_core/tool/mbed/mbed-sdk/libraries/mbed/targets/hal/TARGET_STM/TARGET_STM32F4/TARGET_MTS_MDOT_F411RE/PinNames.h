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

    // Generic signals namings
    XBEE_DOUT        = PA_2,
    XBEE_DIN         = PA_3,
    XBEE_AD0         = PB_1,
    XBEE_AD1         = PB_0,
    XBEE_AD2         = PA_5,
    XBEE_AD3         = PA_4,
    XBEE_AD4         = PA_7,
    XBEE_AD5         = PC_1,
    XBEE_AD6         = PA_1,
    XBEE_DIO0        = PB_1,
    XBEE_DIO1        = PB_0,
    XBEE_DIO2        = PA_5,
    XBEE_DIO3        = PA_4,
    XBEE_DIO4        = PA_7,
    XBEE_DIO5        = PC_1,
    XBEE_DIO6        = PA_1,
    XBEE_DO8         = PA_6,
    XBEE_DI8         = PA_11,
    XBEE_PWM0        = PA_8,
    XBEE_PWM1        = PC_9,
    XBEE_CTS         = PA_0,
    XBEE_RTS         = PA_1,
    XBEE_DTR         = PA_11,
    XBEE_RSSI        = PA_8,
    XBEE_SLEEPRQ     = PA_11,
    XBEE_ON_SLEEP    = PC_13,
    XBEE_ASSOCIATE   = PC_1,
    XBEE_USB_RES     = PA_12,

    // needed for mbed to build tests
    LED1        = PA_0,

    // XBEE_DOUT/DIN, RS232 port on UDK board
    SERIAL_TX   = PA_2,
    SERIAL_RX   = PA_3,

    // DB_TX/RX, USB port on UDK board
    DB_TX       = PA_9,
    DB_RX       = PA_10,
    USBTX       = PA_9,
    USBRX       = PA_10,

    // Multiplexed with XBEE pins
    I2C_SCL     = PA_8,
    I2C_SDA     = PC_9,
    SPI1_MOSI   = PA_7,
    SPI1_MISO   = PA_6,
    SPI1_SCK    = PA_5,
    SPI1_CS     = PA_4,

    // SPI flash
    SPI3_MOSI   = PC_12,
    SPI3_MISO   = PC_11,
    SPI3_SCK    = PC_10,
    SPI3_CS     = PC_6,
    FLASH_HOLD  = PC_7,
    FLASH_WP    = PC_8,

    // LoRa
    LORA_RESET  = PC_0,
    LORA_RXCTL  = PC_2,
    LORA_TXCTL  = PC_3,
    LORA_DIO0   = PB_5,
    LORA_DIO1   = PB_6,
    LORA_DIO2   = PB_7,
    LORA_DIO3   = PB_8,
    LORA_DIO4   = PB_9,
    LORA_DIO5   = PB_10,
    // LoRa/SPI2
    LORA_NSS    = PB_12,
    LORA_SCK    = PB_13,
    LORA_MISO   = PB_14,
    LORA_MOSI   = PB_15,

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
