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
#include "spi_api.h"

#include <math.h>

#include "cmsis.h"
#include "pinmap.h"

static const PinMap PinMap_SPI_SCLK[] = {
    {PTA15, SPI_0, 2},
    {PTB9,  SPI_1, 2},
    {PTB11, SPI_1, 2},
    {PTC5,  SPI_0, 2},
    {PTD1,  SPI_0, 2},
    {PTD5,  SPI_1, 2},
    {PTE2,  SPI_1, 2},
    {PTE17, SPI_0, 2},
    {NC  ,  NC   , 0}
};

static const PinMap PinMap_SPI_MOSI[] = {
    {PTA16, SPI_0, 2},
    {PTA17, SPI_0, 5},
    {PTB16, SPI_1, 2},
    {PTB17, SPI_1, 5},
    {PTC6,  SPI_0, 2},
    {PTC7,  SPI_0, 5},
    {PTD2,  SPI_0, 2},
    {PTD3,  SPI_0, 5},
    {PTD6,  SPI_1, 2},
    {PTD7,  SPI_1, 5},
    {PTE1,  SPI_1, 2},
    {PTE3,  SPI_1, 5},
    {PTE18, SPI_0, 2},
    {PTE19, SPI_0, 5},
    {NC  ,  NC   , 0}
};

static const PinMap PinMap_SPI_MISO[] = {
    {PTA16, SPI_0, 5},
    {PTA17, SPI_0, 2},
    {PTB16, SPI_1, 5},
    {PTB17, SPI_1, 2},
    {PTC6,  SPI_0, 5},
    {PTC7,  SPI_0, 2},
    {PTD2,  SPI_0, 5},
    {PTD3,  SPI_0, 2},
    {PTD6,  SPI_1, 5},
    {PTD7,  SPI_1, 2},
    {PTE1,  SPI_1, 5},
    {PTE3,  SPI_1, 2},
    {PTE18, SPI_0, 5},
    {PTE19, SPI_0, 2},
    {NC   , NC   , 0}
};

static const PinMap PinMap_SPI_SSEL[] = {
    {PTA14, SPI_0, 2},
    {PTB10, SPI_1, 2},
    {PTC4,  SPI_0, 2},
    {PTD0,  SPI_0, 2},
    {PTD4,  SPI_1, 2},
    {PTE4,  SPI_1, 2},
    {PTE16, SPI_0, 2},
    {NC  ,  NC   , 0}
};

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel) {
    // determine the SPI to use
    SPIName spi_mosi = (SPIName)pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    SPIName spi_miso = (SPIName)pinmap_peripheral(miso, PinMap_SPI_MISO);
    SPIName spi_sclk = (SPIName)pinmap_peripheral(sclk, PinMap_SPI_SCLK);
    SPIName spi_ssel = (SPIName)pinmap_peripheral(ssel, PinMap_SPI_SSEL);
    SPIName spi_data = (SPIName)pinmap_merge(spi_mosi, spi_miso);
    SPIName spi_cntl = (SPIName)pinmap_merge(spi_sclk, spi_ssel);

    obj->spi = (SPI_Type*)pinmap_merge(spi_data, spi_cntl);
    MBED_ASSERT((int)obj->spi != NC);

    // enable power and clocking
    switch ((int)obj->spi) {
        case SPI_0: SIM->SCGC5 |= 1 << 13; SIM->SCGC4 |= 1 << 22; break;
        case SPI_1: SIM->SCGC5 |= 1 << 13; SIM->SCGC4 |= 1 << 23; break;
    }

    // set default format and frequency
    if (ssel == NC) {
        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
    } else {
        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
    }
    spi_frequency(obj, 1000000);

    // enable SPI
    obj->spi->C1 |= SPI_C1_SPE_MASK;
    obj->spi->C2 &= ~SPI_C2_SPIMODE_MASK; //8bit

    // pin out the spi pins
    pinmap_pinout(mosi, PinMap_SPI_MOSI);
    pinmap_pinout(miso, PinMap_SPI_MISO);
    pinmap_pinout(sclk, PinMap_SPI_SCLK);
    if (ssel != NC) {
        pinmap_pinout(ssel, PinMap_SPI_SSEL);
    }
}

void spi_free(spi_t *obj) {
    // [TODO]
}
void spi_format(spi_t *obj, int bits, int mode, int slave) {
    MBED_ASSERT((bits == 8) || (bits == 16));
    MBED_ASSERT((mode >= 0) && (mode <= 3));

    uint8_t polarity = (mode & 0x2) ? 1 : 0;
    uint8_t phase = (mode & 0x1) ? 1 : 0;
    uint8_t c1_data = ((!slave) << 4) | (polarity << 3) | (phase << 2);

    // clear MSTR, CPOL and CPHA bits
    obj->spi->C1 &= ~(0x7 << 2);

    // write new value
    obj->spi->C1 |= c1_data;
    if (bits == 8) {
        obj->spi->C2 &= ~SPI_C2_SPIMODE_MASK;
    } else {
        obj->spi->C2 |= SPI_C2_SPIMODE_MASK;
    }
}

void spi_frequency(spi_t *obj, int hz) {
    uint32_t error = 0;
    uint32_t p_error = 0xffffffff;
    uint32_t ref = 0;
    uint8_t  spr = 0;
    uint8_t  ref_spr = 0;
    uint8_t  ref_prescaler = 0;

    // bus clk
    uint32_t PCLK = SystemCoreClock / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1);
    uint8_t prescaler = 1;
    uint8_t divisor = 2;

    for (prescaler = 1; prescaler <= 8; prescaler++) {
        divisor = 2;
        for (spr = 0; spr <= 8; spr++, divisor *= 2) {
            ref = PCLK / (prescaler*divisor);
            if (ref > (uint32_t)hz)
                continue;
            error = hz - ref;
            if (error < p_error) {
                ref_spr = spr;
                ref_prescaler = prescaler - 1;
                p_error = error;
            }
        }
    }

    // set SPPR and SPR
    obj->spi->BR = ((ref_prescaler & 0x7) << 4) | (ref_spr & 0xf);
}

static inline int spi_writeable(spi_t * obj) {
    return (obj->spi->S & SPI_S_SPTEF_MASK) ? 1 : 0;
}

static inline int spi_readable(spi_t * obj) {
    return (obj->spi->S & SPI_S_SPRF_MASK) ? 1 : 0;
}

int spi_master_write(spi_t *obj, int value) {
    int ret;
    if (obj->spi->C2 & SPI_C2_SPIMODE_MASK) {
        // 16bit
        while(!spi_writeable(obj));
        obj->spi->DL = (value & 0xff);
        obj->spi->DH = ((value >> 8) & 0xff);

        // wait rx buffer full
        while (!spi_readable(obj));
        ret = obj->spi->DH;
        ret = (ret << 8) | obj->spi->DL;
    } else {
        //8bit
        while(!spi_writeable(obj));
        obj->spi->DL = (value & 0xff);

        // wait rx buffer full
        while (!spi_readable(obj));
        ret = (obj->spi->DL & 0xff);
    }

    return ret;
}

int spi_slave_receive(spi_t *obj) {
    return spi_readable(obj);
}

int spi_slave_read(spi_t *obj) {
    int ret;
    if (obj->spi->C2 & SPI_C2_SPIMODE_MASK) {
        ret = obj->spi->DH;
        ret = ((ret << 8) | obj->spi->DL);
    } else {
        ret = obj->spi->DL;
    }
    return ret;
}

void spi_slave_write(spi_t *obj, int value) {
    while (!spi_writeable(obj));
    if (obj->spi->C2 & SPI_C2_SPIMODE_MASK) {
        obj->spi->DL = (value & 0xff);
        obj->spi->DH = ((value >> 8) & 0xff);
    } else {
        obj->spi->DL = value;
    }

}
