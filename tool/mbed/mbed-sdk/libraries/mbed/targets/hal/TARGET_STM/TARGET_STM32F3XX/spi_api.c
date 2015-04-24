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
#include "mbed_assert.h"
#include "spi_api.h"

#if DEVICE_SPI

#include <math.h>
#include "cmsis.h"
#include "pinmap.h"

static const PinMap PinMap_SPI_MOSI[] = {
    {PA_11, SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {PB_5,  SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {PB_15, SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {PC_12, SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {NC,    NC,    0}
};

static const PinMap PinMap_SPI_MISO[] = {
    {PA_10, SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {PB_4,  SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {PB_14, SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {PC_11, SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {NC,    NC,    0}
};

static const PinMap PinMap_SPI_SCLK[] = {
    {PB_3,  SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {PB_13, SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {PC_10, SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {PF_1,  SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {NC,    NC,    0}
};

static const PinMap PinMap_SPI_SSEL[] = {
    {PA_4,  SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {PA_15, SPI_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_6)},
    {PB_12, SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {PF_0,  SPI_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_AF_5)},
    {NC,    NC,    0}
};

static void init_spi(spi_t *obj) {
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    SPI_InitTypeDef SPI_InitStructure;

    SPI_Cmd(spi, DISABLE);

    SPI_InitStructure.SPI_Mode              = obj->mode;
    SPI_InitStructure.SPI_NSS               = obj->nss;
    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize          = obj->bits;
    SPI_InitStructure.SPI_CPOL              = obj->cpol;
    SPI_InitStructure.SPI_CPHA              = obj->cpha;
    SPI_InitStructure.SPI_BaudRatePrescaler = obj->br_presc;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial     = 7;
    SPI_Init(spi, &SPI_InitStructure);

    SPI_RxFIFOThresholdConfig(spi, SPI_RxFIFOThreshold_QF);

    SPI_Cmd(spi, ENABLE);
}

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel) {
    // Determine the SPI to use
    SPIName spi_mosi = (SPIName)pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    SPIName spi_miso = (SPIName)pinmap_peripheral(miso, PinMap_SPI_MISO);
    SPIName spi_sclk = (SPIName)pinmap_peripheral(sclk, PinMap_SPI_SCLK);
    SPIName spi_ssel = (SPIName)pinmap_peripheral(ssel, PinMap_SPI_SSEL);

    SPIName spi_data = (SPIName)pinmap_merge(spi_mosi, spi_miso);
    SPIName spi_cntl = (SPIName)pinmap_merge(spi_sclk, spi_ssel);

    obj->spi = (SPIName)pinmap_merge(spi_data, spi_cntl);

    MBED_ASSERT(obj->spi != (SPIName)NC);

    // Enable SPI clock
    if (obj->spi == SPI_2) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    }
    if (obj->spi == SPI_3) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    }

    // Configure the SPI pins
    pinmap_pinout(mosi, PinMap_SPI_MOSI);
    pinmap_pinout(miso, PinMap_SPI_MISO);
    pinmap_pinout(sclk, PinMap_SPI_SCLK);

    // Save new values
    obj->bits = SPI_DataSize_8b;
    obj->cpol = SPI_CPOL_Low;
    obj->cpha = SPI_CPHA_1Edge;
    obj->br_presc = SPI_BaudRatePrescaler_256;

    if (ssel == NC) { // Master
        obj->mode = SPI_Mode_Master;
        obj->nss = SPI_NSS_Soft;
    } else { // Slave
        pinmap_pinout(ssel, PinMap_SPI_SSEL);
        obj->mode = SPI_Mode_Slave;
        obj->nss = SPI_NSS_Soft;
    }

    init_spi(obj);
}

void spi_free(spi_t *obj) {
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    SPI_I2S_DeInit(spi);
}

void spi_format(spi_t *obj, int bits, int mode, int slave) {
    // Save new values
    if (bits == 8) {
        obj->bits = SPI_DataSize_8b;
    } else {
        obj->bits = SPI_DataSize_16b;
    }

    switch (mode) {
        case 0:
            obj->cpol = SPI_CPOL_Low;
            obj->cpha = SPI_CPHA_1Edge;
            break;
        case 1:
            obj->cpol = SPI_CPOL_Low;
            obj->cpha = SPI_CPHA_2Edge;
            break;
        case 2:
            obj->cpol = SPI_CPOL_High;
            obj->cpha = SPI_CPHA_1Edge;
            break;
        default:
            obj->cpol = SPI_CPOL_High;
            obj->cpha = SPI_CPHA_2Edge;
            break;
    }

    if (slave == 0) {
        obj->mode = SPI_Mode_Master;
        obj->nss = SPI_NSS_Soft;
    } else {
        obj->mode = SPI_Mode_Slave;
        obj->nss = SPI_NSS_Hard;
    }

    init_spi(obj);
}

void spi_frequency(spi_t *obj, int hz) {
    // Values depend of PCLK1: 32 MHz if HSI is used, 36 MHz if HSE is used
    if (hz < 250000) {
        obj->br_presc = SPI_BaudRatePrescaler_256; // 125 kHz - 141 kHz
    } else if ((hz >= 250000) && (hz < 500000)) {
        obj->br_presc = SPI_BaudRatePrescaler_128; // 250 kHz - 280 kHz
    } else if ((hz >= 500000) && (hz < 1000000)) {
        obj->br_presc = SPI_BaudRatePrescaler_64; // 500 kHz - 560 kHz
    } else if ((hz >= 1000000) && (hz < 2000000)) {
        obj->br_presc = SPI_BaudRatePrescaler_32; // 1 MHz - 1.13 MHz
    } else if ((hz >= 2000000) && (hz < 4000000)) {
        obj->br_presc = SPI_BaudRatePrescaler_16; // 2 MHz - 2.25 MHz
    } else if ((hz >= 4000000) && (hz < 8000000)) {
        obj->br_presc = SPI_BaudRatePrescaler_8; // 4 MHz - 4.5 MHz
    } else if ((hz >= 8000000) && (hz < 16000000)) {
        obj->br_presc = SPI_BaudRatePrescaler_4; // 8 MHz - 9 MHz
    } else { // >= 16000000
        obj->br_presc = SPI_BaudRatePrescaler_2; // 16 MHz - 18 MHz
    }
    init_spi(obj);
}

static inline int ssp_readable(spi_t *obj) {
    int status;
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    // Check if data is received
    status = ((SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_RXNE) != RESET) ? 1 : 0);
    return status;
}

static inline int ssp_writeable(spi_t *obj) {
    int status;
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    // Check if data is transmitted
    status = ((SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_TXE) != RESET) ? 1 : 0);
    return status;
}

static inline void ssp_write(spi_t *obj, int value) {
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_writeable(obj));
    if (obj->bits == SPI_DataSize_8b) {
        SPI_SendData8(spi, (uint8_t)value);
    } else {
        SPI_I2S_SendData16(spi, (uint16_t)value);
    }
}

static inline int ssp_read(spi_t *obj) {
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_readable(obj));
    if (obj->bits == SPI_DataSize_8b) {
        return (int)SPI_ReceiveData8(spi);
    } else {
        return (int)SPI_I2S_ReceiveData16(spi);
    }
}

static inline int ssp_busy(spi_t *obj) {
    int status;
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    status = ((SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_BSY) != RESET) ? 1 : 0);
    return status;
}

int spi_master_write(spi_t *obj, int value) {
    ssp_write(obj, value);
    return ssp_read(obj);
}

int spi_slave_receive(spi_t *obj) {
    return (ssp_readable(obj) && !ssp_busy(obj)) ? (1) : (0);
};

int spi_slave_read(spi_t *obj) {
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    if (obj->bits == SPI_DataSize_8b) {
        return (int)SPI_ReceiveData8(spi);
    } else {
        return (int)SPI_I2S_ReceiveData16(spi);
    }
}

void spi_slave_write(spi_t *obj, int value) {
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_writeable(obj));
    if (obj->bits == SPI_DataSize_8b) {
        SPI_SendData8(spi, (uint8_t)value);
    } else {
        SPI_I2S_SendData16(spi, (uint16_t)value);
    }
}

int spi_busy(spi_t *obj) {
    return ssp_busy(obj);
}

#endif
