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
#include "PeripheralPins.h"

static SPI_HandleTypeDef SpiHandle;

static void init_spi(spi_t *obj)
{
    SpiHandle.Instance = (SPI_TypeDef *)(obj->spi);

    __HAL_SPI_DISABLE(&SpiHandle);

    SpiHandle.Init.Mode              = obj->mode;
    SpiHandle.Init.BaudRatePrescaler = obj->br_presc;
    SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase          = obj->cpha;
    SpiHandle.Init.CLKPolarity       = obj->cpol;
    SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
    SpiHandle.Init.CRCPolynomial     = 7;
    SpiHandle.Init.DataSize          = obj->bits;
    SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.NSS               = obj->nss;
    SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLED;

    HAL_SPI_Init(&SpiHandle);

    __HAL_SPI_ENABLE(&SpiHandle);
}

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
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
    if (obj->spi == SPI_1) {
        __SPI1_CLK_ENABLE();
    }
    if (obj->spi == SPI_2) {
        __SPI2_CLK_ENABLE();
    }
    if (obj->spi == SPI_3) {
        __SPI3_CLK_ENABLE();
    }

    // Configure the SPI pins
    pinmap_pinout(mosi, PinMap_SPI_MOSI);
    pinmap_pinout(miso, PinMap_SPI_MISO);
    pinmap_pinout(sclk, PinMap_SPI_SCLK);

    // Save new values
    obj->bits = SPI_DATASIZE_8BIT;
    obj->cpol = SPI_POLARITY_LOW;
    obj->cpha = SPI_PHASE_1EDGE;
    obj->br_presc = SPI_BAUDRATEPRESCALER_256;

    obj->pin_miso = miso;
    obj->pin_mosi = mosi;
    obj->pin_sclk = sclk;
    obj->pin_ssel = ssel;

    if (ssel == NC) { // SW NSS Master mode
        obj->mode = SPI_MODE_MASTER;
        obj->nss = SPI_NSS_SOFT;
    } else { // Slave
        pinmap_pinout(ssel, PinMap_SPI_SSEL);
        obj->mode = SPI_MODE_SLAVE;
        obj->nss = SPI_NSS_HARD_INPUT;
    }

    init_spi(obj);
}

void spi_free(spi_t *obj)
{
    // Reset SPI and disable clock
    if (obj->spi == SPI_1) {
        __SPI1_FORCE_RESET();
        __SPI1_RELEASE_RESET();
        __SPI1_CLK_DISABLE();
    }

    if (obj->spi == SPI_2) {
        __SPI2_FORCE_RESET();
        __SPI2_RELEASE_RESET();
        __SPI2_CLK_DISABLE();
    }

    if (obj->spi == SPI_3) {
        __SPI3_FORCE_RESET();
        __SPI3_RELEASE_RESET();
        __SPI3_CLK_DISABLE();
    }

    // Configure GPIO
    pin_function(obj->pin_miso, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
    pin_function(obj->pin_mosi, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
    pin_function(obj->pin_sclk, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
    pin_function(obj->pin_ssel, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
}

void spi_format(spi_t *obj, int bits, int mode, int slave)
{
    // Save new values
    if (bits == 16) {
        obj->bits = SPI_DATASIZE_16BIT;
    } else {
        obj->bits = SPI_DATASIZE_8BIT;
    }

    switch (mode) {
        case 0:
            obj->cpol = SPI_POLARITY_LOW;
            obj->cpha = SPI_PHASE_1EDGE;
            break;
        case 1:
            obj->cpol = SPI_POLARITY_LOW;
            obj->cpha = SPI_PHASE_2EDGE;
            break;
        case 2:
            obj->cpol = SPI_POLARITY_HIGH;
            obj->cpha = SPI_PHASE_1EDGE;
            break;
        default:
            obj->cpol = SPI_POLARITY_HIGH;
            obj->cpha = SPI_PHASE_2EDGE;
            break;
    }

    if (slave == 0) {
        obj->mode = SPI_MODE_MASTER;
        obj->nss = SPI_NSS_SOFT;
    } else {
        obj->mode = SPI_MODE_SLAVE;
        obj->nss = SPI_NSS_HARD_INPUT;
    }

    init_spi(obj);
}

void spi_frequency(spi_t *obj, int hz)
{
    // Values depend of PCLK1 and PCLK2: 32 MHz if HSI is used, 24 MHz if HSE is used
    if (SystemCoreClock == 32000000) { // HSI
        if (hz < 250000) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_256; // 125 kHz
        } else if ((hz >= 250000) && (hz < 500000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_128; // 250 kHz
        } else if ((hz >= 500000) && (hz < 1000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_64; // 500 kHz
        } else if ((hz >= 1000000) && (hz < 2000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_32; // 1 MHz
        } else if ((hz >= 2000000) && (hz < 4000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_16; // 2 MHz
        } else if ((hz >= 4000000) && (hz < 8000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_8; // 4 MHz
        } else if ((hz >= 8000000) && (hz < 16000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_4; // 8 MHz
        } else { // >= 16000000
            obj->br_presc = SPI_BAUDRATEPRESCALER_2; // 16 MHz
        }
    } else { // 24 MHz - HSE
        if (hz < 180000) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_256; // 94 kHz
        } else if ((hz >= 180000) && (hz < 350000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_128; // 188 kHz
        } else if ((hz >= 350000) && (hz < 750000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_64; // 375 kHz
        } else if ((hz >= 750000) && (hz < 1000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_32; // 750 kHz
        } else if ((hz >= 1000000) && (hz < 3000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_16; // 1.5 MHz
        } else if ((hz >= 3000000) && (hz < 6000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_8; // 3 MHz
        } else if ((hz >= 6000000) && (hz < 12000000)) {
            obj->br_presc = SPI_BAUDRATEPRESCALER_4; // 6 MHz
        } else { // >= 12000000
            obj->br_presc = SPI_BAUDRATEPRESCALER_2; // 12 MHz
        }
    }
    init_spi(obj);
}

static inline int ssp_readable(spi_t *obj)
{
    int status;
    SpiHandle.Instance = (SPI_TypeDef *)(obj->spi);
    // Check if data is received
    status = ((__HAL_SPI_GET_FLAG(&SpiHandle, SPI_FLAG_RXNE) != RESET) ? 1 : 0);
    return status;
}

static inline int ssp_writeable(spi_t *obj)
{
    int status;
    SpiHandle.Instance = (SPI_TypeDef *)(obj->spi);
    // Check if data is transmitted
    status = ((__HAL_SPI_GET_FLAG(&SpiHandle, SPI_FLAG_TXE) != RESET) ? 1 : 0);
    return status;
}

static inline void ssp_write(spi_t *obj, int value)
{
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_writeable(obj));
    spi->DR = (uint16_t)value;
}

static inline int ssp_read(spi_t *obj)
{
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_readable(obj));
    return (int)spi->DR;
}

static inline int ssp_busy(spi_t *obj)
{
    int status;
    SpiHandle.Instance = (SPI_TypeDef *)(obj->spi);
    status = ((__HAL_SPI_GET_FLAG(&SpiHandle, SPI_FLAG_BSY) != RESET) ? 1 : 0);
    return status;
}

int spi_master_write(spi_t *obj, int value)
{
    ssp_write(obj, value);
    return ssp_read(obj);
}

int spi_slave_receive(spi_t *obj)
{
    return (ssp_readable(obj) ? 1 : 0);
};

int spi_slave_read(spi_t *obj)
{
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_readable(obj));
    return (int)spi->DR;
}

void spi_slave_write(spi_t *obj, int value)
{
    SPI_TypeDef *spi = (SPI_TypeDef *)(obj->spi);
    while (!ssp_writeable(obj));
    spi->DR = (uint16_t)value;
}

int spi_busy(spi_t *obj)
{
    return ssp_busy(obj);
}

#endif
