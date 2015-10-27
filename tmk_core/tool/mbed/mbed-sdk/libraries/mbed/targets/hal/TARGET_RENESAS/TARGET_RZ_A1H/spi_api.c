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
#include "RZ_A1_Init.h"

static const PinMap PinMap_SPI_SCLK[] = {
    {P10_12, SPI_0, 4},
    {P4_4  , SPI_1, 2},
    {P11_12, SPI_1, 2},
    {P8_3  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const PinMap PinMap_SPI_SSEL[] = {
    {P10_13, SPI_0, 4},
    {P4_5  , SPI_1, 2},
    {P11_13, SPI_1, 2},
    {P8_4  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const PinMap PinMap_SPI_MOSI[] = {
    {P10_14, SPI_0, 4},
    {P4_6  , SPI_1, 2},
    {P11_14, SPI_1, 2},
    {P8_5  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const PinMap PinMap_SPI_MISO[] = {
    {P10_15, SPI_0, 4},
    {P4_7  , SPI_1, 2},
    {P11_15, SPI_1, 2},
    {P8_6  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const struct st_rspi *RSPI[] = RSPI_ADDRESS_LIST;

static inline void spi_disable(spi_t *obj);
static inline void spi_enable(spi_t *obj);
static inline int spi_readable(spi_t *obj);
static inline void spi_write(spi_t *obj, int value);
static inline int spi_read(spi_t *obj);

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel) {
    // determine the SPI to use
    volatile uint8_t dummy;
    uint32_t spi_mosi = pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    uint32_t spi_miso = pinmap_peripheral(miso, PinMap_SPI_MISO);
    uint32_t spi_sclk = pinmap_peripheral(sclk, PinMap_SPI_SCLK);
    uint32_t spi_ssel = pinmap_peripheral(ssel, PinMap_SPI_SSEL);
    uint32_t spi_data = pinmap_merge(spi_mosi, spi_miso);
    uint32_t spi_cntl = pinmap_merge(spi_sclk, spi_ssel);
    uint32_t spi      = pinmap_merge(spi_data, spi_cntl);

    MBED_ASSERT((int)spi != NC);

    obj->spi = (struct st_rspi *)RSPI[spi];

    // enable power and clocking
    switch (spi) {
        case SPI_0: CPGSTBCR10 &= ~(0x80); break;
        case SPI_1: CPGSTBCR10 &= ~(0x40); break;
        case SPI_2: CPGSTBCR10 &= ~(0x20); break;
    }
    dummy = CPGSTBCR10;

    obj->spi->SPCR   = 0x00;  // CTRL to 0
    obj->spi->SPSCR  = 0x00;  // no sequential operation
    obj->spi->SSLP   = 0x00;  // SSL 'L' active 
    obj->spi->SPDCR  = 0x20;  // byte access
    obj->spi->SPCKD  = 0x00;  // SSL -> enable CLK delay : 1RSPCK
    obj->spi->SSLND  = 0x00;  // CLK end -> SSL neg delay : 1RSPCK
    obj->spi->SPND   = 0x00;  // delay between CMD : 1RSPCK + 2P1CLK
    obj->spi->SPPCR  = 0x20;  // MOSI Idle fixed value equals 0
    obj->spi->SPBFCR = 0xf0;  // and set trigger count: read 1, write 1
    obj->spi->SPBFCR = 0x30;  // and reset buffer

    // set default format and frequency
    if ((int)ssel == NC) {
        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
    } else {
        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
    }
    spi_frequency(obj, 1000000);

    // pin out the spi pins
    pinmap_pinout(mosi, PinMap_SPI_MOSI);
    pinmap_pinout(miso, PinMap_SPI_MISO);
    pinmap_pinout(sclk, PinMap_SPI_SCLK);
    if ((int)ssel != NC) {
        pinmap_pinout(ssel, PinMap_SPI_SSEL);
    }
}

void spi_free(spi_t *obj) {}

void spi_format(spi_t *obj, int bits, int mode, int slave) {
    int      DSS;      // DSS (data select size)
    int      polarity  = (mode & 0x2) ? 1 : 0;
    int      phase     = (mode & 0x1) ? 1 : 0;
    uint16_t tmp       = 0;
    uint16_t mask      = 0xf03;
    uint16_t wk_spcmd0;
    uint8_t  splw;

    switch (mode) {
        case 0:
        case 1:
        case 2:
        case 3:
            // Do Nothing
            break;
        default:
            error("SPI format error");
            return;
    }

    switch (bits) {
        case 8:
            DSS  = 0x7;
            splw = 0x20;
            break;
        case 16:
            DSS  = 0xf;
            splw = 0x40;
            break;
        case 32:
            DSS  = 0x2;
            splw = 0x60;
            break;
        default:
            error("SPI module don't support other than 8/16/32bits");
            return;
    }
    tmp |= phase;
    tmp |= (polarity << 1);
    tmp |= (DSS << 8);
    obj->bits = bits;

    spi_disable(obj);
    wk_spcmd0 = obj->spi->SPCMD0;
    wk_spcmd0 &= ~mask;
    wk_spcmd0 |= (mask & tmp);
    obj->spi->SPCMD0 = wk_spcmd0;
    obj->spi->SPDCR   = splw;
    if (slave) {
        obj->spi->SPCR &=~(1 << 3);  // MSTR to 0
    } else {
        obj->spi->SPCR |= (1 << 3);  // MSTR to 1
    }
    spi_enable(obj);
}

void spi_frequency(spi_t *obj, int hz) {
    uint32_t  pclk_base;
    uint32_t  div;
    uint32_t  brdv = 0;
    uint32_t  hz_max;
    uint32_t  hz_min;
    uint16_t  mask = 0x000c;
    uint16_t  wk_spcmd0;

    /* set PCLK */
    if (RZ_A1_IsClockMode0() == false) {
        pclk_base = CM1_RENESAS_RZ_A1_P1_CLK;
    } else {
        pclk_base = CM0_RENESAS_RZ_A1_P1_CLK;
    }

    hz_min = pclk_base / 2 / 256 / 8;
    hz_max = pclk_base / 2;
    if ((hz < hz_min) || (hz > hz_max)) {
        error("Couldn't setup requested SPI frequency");
        return;
    }

    div = (pclk_base / hz / 2);
    while (div > 256) {
        div >>= 1;
        brdv++;
    }
    div  -= 1;
    brdv  = (brdv << 2);

    spi_disable(obj);
    obj->spi->SPBR = div;
    wk_spcmd0 = obj->spi->SPCMD0;
    wk_spcmd0 &= ~mask;
    wk_spcmd0 |= (mask & brdv);
    obj->spi->SPCMD0 = wk_spcmd0;
    spi_enable(obj);
}

static inline void spi_disable(spi_t *obj) {
    obj->spi->SPCR &= ~(1 << 6);       // SPE to 0
}

static inline void spi_enable(spi_t *obj) {
    obj->spi->SPCR |=  (1 << 6);       // SPE to 1
}

static inline int spi_readable(spi_t *obj) {
    return obj->spi->SPSR & (1 << 7);  // SPRF
}

static inline int spi_tend(spi_t *obj) {
    return obj->spi->SPSR & (1 << 6);  // TEND
}

static inline void spi_write(spi_t *obj, int value) {
    if (obj->bits == 8) {
        obj->spi->SPDR.UINT8[0]  = (uint8_t)value;
    } else if (obj->bits == 16) {
        obj->spi->SPDR.UINT16[0] = (uint16_t)value;
    } else {
        obj->spi->SPDR.UINT32    = (uint32_t)value;
    }
}

static inline int spi_read(spi_t *obj) {
    int read_data;

    if (obj->bits == 8) {
        read_data = obj->spi->SPDR.UINT8[0];
    } else if (obj->bits == 16) {
        read_data = obj->spi->SPDR.UINT16[0];
    } else {
        read_data = obj->spi->SPDR.UINT32;
    }

    return read_data;
}

int spi_master_write(spi_t *obj, int value) {
    spi_write(obj, value);
    while(!spi_tend(obj));
    return spi_read(obj);
}

int spi_slave_receive(spi_t *obj) {
    return (spi_readable(obj) && !spi_busy(obj)) ? (1) : (0);
}

int spi_slave_read(spi_t *obj) {
    return spi_read(obj);
}

void spi_slave_write(spi_t *obj, int value) {
    spi_write(obj, value);
}

int spi_busy(spi_t *obj) {
    return 0;
}
