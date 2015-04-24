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
#include "spi_api.h"

#include <math.h>

#include "cmsis.h"
#include "pinmap.h"

static const PinMap PinMap_SPI_SCLK[] = {
    {PTB0, SPI_0, 3},
    {NC  , NC   , 0}
};

static const PinMap PinMap_SPI_MOSI[] = {
    {PTA7, SPI_0, 3},
    {NC  , NC   , 0}
};

static const PinMap PinMap_SPI_MISO[] = {
    {PTA6, SPI_0, 3},
    {NC  , NC   , 0}
};

static const PinMap PinMap_SPI_SSEL[] = {
    {PTA5, SPI_0, 3},
    {NC  , NC   , 0}
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
        case SPI_0:
          SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK);
          SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
          break;
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
    MBED_ASSERT(bits == 8);
    MBED_ASSERT((mode >= 0) && (mode <= 3));

    uint8_t polarity = (mode & 0x2) ? 1 : 0;
    uint8_t phase = (mode & 0x1) ? 1 : 0;
    uint8_t c1_data = ((!slave) << 4) | (polarity << 3) | (phase << 2);

    // clear MSTR, CPOL and CPHA bits
    obj->spi->C1 &= ~(0x7 << 2);

    // write new value
    obj->spi->C1 |= c1_data;
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
        for (spr = 0; spr <= 8; spr++) {
            ref = PCLK / (prescaler*divisor);
            if (ref > (uint32_t)hz)
                continue;
            error = hz - ref;
            if (error < p_error) {
                ref_spr = spr;
                ref_prescaler = prescaler - 1;
                p_error = error;
            }
            divisor *= 2;
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
    // wait tx buffer empty
    while(!spi_writeable(obj));
    obj->spi->D = (value & 0xff);

    // wait rx buffer full
    while (!spi_readable(obj));
    return obj->spi->D & 0xff;
}

int spi_slave_receive(spi_t *obj) {
    return spi_readable(obj);
}

int spi_slave_read(spi_t *obj) {
    return obj->spi->D;
}

void spi_slave_write(spi_t *obj, int value) {
    while (!spi_writeable(obj));
    obj->spi->D = value;
}
