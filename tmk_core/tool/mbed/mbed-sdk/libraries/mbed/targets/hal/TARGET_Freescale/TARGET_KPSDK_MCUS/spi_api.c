/* mbed Microcontroller Library
 * Copyright (c) 2013 ARM Limited
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
#include <math.h>
#include "mbed_assert.h"

#include "spi_api.h"

#if DEVICE_SPI

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "fsl_clock_manager.h"
#include "fsl_dspi_hal.h"
#include "PeripheralPins.h"

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel) {
    // determine the SPI to use
    uint32_t spi_mosi = pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    uint32_t spi_miso = pinmap_peripheral(miso, PinMap_SPI_MISO);
    uint32_t spi_sclk = pinmap_peripheral(sclk, PinMap_SPI_SCLK);
    uint32_t spi_ssel = pinmap_peripheral(ssel, PinMap_SPI_SSEL);
    uint32_t spi_data = pinmap_merge(spi_mosi, spi_miso);
    uint32_t spi_cntl = pinmap_merge(spi_sclk, spi_ssel);

    obj->instance = pinmap_merge(spi_data, spi_cntl);
    MBED_ASSERT((int)obj->instance != NC);

    CLOCK_SYS_EnableSpiClock(obj->instance);
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    DSPI_HAL_Init(spi_address[obj->instance]);
    DSPI_HAL_Disable(spi_address[obj->instance]);
    // set default format and frequency
    if (ssel == NC) {
        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
    } else {
        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
    }
    DSPI_HAL_SetDelay(spi_address[obj->instance], kDspiCtar0, 0, 0, kDspiPcsToSck);
    spi_frequency(obj, 1000000);

    DSPI_HAL_Enable(spi_address[obj->instance]);
    DSPI_HAL_StartTransfer(spi_address[obj->instance]);

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
    dspi_data_format_config_t config = {0};
    config.bitsPerFrame = (uint32_t)bits;
    config.clkPolarity = (mode & 0x2) ? kDspiClockPolarity_ActiveLow : kDspiClockPolarity_ActiveHigh;
    config.clkPhase = (mode & 0x1) ? kDspiClockPhase_SecondEdge : kDspiClockPhase_FirstEdge;
    config.direction = kDspiMsbFirst;
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    dspi_status_t result = DSPI_HAL_SetDataFormat(spi_address[obj->instance], kDspiCtar0, &config);
    if (result != kStatus_DSPI_Success) {
        error("Failed to configure SPI data format");
    }

    if (slave) {
        DSPI_HAL_SetMasterSlaveMode(spi_address[obj->instance], kDspiSlave);
    } else {
        DSPI_HAL_SetMasterSlaveMode(spi_address[obj->instance], kDspiMaster);
    }
}

void spi_frequency(spi_t *obj, int hz) {
    uint32_t busClock;
    CLOCK_SYS_GetFreq(kBusClock, &busClock);
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    DSPI_HAL_SetBaudRate(spi_address[obj->instance], kDspiCtar0, (uint32_t)hz, busClock);
}

static inline int spi_writeable(spi_t * obj) {
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    return DSPI_HAL_GetStatusFlag(spi_address[obj->instance], kDspiTxFifoFillRequest);
}

static inline int spi_readable(spi_t * obj) {
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    return DSPI_HAL_GetStatusFlag(spi_address[obj->instance], kDspiRxFifoDrainRequest);
}

int spi_master_write(spi_t *obj, int value) {
    uint32_t spi_address[] = SPI_BASE_ADDRS;

    // wait tx buffer empty
    while(!spi_writeable(obj));
    dspi_command_config_t command = {0};
    command.isEndOfQueue = true;
    command.isChipSelectContinuous = 0;
    DSPI_HAL_WriteDataMastermode(spi_address[obj->instance], &command, (uint16_t)value);
    DSPI_HAL_ClearStatusFlag(spi_address[obj->instance], kDspiTxFifoFillRequest);

    // wait rx buffer full
    while (!spi_readable(obj));
    DSPI_HAL_ClearStatusFlag(spi_address[obj->instance], kDspiRxFifoDrainRequest);
    return DSPI_HAL_ReadData(spi_address[obj->instance]) & 0xff;
}

int spi_slave_receive(spi_t *obj) {
    return spi_readable(obj);
}

int spi_slave_read(spi_t *obj) {
    DSPI_HAL_ClearStatusFlag(obj->instance, kDspiRxFifoDrainRequest);
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    return DSPI_HAL_ReadData(spi_address[obj->instance]);
}

void spi_slave_write(spi_t *obj, int value) {
    while (!spi_writeable(obj));
    uint32_t spi_address[] = SPI_BASE_ADDRS;
    DSPI_HAL_WriteDataSlavemode(spi_address[obj->instance], (uint32_t)value);
}

#endif
