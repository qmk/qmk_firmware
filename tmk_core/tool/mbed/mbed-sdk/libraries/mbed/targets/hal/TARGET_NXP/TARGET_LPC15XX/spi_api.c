/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed_assert.h"
#include <math.h>

#include "spi_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

static const SWM_Map SWM_SPI_SSEL[] = {
    {4, 0},
    {5, 24},
};

static const SWM_Map SWM_SPI_SCLK[] = {
    {3, 8},
    {5, 0},
};

static const SWM_Map SWM_SPI_MOSI[] = {
    {3, 16},
    {5, 8},
};

static const SWM_Map SWM_SPI_MISO[] = {
    {3, 24},
    {5, 16},
};

// bit flags for used SPIs
static unsigned char spi_used = 0;
static int get_available_spi(PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    if (spi_used == 0) {
        return 0; // The first user
    }

    const SWM_Map *swm;
    uint32_t regVal;

    // Investigate if same pins as the used SPI0/1 - to be able to reuse it
    for (int spi_n = 0; spi_n < 2; spi_n++) {
        if (spi_used & (1<<spi_n)) {
            if (sclk != NC) {
                swm = &SWM_SPI_SCLK[spi_n];
                regVal = LPC_SWM->PINASSIGN[swm->n] & (0xFF << swm->offset);
                if (regVal != (sclk << swm->offset)) {
                    // Existing pin is not the same as the one we want
                    continue;
                }
            }

            if (mosi != NC) {
                swm = &SWM_SPI_MOSI[spi_n];
                regVal = LPC_SWM->PINASSIGN[swm->n] & (0xFF << swm->offset);
                if (regVal != (mosi << swm->offset)) {
                    // Existing pin is not the same as the one we want
                    continue;
                }
            }

            if (miso != NC) {
                swm = &SWM_SPI_MISO[spi_n];
                regVal = LPC_SWM->PINASSIGN[swm->n] & (0xFF << swm->offset);
                if (regVal != (miso << swm->offset)) {
                    // Existing pin is not the same as the one we want
                    continue;
                }
            }

            if (ssel != NC) {
                swm = &SWM_SPI_SSEL[spi_n];
                regVal = LPC_SWM->PINASSIGN[swm->n] & (0xFF << swm->offset);
                if (regVal != (ssel << swm->offset)) {
                    // Existing pin is not the same as the one we want
                    continue;
                }
            }

            // The pins for the currently used SPIx are the same as the
            // ones we want so we will reuse it
            return spi_n;
        }
    }

    // None of the existing SPIx pin setups match the pins we want
    // so the last hope is to select one unused SPIx
    if ((spi_used & 1) == 0) {
        return 0;
    } else if ((spi_used & 2) == 0) {
        return 1;
    }

    // No matching setup and no free SPIx
    return -1;
}

static inline void spi_disable(spi_t *obj);
static inline void spi_enable(spi_t *obj);

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    int spi_n = get_available_spi(mosi, miso, sclk, ssel);
    if (spi_n == -1) {
        error("No available SPI");
    }

    obj->spi_n = spi_n;
    spi_used |= (1 << spi_n);

    obj->spi = (spi_n) ? (LPC_SPI0_Type *)(LPC_SPI1_BASE) : (LPC_SPI0_Type *)(LPC_SPI0_BASE);

    const SWM_Map *swm;
    uint32_t regVal;

    if (sclk != NC) {
        swm = &SWM_SPI_SCLK[obj->spi_n];
        regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
        LPC_SWM->PINASSIGN[swm->n] = regVal |  (sclk   << swm->offset);
    }

    if (mosi != NC) {
        swm = &SWM_SPI_MOSI[obj->spi_n];
        regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
        LPC_SWM->PINASSIGN[swm->n] = regVal |  (mosi   << swm->offset);
    }

    if (miso != NC) {
        swm = &SWM_SPI_MISO[obj->spi_n];
        regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
        LPC_SWM->PINASSIGN[swm->n] = regVal |  (miso   << swm->offset);
    }

    if (ssel != NC) {
        swm = &SWM_SPI_SSEL[obj->spi_n];
        regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
        LPC_SWM->PINASSIGN[swm->n] = regVal |  (ssel   << swm->offset);
    }

    // clear interrupts
    obj->spi->INTENCLR = 0x3f;

    // enable power and clocking
    LPC_SYSCON->SYSAHBCLKCTRL1 |=  (0x1 << (obj->spi_n + 9));
    LPC_SYSCON->PRESETCTRL1    |=  (0x1 << (obj->spi_n + 9));
    LPC_SYSCON->PRESETCTRL1    &= ~(0x1 << (obj->spi_n + 9));

    // set default format and frequency
    if (ssel == NC) {
        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
    } else {
        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
    }
    spi_frequency(obj, 1000000);

    // enable the spi channel
    spi_enable(obj);
}

void spi_free(spi_t *obj)
{
}

void spi_format(spi_t *obj, int bits, int mode, int slave)
{
    spi_disable(obj);
    MBED_ASSERT((bits >= 1 && bits <= 16) && (mode >= 0 && mode <= 3));

    int polarity = (mode & 0x2) ? 1 : 0;
    int phase = (mode & 0x1) ? 1 : 0;

    // set it up
    int LEN = bits - 1;             // LEN  - Data Length
    int CPOL = (polarity) ? 1 : 0;  // CPOL - Clock Polarity select
    int CPHA = (phase) ? 1 : 0;     // CPHA - Clock Phase select

    uint32_t tmp = obj->spi->CFG;
    tmp &= ~((1 << 5) | (1 << 4) | (1 << 2));
    tmp |= (CPOL << 5) | (CPHA << 4) | ((slave ? 0 : 1) << 2);
    obj->spi->CFG = tmp;

    // select frame length
    tmp = obj->spi->TXCTL;
    tmp &= ~(0xf << 24);
    tmp |= (LEN << 24);
    obj->spi->TXCTL = tmp;

    spi_enable(obj);
}

void spi_frequency(spi_t *obj, int hz)
{
    spi_disable(obj);

    // rise DIV value if it cannot be divided
    obj->spi->DIV = (SystemCoreClock + (hz - 1))/hz - 1;
    obj->spi->DLY = 0;

    spi_enable(obj);
}

static inline void spi_disable(spi_t *obj)
{
    obj->spi->CFG &= ~(1 << 0);
}

static inline void spi_enable(spi_t *obj)
{
    obj->spi->CFG |= (1 << 0);
}

static inline int spi_readable(spi_t *obj)
{
    return obj->spi->STAT & (1 << 0);
}

static inline int spi_writeable(spi_t *obj)
{
    return obj->spi->STAT & (1 << 1);
}

static inline void spi_write(spi_t *obj, int value)
{
    while (!spi_writeable(obj));
    // end of transfer
    obj->spi->TXCTL |= (1 << 20);
    obj->spi->TXDAT = (value & 0xffff);
}

static inline int spi_read(spi_t *obj)
{
    while (!spi_readable(obj));
    return obj->spi->RXDAT & 0xffff; // Only the lower 16 bits contain data
}

int spi_busy(spi_t *obj)
{
    // checking RXOV(Receiver Overrun interrupt flag)
    return obj->spi->STAT & (1 << 2);
}

int spi_master_write(spi_t *obj, int value)
{
    spi_write(obj, value);
    return spi_read(obj);
}

int spi_slave_receive(spi_t *obj)
{
    return (spi_readable(obj) && !spi_busy(obj)) ? (1) : (0);
}

int spi_slave_read(spi_t *obj)
{
    return obj->spi->RXDAT & 0xffff; // Only the lower 16 bits contain data
}

void spi_slave_write(spi_t *obj, int value)
{
    while (spi_writeable(obj) == 0) ;
    obj->spi->TXDAT = value;
}
